/* Semant.java -- semantic checks */

package semant;

import absyn.*;
import sym.Sym;
import table.*;
import types.*;
import varalloc.*;
import java.lang.Class;

import javax.management.RuntimeErrorException;

/**
 * A SemanticChecker object defines a method "check" for semantic 
 * analysis and symbol table construction for SPL
 * <br>
 * SemanticChecker is a singleton class
 * <br>
 * author: Michael Jäger
 */

public class SemanticChecker {

	static final Type intType = new PrimitiveType("int", VarAllocator.INTBYTESIZE);
	static final Type boolType = new PrimitiveType("boolean", VarAllocator.BOOLBYTESIZE);

	public Table check(Absyn program, boolean showTables) {
        /* Semantische Prüfung */
		TableBuilder tBuilder = new TableBuilder();
		Table globalTable =  tBuilder.buildSymbolTables(program, showTables);
		
		/* hier gibts noch was zu tun: das Meiste kann an Visitor-Objekte delegiert werden */
		ProcedureBodyChecker bodyChecker = new ProcedureBodyChecker();
		bodyChecker.check(program, globalTable);

		checkMainProcedure(globalTable);

		return globalTable;
	}

	static void checkClass (Object object, Class<?> expectedClass, String errorMessage, int lineNo)  {
		checkClass(object, expectedClass, errorMessage + " in line " + lineNo);
	}

	static void checkClass (Object object, Class<?> expectedClass, String errorMessage)  {
		if (object.getClass()!=expectedClass)
			throw new RuntimeException(errorMessage);
	}

	/*
		procedure ’main’ is missing
		’main’ is not a procedure
		procedure ’main’ must not have any parameters
		redeclaration of ... as procedure in line ...
	*/
	private void checkMainProcedure(Table globalTable) {
		   /* hier gibts noch was zu tun! */
			Entry e = globalTable.getDeclaration(Sym.newSym("main"), "procedure ‘main‘ is missing");
			SemanticChecker.checkClass(e, ProcEntry.class, "procedure ‘main‘ is missing");
			ProcEntry procMain = ((ProcEntry)e);
			if(!procMain.paramTypes.isEmpty()){
				throw new RuntimeException("procedure ’main’ must not have any parameters");
			}
			
	}
}
