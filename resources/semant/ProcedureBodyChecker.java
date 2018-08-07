package semant;

import table.*;
import types.*;

import com.sun.org.apache.xalan.internal.xsltc.compiler.sym;

import absyn.*;
import sym.Sym;

class ProcedureBodyChecker {

	private Table symTable = new Table();

	void check(Absyn program, Table globalTable) {
		program.accept(new CheckVisitor(globalTable));
	}

	private class CheckVisitor extends DoNothingVisitor {

		private Type resultType;
		private Entry resultEntry;
		private Table localTable;
		private boolean isBooleanExp = false;


		/*
			redeclaration of ... as procedure in line ...
		*/
		public void visit(ProcDec procDec) {
			localTable = ((ProcEntry)symTable.lookup(procDec.name)).localTable;
			procDec.params.accept(this);
			procDec.decls.accept(this);
			procDec.body.accept(this);
		}

		public void visit(CompStm node) {
			node.stms.accept(this);
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
		
		public void visit(ExpList expList){
			for(Absyn exp: expList){
				exp.accept(this);
			}
		}
		/*
			illegal indexing a non-array in line ...
    		illegal indexing with a non-integer in line ...
		*/
		public void visit(ArrayVar arrayVar){
			arrayVar.var.accept(this);
			SemanticChecker.checkClass(resultType, ArrayType.class, "illegal indexing a non-array ", arrayVar.row);
			
			arrayVar.index.accept(this);
			SemanticChecker.checkClass(resultType, PrimitiveType.class, "illegal indexing with a non-integer ", arrayVar.index.row);
		}

		/*
			undefined variable ... in line ...
		*/
		public void visit(SimpleVar simpleVar){
			Entry e = localTable.getDeclaration(sym, "undefined variable " + simpleVar.name + " in line " + simpleVar.row);
			SemanticChecker.checkClass(e, VarEntry.class, " is not a variable ", arrayVar.index.row);
			resultType = ((VarEntry)e).type;
			resultEntry = e;
		}

		/*
			expression combines different types in line ...
			comparison requires integer operands in line ...
			arithmetic operation requires integer operands in line ...
		*/
		public void visit(OpExp opExp){
			
			opExp.left.accept(this);
			Type leftType = resultType;
			opExp.right.accept(this);
			SemanticChecker.checkClass(resultType, leftType.getClass(), "expression combines different types ", lineNo);
			//Vergleichsoperatoren < 6
			if(opExp.op < 6){
				isBooleanExp = true;
				SemanticChecker.checkClass(leftType, IntExp.class, "Comparison requires integer operands ", opExp.left.row);
				SemanticChecker.checkClass(resultType, IntExp.class, "Comparison requires integer operands ", opExp.right.row);
			}else{
				isBooleanExp = false;
				SemanticChecker.checkClass(leftType, IntExp.class, "arithmetic operation requires integer operands ", opExp.left.row);
				SemanticChecker.checkClass(resultType, IntExp.class, "arithmetic operation requires integer operands ", opExp.right.row);
			}
		}

		
		public void visit(VarExp varExp){
			varExp.var.accept(this);
		}

		public void visit(IntExp intExp){
			resultEntry = symTable.lookup(Sym.newSym("int"));
			resultType = ((TypeEntry) resultEntry).type;
		}
		/*
			assignment has different types in line ...
			assignment requires integer variable in line ...
		*/
		public void visit(AssignStm assignStm){
			assignStm.var.accept(this);
			Type varType = resultType;

			assignStm.exp.accept(this);

			SemanticChecker(resultType, varType.getClass(), "assignment has different types ", assignStm.row);


		}
		/*
			undefined procedure ... in line ...
			call of non-procedure ... in line ...
			procedure ... argument ... type mismatch in line ...
			procedure ... argument ... must be a variable in line ...
			parameter ... must be a reference parameter in line ...
			procedure ... called with too few arguments in line ...
			procedure ... called with too many arguments in line ...
		*/
		public void visit(CallStm callStm){
			Entry e = symTable.getDeclaration(callStm.name,
			 "undefined procedure " + callStm.name + " in line " + callStm.row);
			
			SemanticChecker.checkClass(e, ProcEntry.class, "call of non-procedure " +callStm.name, callStm.row);
			ProcEntry proc = ((ProcEntry)e);

			int argumentSize = proc.paramTypes.size();
			ListNodeIterator callStmArgs = callStm.args.iterator();
			int index = 1;
			for(ParamType paramTyp: proc.paramTypes){
				if(callStmArgs.hasNext()){
					Exp arg = callStmArgs.next();
					arg.accept(this);

					if( resultType != paramTyp.type){
						throw new RuntimeException("procedure" + callStm.name +
						 "argument " + index + " type mismatch in line " + callStm.row);
					}
					//reference or variable
					if(paramTyp.isRef){
						VarEntry entry = (VarEntry) resultEntry;
						if(!entry.isRef){
							throw new RuntimeException("parameter " + index + 
							" must be a reference parameter in line  " + callStm.row);
						}	
					}else{
						if(entry.isRef){
							throw new RuntimeException( "argument " + index + 
							" must be a reference parameter in line  " + callStm.row);
						}	
					}
				}else{
					throw new RuntimeException("procedure "+ callStm.name + 
					" called with too few arguments in line " + callStm.row);
				}	
				index ++;
			}
			if(callStmArgs.hasNext()){
				throw new RuntimeException("procedure "+ callStm.name.toString() + 
					" called with too many arguments in line " + callStm.row);
			}

		}

		/*
			’while’ test expression must be of type boolean in line ...
		*/
		public void visit(WhileStm whileStm){
			whileStm.test.accept(this);
			if(!isBooleanExp){
				throw new RuntimeException("’while’ test expression must be of type boolean in line " + ifStm.test.row);
			}
			whileStm.body.accept(this);
		}
		/*
		
			if’ test expression must be of type boolean in line ...
		*/
		public void visit(IfStm ifStm){
			ifStm.test.accept(this);
			if(!isBooleanExp){
				throw new RuntimeException("’if’ test expression must be of type boolean in line " + ifStm.test.row);
			}
			ifStm.thenPart.accept(this);
			ifStm.elsePart.accept(this);

		}
		
		public void visit(EmptyStm emptyStm){

		}

	}
}
