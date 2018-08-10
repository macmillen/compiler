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
	private int nextLabel = 0;
	private static final int firstReg = 8;
  private static final int lastReg  = 23;
  private Table globalTable;
  private Table localTable;
  final int SP = 31;
  final int RETR = 30;
  final int FP = 29;
  int rsp = 0;//7
  int imm = -99;
  Type arrayType;
  int areaSize = 0;
  boolean arguments = false;
  String procName = "";
  boolean isRef = false;

	public Codegenerator (FileWriter writer) {
    output = new PrintWriter(writer);
	}

	public void genCode(Absyn node, Table t) {
		assemblerProlog();
		node.accept(new CodegenVisitor(t, firstReg));
	}

	private void checkRegister(int reg) {
		if (reg > lastReg)
			throw new RuntimeException
			("expression too complicated, running out of registers");
	}

	private String newLabel() {
		return "L" + nextLabel++;
	}

	private void assemblerProlog() {
		emitImport("printi");
		emitImport("printc");
		emitImport("readi");
		emitImport("readc");
		emitImport("exit");
		emitImport("indexError");
    emit("\n.executable main");
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

	private void emitR(String opcode, int reg, String comment) {
		output.format("%s$%d; %s\n", opcode, reg, comment);
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
  
	private void emitRR(String opcode, int reg1, int reg2) {
		output.format("%s $%d $%d\n", opcode, reg1, reg2);
	}

	private void emitLabel(String labelString) {
		output.format("%s:\n", labelString);
	}

	private void emitJump(String labelString) {
		output.format("j%s\n", labelString);
	}

	private void emitSS(String s1, String s2) {
		output.print("" + s1 + "" + s2 + "\n");
	}

	public class CodegenVisitor extends DoNothingVisitor {

    public void visit(ProcDec node) { // 2x
      ProcEntry procEntry = (ProcEntry) globalTable.lookup(node.name);
      localTable = procEntry.localTable;

      int outgoingAreaSize = procEntry.outgoingAreaSize;
      int localvarAreaSize = procEntry.localvarAreaSize;
      int argumentAreaSize = procEntry.argumentAreaSize;

      emit("; procedure prologue");
      
      emit("; allocate space for local variables (" + localvarAreaSize + " bytes)");
      emitRRI("SUBC", SP, SP, localvarAreaSize);

      emit("; save old frame pointer (4 bytes)");
      emitRRI("SUBC", SP, SP, 4);
      emitRR("STW", FP, SP);
      
      emit("; set new frame pointer");
      emitRRI("ADDC", FP, SP, localvarAreaSize + 4);
      
      if(procEntry.isCaller) {
        emit("save return register (main calls at least one procedure in its body)");
        emitRRI("SUBC", SP, SP, 4);
        emitRR("STW", RETR, SP);
      }

      emit("; allocate space for outgoing arguments (" + outgoingAreaSize + " bytes)");
      emitRRI("SUBC", SP, SP, outgoingAreaSize);
//simpleVar      (VarEntry) localTable.lookup(node.name);

			/* get symbol table entry for this procedure */
      
			/* prolog */
      
      /* epilog */
      // emit("; procedure params");
      System.out.println("procDec - params");
      node.params.accept(this);

      // emit("; procedure decls");
      System.out.println("procDec - decls");
      node.decls.accept(this);

      emit("; procedure body");
      System.out.println("procDec - body");
      node.body.accept(this);
		}

		public CodegenVisitor(Table t, int i){
      globalTable = t;
    }
    
    public void visit(CallStm callStm){
      System.out.println("callStm");
      arguments = true;
      procName = callStm.name.toString();
      callStm.args.accept(this);
      emitRRI("SUBC", FP, FP, areaSize);
    }

    public void visit(ExpList expList){
      System.out.println("expList");
      areaSize = 0;
      int index = 0;
      for(Absyn exp: expList){
        if(arguments) {
          emit("; storing argument #" + index + " for procedure " + procName);
          if(isRef) {
            // emitRRI("SUBC", reg1, reg2, value);
          } else {
            // emitRR("SETW", FP, reg2);
          }
          // SETW $1 3
          // SUBC $29 $29 20
          // STW $1 $29
          // ADDC $29 $29 20
        }
        exp.accept(this);
        index++;
        areaSize += 4;
      }
      arguments = false;
    }

    public void visit(DecList decList){ // 1x
      System.out.println("decList");
			for(Absyn dec: decList){
        dec.accept(this);
			}
		}

    public void visit(StmList stmList){
      System.out.println("stmList");
			for(Absyn stm: stmList){
				stm.accept(this);
			}
    }

    public void visit(ArrayVar arrayVar){

      arrayVar.var.accept(this);
      // int size = (ArrayType)arrayType.baseType.bytesize;
      arrayVar.index.accept(this);
      // (ArrayType)arrayType.size
    }
    
    public void visit(SimpleVar simpleVar){
      System.out.println("simpleVar");
      VarEntry varEntry = (VarEntry)localTable.lookup(simpleVar.name);
      arrayType = varEntry.type;
      emitRRI("SUBC", ++rsp, FP, varEntry.offset);
      isRef = varEntry.isRef;
    }
    
    public void visit(VarExp varExp){
      System.out.println("varExp");
      varExp.var.accept(this);
      emitRR("LDW", rsp, rsp);
    }

    public void visit(AssignStm assignStm){
      // no code to be generated
      System.out.println("assignStm");
      assignStm.var.accept(this);
      assignStm.exp.accept(this);
      emitRR("STW", rsp, --rsp);
    }
    
    public void visit(VarDec varDec){
      System.out.println("varDec");
    }

    public void visit(OpExp opExp){
      System.out.println("opExp - left");
      opExp.left.accept(this);
      System.out.println("opExp - right");
      opExp.right.accept(this);
      
      String opCode = "NULL";
      switch(opExp.op) { 
        case OpExp.ADD: opCode = "ADD"; break;
        case OpExp.SUB: opCode = "SUB"; break;
        case OpExp.MUL: opCode = "MULI"; break;
        case OpExp.DIV: opCode = "DIVI"; break;
      }
      emitRRR(opCode, rsp - 1, rsp - 1, rsp);
      rsp--;
    }

    public void visit(IntExp intExp){
      System.out.println("intExp");
      
      emitRI("SETW", ++rsp, intExp.val);
    }

    // SUBC $1 $29 4  load FP in $1
    // SETW $2 1      save immidiatVal in $2
    // SETW $3 2      save immidiatVal in $3
    // ADD $2 $2 $3   ADD $2 + $3 and save in $2
    // STW $2 $1      

	}
}
