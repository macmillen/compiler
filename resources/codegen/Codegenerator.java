/*
 * Codegen.java -- ECO32 code generator
 */

package codegen;

import java.io.*;
import absyn.*;
import table.*;
import types.*;

public class Codegenerator {

	private PrintWriter output;
	private int label = 0;
	private static final int firstReg = 8;
  private static final int lastReg  = 23;
  private Table globalTable;
  private Table localTable;
  final int SP = 31;
  final int RETR = 30;
  final int FP = 29;
  int rsp = 0;//7
  Type arrayType;
  int areaSize = 0;
  boolean arguments = true;
  String procName = "";
  boolean isRef = false;
  String fn = "";
  int jumpCounter = 0;
  boolean elseBlock = false;
  boolean isCalling = true;
  int totalJumps = 0;
  int tempJumps = 0;
  ProcEntry p;
  boolean ref = false;
  int localvarAreaSize;
  int outgoingAreaSize;

	public Codegenerator (FileWriter writer) {
    output = new PrintWriter(writer);
	}

	public void genCode(Absyn node, Table t, String fn) {
    this.fn = fn;
		assemblerProlog();
		node.accept(new CodegenVisitor(t, firstReg));
	}

	private void checkRegister(int reg) {
		if (reg > lastReg)
			throw new RuntimeException
			("expression too complicated, running out of registers");
	}

	private int newLabel() {
		return label++;
  }
  
  private void jumper() {
    jumpCounter++;
    // tempJumps++;
  }

	private void assemblerProlog() {
		emit(".object " + fn);
		emitImport("printi");
		emitImport("printc");
		emitImport("readi");
		emitImport("readc");
		emitImport("exit");
		emitImport("indexError\n");
	}

	private void emitImport(String id) {
		output.format(".import spllib %s\n", id);
	}
	
	private void emit(String line) {
		output.print(line + "\n");
	}

	private void emitRRI(String opcode, int reg1, int reg2, int value, String comment) {
		output.format("%s $%d $%d %d; %s\n", opcode, reg1, reg2, value, comment);
	}

	private void emitR(String opcode, int reg) {
		output.format("%s $%d\n", opcode, reg);
	}

	private void emitRRI(String opcode, int reg1, int reg2, int value) {
		output.format("%s $%d $%d %d\n", opcode, reg1, reg2, value);
	}

	private void emitRRR(String opcode, int reg1, int reg2, int reg3) {
		output.format("%s $%d $%d $%d\n", opcode, reg1, reg2, reg3);
	}

	private void emitRRL(String opcode, int reg1, int reg2, String labelString) {
		output.format("%s $%d $%d %s\n", opcode, reg1, reg2, labelString);
  }
  
	private void emitRI(String opcode, int reg1, int value) {
		output.format("%s $%d %d\n", opcode, reg1, value);
	}
  
	private void emitRS(String opcode, int reg1, String str) {
		output.format("%s $%d %s\n", opcode, reg1, str);
	}
  
	private void emitRR(String opcode, int reg1, int reg2) {
		output.format("%s $%d $%d\n", opcode, reg1, reg2);
	}

	private void emitLabel(String labelString) {
		output.format("%s:\n", labelString);
	}

	private void emitJump(String labelString) {
		output.format("JMP %s\n", labelString);
	}

	private void emitSS(String s1, String s2) {
		output.print("" + s1 + "" + s2 + "\n");
	}

	public class CodegenVisitor extends DoNothingVisitor {

    public void visit(ProcDec node) {
      ProcEntry procEntry = (ProcEntry) globalTable.lookup(node.name);
      localTable = procEntry.localTable;

      outgoingAreaSize = procEntry.outgoingAreaSize;
      localvarAreaSize = procEntry.localvarAreaSize;
      int argumentAreaSize = procEntry.argumentAreaSize;

      if(node.id().equals("main")) {
        emit(".executable main");
      }

      emit(node.id() + ":");
      emit("; procedure prologue");
      
      if(localvarAreaSize > 0) {
        emit("; allocate space for local variables (" + localvarAreaSize + " bytes)");
        emitRRI("SUBC", SP, SP, localvarAreaSize);
      }

      emit("; save old frame pointer (4 bytes)");
      emitRRI("SUBC", SP, SP, 4);
      emitRR("STW", FP, SP);
      
      emit("; set new frame pointer");
      emitRRI("ADDC", FP, SP, localvarAreaSize + 4);
      
      if(procEntry.isCaller) {
        emit("; save return register (" + node.id() + " calls at least one procedure in its body)");
        emitRRI("SUBC", SP, SP, 4);
        emitRR("STW", RETR, SP);
      }

      if(/*outgoingAreaSize > 0*/ outgoingAreaSize > 0) {
        emit("; allocate space for outgoing arguments (" + outgoingAreaSize + " bytes)");
        emitRRI("SUBC", SP, SP, outgoingAreaSize);
      }

			/* get symbol table entry for this procedure */
      
			/* prolog */
      
      /* epilog */
      node.params.accept(this);

      node.decls.accept(this);

      emit("; procedure body");
      node.body.accept(this);

      emit("; procedure epilogue");

      if(isCalling && outgoingAreaSize > 0) {
        emit("; restore return register");
        emitRRI("ADDC", SP, SP, outgoingAreaSize);
        emitRR("LDW", RETR, SP);
        emitRRI("ADDC", SP, SP, 4);
        isCalling = false;
      }

      emit("; restore old frame pointer");
      emitRR("LDW", FP, SP);
      emitRRI("ADDC", SP, SP, localvarAreaSize + 4);
      emit("; return to caller");
      emitR("JMPR", RETR);
      emit("\n");
		}

