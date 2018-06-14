package semant;

import sym.Sym;
import table.*;
import types.*;
import absyn.*;

class TableBuilder {

	private boolean showTables;
	private Table symTable = new Table();

	Table buildSymbolTables(Absyn program, boolean showTables) {
		TableBuilderVisitor visitor = new TabBuilderVisitor();
		program.accept(visitor);
	}
    
	private class TableBuilderVisitor extends DoNothingVisitor {
		private Type resultType;
		public void visit(DecList list) {
			for(Dec dec: list){
				dec.accept(this);
			}
		}

		public void visit(TypeDec node) {
			
		}

		public void visit(NameTy node) {

		}

		public void visit(ArrayTy node) {

		}

		public void visit(ProcDec node) {

		}

		public void visit(ParDec node) {

		}

		public void visit(VarDec node) {
			node.ty.accept(this);
			symTable.enter(node.name, new VarEntry(resultType, false));
		}
	}
}


