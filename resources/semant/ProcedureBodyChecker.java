package semant;

import table.*;
import types.*;
import absyn.*;
import sym.Sym;

/*
TO-DO
undefined type ... in line ...
... is not a type in line ...
parameter ... must be a reference parameter in line ...
*/

class ProcedureBodyChecker {

	
	void check(Absyn program, Table globalTable) {
		program.accept(new CheckVisitor(globalTable));
	}

	private class CheckVisitor extends DoNothingVisitor {

		private Type resultType;
		private Table localTable;
		private Table globalTable = new Table();
		private boolean isBooleanExp = false;
		
		public CheckVisitor(Table globalTable){
			this.globalTable = globalTable;
		}

		/*
			redeclaration of ... as procedure in line ...
		*/
		public void visit(ProcDec procDec) {
			ProcEntry e = (ProcEntry) globalTable.lookup(procDec.name);
			if(e != null){

			}
			localTable = e.localTable;
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
			System.out.println("###########################################"+resultType.toString());
			SemanticChecker.checkClass(resultType, ArrayType.class, "illegal indexing a non-array ", arrayVar.row);
			arrayVar.index.accept(this);
			SemanticChecker.checkClass(resultType, PrimitiveType.class, "illegal indexing with a non-integer ", arrayVar.index.row);
		}

		/*
			undefined variable ... in line ...
		*/
		public void visit(SimpleVar simpleVar){
			Entry e = localTable.getDeclaration(simpleVar.name, "undefined variable " + simpleVar.name + " in line " + simpleVar.row);
			SemanticChecker.checkClass(e, VarEntry.class, " is not a variable ", simpleVar.row);
			resultType = ((VarEntry)e).type;
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
			SemanticChecker.checkClass(resultType, leftType.getClass(), "expression combines different types ", opExp.row);
			//Vergleichsoperatoren < 6
			if(opExp.op < 6){
				isBooleanExp = true;
				SemanticChecker.checkClass(leftType, PrimitiveType.class, "Comparison requires integer operands ", opExp.left.row);
				SemanticChecker.checkClass(resultType, PrimitiveType.class, "Comparison requires integer operands ", opExp.right.row);
			}else{
				isBooleanExp = false;
				SemanticChecker.checkClass(leftType, PrimitiveType.class, "arithmetic operation requires integer operands ", opExp.left.row);
				SemanticChecker.checkClass(resultType, PrimitiveType.class, "arithmetic operation requires integer operands ", opExp.right.row);
			}
		}

		
		public void visit(VarExp varExp){
			varExp.var.accept(this);
		}

		public void visit(IntExp intExp){
			resultType = ((TypeEntry) globalTable.lookup(Sym.newSym("int"))).type;
		}
		/*
			assignment has different types in line ...
			assignment requires integer variable in line ...
		*/
		public void visit(AssignStm assignStm){
			assignStm.var.accept(this);
			Type varType = resultType;

			assignStm.exp.accept(this);

			SemanticChecker.checkClass(resultType, varType.getClass(), "assignment has different types ", assignStm.row);
			SemanticChecker.checkClass(resultType, PrimitiveType.class, "assignment requires integer variable", assignStm.row);

		}
		/*
			undefined procedure ... in line ...
			call of non-procedure ... in line ...
			procedure ... argument ... type mismatch in line ...
			procedure ... argument ... must be a variable in line ...
			procedure ... called with too few arguments in line ...
			procedure ... called with too many arguments in line ...
		*/
		public void visit(CallStm callStm){
			Entry e = globalTable.getDeclaration(callStm.name,
			 "undefined procedure " + callStm.name + " in line " + callStm.row);
			
			SemanticChecker.checkClass(e, ProcEntry.class, "call of non-procedure " +callStm.name, callStm.row);
			ProcEntry proc = ((ProcEntry)e);

			ListNodeIterator callStmArgs = callStm.args.iterator();
			int index = 1;
			for(ParamType paramTyp: proc.paramTypes){
				if(callStmArgs.hasNext()){
					Exp arg = (Exp) callStmArgs.next();
					arg.accept(this);

					if( resultType != paramTyp.type){
						throw new RuntimeException("procedure" + callStm.name +
						 "argument " + index + " type mismatch in line " + callStm.row);
					}
					//reference or variable
					if(paramTyp.isRef){
						SemanticChecker.checkClass(arg, VarExp.class,"procedure " + callStm.name + " argument " + index + 
						" must be a must be a variable ", callStm.row);
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
				throw new RuntimeException("’while’ test expression must be of type boolean in line " + whileStm.test.row);
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