		public CodegenVisitor(Table t, int i){
      globalTable = t;
    }
    
    public void visit(CompStm compStm){
      compStm.stms.accept(this);
    }
      
    public void visit(CallStm callStm){
      p = (ProcEntry)globalTable.lookup(callStm.name);

      if(p.argumentAreaSize == 0) {
        arguments = false;
      }
      procName = callStm.id();
      callStm.args.accept(this);
      emit("; call procedure " + callStm.id());
      emitRS("CALL", RETR, callStm.id());
      isCalling = true;
      arguments = true;
    }

    public void visit(ExpList expList){
      areaSize = 0;
      int index = 0;
      for(Absyn exp: expList){
        if(arguments) {
          emit("; storing argument #" + index + " for procedure " + procName);
        }
        ref = p.paramTypes.get(index).isRef;
        exp.accept(this);
        if(arguments) {
          emitRRI("SUBC", FP, FP, 8 - 4 * index + localvarAreaSize + outgoingAreaSize);
          emitRR("STW", rsp--, FP);
          emitRRI("ADDC", FP, FP, 8 - 4 * index + localvarAreaSize + outgoingAreaSize);
        } else {
        }
        index++;
        areaSize += 4;
      }
      arguments = false;
      ref = false;
    }

    public void visit(DecList decList){ // 1x
			for(Absyn dec: decList){
        dec.accept(this);
			}
		}

    public void visit(StmList stmList){
			for(Absyn stm: stmList){
				stm.accept(this);
			}
    }

    public void visit(ArrayVar arrayVar){
      arrayVar.var.accept(this);
      int bytesize = ((ArrayType)arrayType).baseType.byteSize;
      emit("; generating index");
      arrayVar.index.accept(this);
      int arrayLength = ((ArrayType)arrayType).size;
      emit("; boundary check");
      emitRI("SETW", ++rsp, arrayLength);
      emitRRR("LTU", rsp, rsp - 1, rsp);
      emitRS("BRF", rsp--, "indexError");
      emitRI("SETW", ++rsp, bytesize);
      emitRRR("MULU", rsp - 1, rsp - 1, rsp--);
      emitRRR("ADD", rsp - 1, rsp - 1, rsp--);

      // bei arrayAccess in arrayaAccess
      arrayType = ((ArrayType)arrayType).baseType;
    }
    
    public void visit(SimpleVar simpleVar){
      VarEntry varEntry = (VarEntry)localTable.lookup(simpleVar.name);
      
      if(varEntry.type instanceof ArrayType) {
        arrayType = varEntry.type;
      }

      if(varEntry.isParam) {
        emitRRI("ADDC", ++rsp, FP, varEntry.offset);
      } else {
        emitRRI("SUBC", ++rsp, FP, varEntry.offset);
      }
      isRef = varEntry.isRef;
      if(isRef) {
        emitRR("LDW", rsp, rsp);
      }
    }
    
    public void visit(VarExp varExp){
      varExp.var.accept(this);
      if(!ref)
        emitRR("LDW", rsp, rsp);
    }

    public void visit(AssignStm assignStm){
      assignStm.var.accept(this);
      assignStm.exp.accept(this);
      emitRR("STW", rsp, --rsp);
      --rsp;
    }
    
    public void visit(VarDec varDec){
    }

    public void visit(OpExp opExp){
      opExp.left.accept(this);
      opExp.right.accept(this);
      
      String opCode = "NULL";
      switch(opExp.op) {
        case OpExp.LST: opCode = "LTI"; break;
        case OpExp.LSE: opCode = "LEI"; break;
        case OpExp.GRT: opCode = "GTI"; break;
        case OpExp.GRE: opCode = "GEI"; break;
        case OpExp.EQU: opCode = "EQ"; break;
        case OpExp.NEQ: opCode = "NE"; break;

        case OpExp.ADD: opCode = "ADD"; break;
        case OpExp.SUB: opCode = "SUB"; break;
        case OpExp.MUL: opCode = "MULI"; break;
        case OpExp.DIV: opCode = "DIVI"; break;
      }
      emitRRR(opCode, rsp - 1, rsp - 1, rsp);
      rsp--;
    }

    public void visit(EmptyStm emptyStm){
      elseBlock = false;
    }

    public void visit(IntExp intExp){
      emitRI("SETW", ++rsp, intExp.val);
    }

    public void visit(IfStm ifStm){
      int elseLabel = label;
      if(ifStm.elsePart instanceof EmptyStm) {
        elseBlock = false;
      } else {
        elseBlock = true;
      }
      
      ifStm.test.accept(this);
      
      emitRS("BRF", rsp--, "l" + newLabel());
      jumpCounter = 0;
// emit(";;;TEST");

      ifStm.thenPart.accept(this);
// emit(";;;THEN");

      if(elseBlock) {
        elseLabel = newLabel();
        emitJump("l" + elseLabel);
        emitLabel("l" + (label - 2 - jumpCounter));
        jumpCounter++;
      }
      
      ifStm.elsePart.accept(this);
// emit(";;;ELSE");
      emitLabel("l" + (elseLabel));
      jumpCounter++;
    }

    public void visit(WhileStm whileStm){
      jumpCounter = 0;
      
      emitJump("l" + label);
      emitLabel("l" + (label + 1));

      newLabel();
      newLabel();
      whileStm.body.accept(this);
      jumpCounter+=2;
      emitLabel("l" + (label - jumpCounter));
      
      whileStm.test.accept(this);
      emitRS("BRT", rsp--, "l" + (label - jumpCounter + 1));
      // (label - el - jumpCounter)

    }
      
    
	}
}
