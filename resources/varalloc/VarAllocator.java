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
		program.accept(new VarAllocatorVisitor(globalTable));
	}

	private class VarAllocatorVisitor extends DoNothingVisitor{
		
		private Table globalTable;
		private int areaSize = 0;
		private int offset = 0;
		private int index = 0;

		public VarAllocatorVisitor(Table globalTable){
			this.globalTable = globalTable;
		}


		public void visit(DecList decList){
			areaSize = 0;
			index = 0;
			for(Absyn dec: decList){
				dec.accept(this);
				index++;
			}
		}

		public void visit(ProcDec procDec){

			if(showVarAlloc){
				System.out.println(" \nVariable allocation for procedure ‘" + procDec.name + "‘");
			}
			
			ProcEntry procEntry = (ProcEntry)globalTable.lookup(procDec.name);

			localTable = procEntry.localTable;

			// Aufrufe
			/*
			offset = 0;
			areaSize = 0;
			procDec.body.accept(this);
			procEntry
			*/
			//Parameter
			offset = 0;
			areaSize = 0;
			procDec.params.accept(this);
			procEntry.argumentAreaSize = areaSize;
			if(showVarAlloc){
				System.out.println("size of argument area = " + procEntry.argumentAreaSize);
			}


			//Lokale Variablen
			offset = 0;
			areaSize = 0;
			procDec.decls.accept(this);
			procEntry.localvarAreaSize = areaSize;
			if(showVarAlloc){
				System.out.println("size of localvar area = " + procEntry.localvarAreaSize);
			}
			

		}


		// Outgoing AreaSize
		public void visit(CallStm callStm){

			ProcEntry procEntry = (ProcEntry) globalTable.lookup(callStm.name);

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

			if(showVarAlloc){
				System.out.println("param '" + parDec.name  +  "': sp + " + parEntry.offset);
			}

		}

		public void visit(VarDec varDec){
			VarEntry varEntry = (VarEntry) localTable.lookup(varDec.name);
			offset = offset + varEntry.type.byteSize;
			varEntry.offset = offset;
			areaSize += varEntry.type.byteSize;
			if(showVarAlloc){
				System.out.println("var '" + varDec.name + "': fp - " + varEntry.offset);
			}
		}

		

	}
}

