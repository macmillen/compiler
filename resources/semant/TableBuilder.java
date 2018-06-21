package semant;

import sym.Sym;
import table.*;
import types.*;

import java.util.Iterator;

import absyn.*;
import jdk.jfr.internal.Type;
import sun.tools.tree.ThisExpression;

class TableBuilder {

	private boolean showTables;
	private Table symTable = new Table();
	private ParamTypeList ptList = new ParamTypeList();

	Table buildSymbolTables(Absyn program, boolean showTables) {
		TableBuilderVisitor visitor = new TabBuilderVisitor();
		program.accept(visitor);
	}
    
	private class TableBuilderVisitor extends DoNothingVisitor {

		private Type resultType;

		public void visit(DecList list) {
			list.head().accept(this);
			list.tail().accept(this);
			// for(Dec dec: list){
			// 	dec.accept(this);
			// }
		}

		public void visit(TypeDec node) {
			node.ty.accept(this);
			symTable.enter(node.name, new TypeEntry(node.ty, resultType));
		}

		
		public void visit(NameTy node) {
			Entry type = symTable.lookup(node.name);

			if(type instanceof TypeEntry){
				resultType = ((TypeEntry)type).type;
			}
		}

		public void visit(ArrayTy node) {
			node.baseTy.accept(this);
			resultType = new ArrayType(node.size, resultType);
		}

		public void visit(ProcDec node) {
			node.ty.accept(this);
			ParamTypeList ptList = new ParamTypeList();
			int index = 0;

			Table globalTable = symTable;
			Table localTable = new Table(symTable);
			symTable = localTable;

			ptList = new ParamTypeList();

			node.params.accept(this);
			node.decls.accept(this);
			
			symTable = globalTable;

			symTable.enter(node.name, new ProcEntry(ptList, localTable));
		}

		public void visit(ParDec node) {
			node.ty.accept(this);
			ptList.add(new ParamType(node.ty, node.isRef));
		}

		public void visit(VarDec node) {
			node.ty.accept(this);
			symTable.enter(node.name, new VarEntry(resultType, false));
		}
	}
}



