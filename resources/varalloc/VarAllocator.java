/*
 * Varalloc.java -- variable allocation
 */


package varalloc;

import java.util.Arrays;
import absyn.*;
import table.*;
import types.*;
import sym.*;

public class VarAllocator {

	public static final int INTBYTESIZE = 4;
	public static final int BOOLBYTESIZE = 4;
	public static final int REFBYTESIZE = 4;

	private Table globalTable;
	private Table localTable;
	private boolean showVarAlloc;
	

	public VarAllocator(Table t, boolean b){
		this.globalTable = t;
		this.showVarAlloc = b;
	}

	public void allocVars(Absyn program) {
		program.accept(new VarAllocatorVisitorHead(globalTable));
		program.accept(new VarAllocatorVisitorBody(globalTable));
		if(showVarAlloc){
			program.accept(new VarAllocatorVisitorPrint(globalTable));
		}
	}

	private class VarAllocatorVisitorHead extends DoNothingVisitor{
		
		private Table globalTable;
		private int areaSize = 0;
		private int offset = 0;

		public VarAllocatorVisitorHead(Table globalTable){
			this.globalTable = globalTable;
		}


		public void visit(DecList decList){
			areaSize = 0;
			for(Absyn dec: decList){
				dec.accept(this);
			}
		}

		public void visit(ProcDec procDec){

			
			
			ProcEntry procEntry = (ProcEntry)globalTable.lookup(procDec.name);

			localTable = procEntry.localTable;

			
			//Parameter
			offset = 0;
			areaSize = 0;
			procDec.params.accept(this);
			procEntry.argumentAreaSize = areaSize;
			


			//Lokale Variablen
			offset = 0;
			areaSize = 0;
			procDec.decls.accept(this);
			procEntry.localvarAreaSize = areaSize;
			
		}


		public void visit(ParDec parDec){
			VarEntry parEntry = (VarEntry) localTable.lookup(parDec.name);
			if(parEntry.isRef){
				parEntry.offset = offset;
				offset = offset + VarAllocator.REFBYTESIZE;
				areaSize += VarAllocator.REFBYTESIZE;
			}else{
				parEntry.offset = offset;
				offset = offset + parEntry.type.byteSize;
				areaSize += parEntry.type.byteSize;
			}

		}

		public void visit(VarDec varDec){
			VarEntry varEntry = (VarEntry) localTable.lookup(varDec.name);
			offset = offset + varEntry.type.byteSize;
			varEntry.offset = offset;
			areaSize += varEntry.type.byteSize;
		
		}
	}

	public class VarAllocatorVisitorBody extends DoNothingVisitor{

		private int maxAreaSize = 0;
		private Table globalTable;
		private ProcEntry procEntry;

		public VarAllocatorVisitorBody(Table globalTable){
			this.globalTable = globalTable;
		}

		public void visit(ProcDec procDec){
			procEntry = (ProcEntry)globalTable.lookup(procDec.name);
			procDec.body.accept(this);
		}

		public void visit(CallStm callStm){
			ProcEntry callee = (ProcEntry)globalTable.lookup(callStm.name);
			if(maxAreaSize < callee.argumentAreaSize){
				procEntry.outgoingAreaSize = callee.argumentAreaSize;
			}
		}

		//Body Statments

		public void visit(IfStm ifStm){
			ifStm.thenPart.accept(this);
			ifStm.elsePart.accept(this);
		}

		public void visit(WhileStm whileStm){
			whileStm.body.accept(this);
		}

		public void visit(CompStm compStm){
			compStm.stms.accept(this);
		}

		public void visit(DecList decList){
			for(Absyn dec: decList){
				dec.accept(this);
			}
		}

		public void visit(StmList stmList){
			for(Absyn stm: stmList){
				stm.accept(this);
			}
		}
	
	}


	private class VarAllocatorVisitorPrint extends DoNothingVisitor{

		private Table globalTable;
		private int index = 0;
		private boolean printArguments = true;

		public VarAllocatorVisitorPrint(Table globalTable){
			this.globalTable = globalTable;
		}

		public void visit(ProcDec procDec){
			ProcEntry procEntry = (ProcEntry)globalTable.lookup(procDec.name);
			
			System.out.println(" \nVariable allocation for procedure ‘" + procDec.name + "‘");
		

			localTable = procEntry.localTable;

			//Parameter und Argumente
			printArguments = true;
			procDec.params.accept(this);
			System.out.println("size of argument area = " + procEntry.argumentAreaSize);
			printArguments = false;
			procDec.params.accept(this);
			

			//Lokale Variablen
			procDec.decls.accept(this);
			System.out.println("size of localvar area = " + procEntry.localvarAreaSize);
			System.out.println("size of outgoing area = " + procEntry.outgoingAreaSize);
		}

		public void visit(DecList decList){
			index = 0;
			for(Absyn dec: decList){
				index ++;
				dec.accept(this);
			}
		}

		public void visit(ParDec parDec){
			VarEntry parEntry = (VarEntry) localTable.lookup(parDec.name);
			if(printArguments){
				System.out.println("arg " + index + ": sp + " + parEntry.offset);
			}else{
				System.out.println("param '" + parDec.name  +  "': sp + " + parEntry.offset);
			}
		}

		public void visit(VarDec varDec){
			VarEntry varEntry = (VarEntry) localTable.lookup(varDec.name);
			System.out.println("var '" + varDec.name + "': fp - " + varEntry.offset);
		}
	}
}

