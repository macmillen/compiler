package semant;

import sym.Sym;
import table.*;
import types.*;

import java.util.Iterator;

import absyn.*;
import jdk.jfr.internal.Type;

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
			node.ty.accept(this);
			symTable.enter(node.name, new TypeEntry(node.ty));
		}

		public void visit(NameTy node) {
			node.ty.accept(this);
			
		}

		public void visit(ArrayTy node) {
			node.baseTy.accept(this);
            resultType = new ArrayType(node.size, resultType);
		}

		public void visit(ProcDec node) {
			node.ty.accept(this);
			ParamTypeList ptList = new ParamTypeList();
			int index = 0;
			ListNodeIterator pIt = node.params.iterator();
			while(node.params.iterator().hasNext()){
				ptList.add(index, new ParamType(pIt.next(), r));
				index ++;
			}
			symTable.enter(node.name, new ProcEntry(ptList, symTable));
		}

		public void visit(ParDec node) {
			node.ty.accept(this);
			resultType = new ParamType(node.ty, node.isRef);
		}

		public void visit(VarDec node) {
			node.ty.accept(this);
			symTable.enter(node.name, new VarEntry(resultType, false));
		}
	}
}



