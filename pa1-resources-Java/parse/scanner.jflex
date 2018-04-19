/*
 * scanner.jflex -- SPL scanner specification
 */


package parse;


%%


%class Scanner
%public
%line
%column
%type Symbol
%function next_token
%eofval{
  return symbol(sym.EOF);
%eofval}
%eofclose

%{

  private Symbol symbol(int type) {
    return new Symbol(type, yyline + 1, yycolumn + 1);
  }

  private Symbol symbol(int type, Object value) {
    return new Symbol(type, yyline + 1, yycolumn + 1, value);
  }

  public void showToken(Symbol token) {
    String s;
    switch (token.sym) {
      case sym.EOF:
        s = "-- EOF --";
        break;
      case sym.ARRAY:
        s = "ARRAY";
        break;
      case sym.ELSE:
        s = "ELSE";
        break;
      case sym.IF:
        s = "IF";
        break;
      case sym.OF:
        s = "OF";
        break;
      case sym.PROC:
        s = "PROC";
        break;
      case sym.REF:
        s = "REF";
        break;
      case sym.TYPE:
        s = "TYPE";
        break;
      case sym.VAR:
        s = "VAR";
        break;
      case sym.WHILE:
        s = "WHILE";
        break;
      case sym.LPAREN:
        s = "LPAREN";
        break;
      case sym.RPAREN:
        s = "RPAREN";
        break;
      case sym.LBRACK:
        s = "LBRACK";
        break;
      case sym.RBRACK:
        s = "RBRACK";
        break;
      case sym.LCURL:
        s = "LCURL";
        break;
      case sym.RCURL:
        s = "RCURL";
        break;
      case sym.EQ:
        s = "EQ";
        break;
      case sym.NE:
        s = "NE";
        break;
      case sym.LT:
        s = "LT";
        break;
      case sym.LE:
        s = "LE";
        break;
      case sym.GT:
        s = "GT";
        break;
      case sym.GE:
        s = "GE";
        break;
      case sym.ASGN:
        s = "ASGN";
        break;
      case sym.COLON:
        s = "COLON";
        break;
      case sym.COMMA:
        s = "COMMA";
        break;
      case sym.SEMIC:
        s = "SEMIC";
        break;
      case sym.PLUS:
        s = "PLUS";
        break;
      case sym.MINUS:
        s = "MINUS";
        break;
      case sym.STAR:
        s = "STAR";
        break;
      case sym.SLASH:
        s = "SLASH";
        break;
      case sym.IDENT:
        s = "IDENT '" + token.value + "'";
        break;
      case sym.INTLIT:
        s = "INTLIT " + token.value;
        break;
      default:
        /* this should never happen */
        throw new RuntimeException(
          "unknown token " + token.sym + " in showToken"
        );
    }
    System.out.println(
      "TOKEN = " + s +
      " in line " + token.left +
      ", column " + token.right
    );
  }

%}



%%


\/\/.*		{
		  /* comment: nothing returned */
		}

array		{
		  return symbol(sym.ARRAY);
		}

\{		{
		  return symbol(sym.LCURL);
		}

\}		{
		  return symbol(sym.RCURL);
		}

\'.\'		{
		  return symbol(sym.INTLIT,
		                (int) yytext().charAt(1));
		}

\'		{
		  throw new RuntimeException(
		    "illegal use of apostrophe" +
		    " in line " + (yyline + 1) +
		    ", column " + (yycolumn + 1)
		  );
		}

.		{
		  throw new RuntimeException(
		    "illegal character 0x" +
		    Integer.toString((int) yytext().charAt(0), 16) +
		    " in line " + (yyline + 1) +
		    ", column " + (yycolumn + 1)
		  );
		}
