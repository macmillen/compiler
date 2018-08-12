package semant;

import sym.Sym;
import table.*;
import types.*;
import absyn.*;

class TableBuilder {

	private boolean showTables;
	private Table symTable = new Table();
	

	Table buildSymbolTables(Absyn program, boolean showTables) {
		TableBuilderVisitor visitor = new TableBuilderVisitor();
		this.showTables = showTables;
		TableInitializer tableInit = new TableInitializer();
		tableInit.intializeSymbolTable(symTable);
		program.accept(visitor);
		// if(showTables){
		// 	symTable.show();
		// }
		return symTable;
	}
    
	private class TableBuilderVisitor extends DoNothingVisitor {

		private Type resultType;
		private ParamTypeList ptList = new ParamTypeList();

		public void visit(DecList list) {
			// list.head().accept(this);
			// list.tail().accept(this);
			for(Absyn dec: list){
				dec.accept(this);
			}
		}

		public void visit(TypeDec node) {

			Entry e = symTable.lookup(node.name);
			if(e != null){
				throw new RuntimeException("redeclaration of " + node.name + " as type in line " + node.row);
			}

			node.ty.accept(this);
			symTable.enter(node.name, new TypeEntry(resultType));
		}

		
		public void visit(NameTy node) {
			Entry type = symTable.lookup(node.name);

			if(type == null){
				throw new RuntimeException("undefined type " + node.name + " in line " + node.row);
			}

			if(type instanceof TypeEntry){
				resultType = ((TypeEntry)type).type;
			}else{
				throw new RuntimeException(node.name + " is not a type in line " + node.row);
			}
		}

		public void visit(ArrayTy node) {
			node.baseTy.accept(this);
			resultType = new ArrayType(node.size, resultType);
		}

		public void visit(ProcDec node) {
			ptList = new ParamTypeList();

			
			Entry e = symTable.lookup(node.name);
			if (e != null){
				throw new RuntimeException("redeclaration of " + node.name + " as procedure in line " + node.row);
			}
			
			Table globalTable = symTable;
			Table localTable = new Table(symTable);
			symTable = localTable;

			node.params.accept(this);
			node.decls.accept(this);

			symTable = globalTable;

			symTable.enter(node.name, new ProcEntry(ptList, localTable));
			if(showTables){
				localTable.show();
			}
			
		}

		public void visit(ParDec node) {

			Entry e = symTable.lookup(node.name);
			if(e != null){
				throw new RuntimeException("redeclaration of " + node.name + " as parameter in line " + node.row);
			}

      node.ty.accept(this);
			ptList.add(new ParamType(resultType, node.isRef));
      symTable.enter(node.name, new VarEntry(resultType, node.isRef, true));
      
		}

		public void visit(VarDec node) {

			Entry e = symTable.lookup(node.name);
			if(e != null){
				throw new RuntimeException("redeclaration of " + node.name + " as variable in line " + node.row);
			}

			node.ty.accept(this);
			symTable.enter(node.name, new VarEntry(resultType, false, false));
		}
	}
}



