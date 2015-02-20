%{
#include "formatting.h"
%}

 /* Definitions, copied & modified from Compiler homework pp2 */
DIGIT             ([0-9])
HEX_DIGIT         ([0-9a-fA-F])
HEX_INTEGER       (0[Xx]{HEX_DIGIT}+)
INTEGER           ({DIGIT}+)
EXPONENT          ([Ee][-+]?{INTEGER})
DOUBLE            ({INTEGER}"."{DIGIT}*{EXPONENT}?)
BEG_STRING        (\"[^"\n]*)
STRING            ({BEG_STRING}\")
IDENTIFIER        ([A-Za-z_][A-Za-z0-9_]*)
OPERATOR          ([-+/*%=.,;!<>()[\]{}])
BEG_COMMENT       ("/*")
END_COMMENT       ("*/")
SINGLE_COMMENT    ("//"[^\n]*)


%s FORMATTING CONDITION

%%

<INITIAL>"###"          { BEGIN(FORMATTING);
                          return T_Delim; }
<FORMATTING>"###"       { BEGIN(CONDITION);
                          return T_Delim; }


 /* Primitive types, specialized for testcases */
int|integer  { return T_Int; }
double|float { return T_Double; }
string       { return T_String; }
grid         { return T_Grid; }
tree         { return T_Tree; }
graph        { return T_Graph; }

 /* Comparson, relational, dimension tokens */
"[]" { return T_Dim; }
"<=" { return T_LessEqual; }
">=" { return T_GreaterEqual; }
"==" { return T_Equal; }
"!=" { return T_NotEqual; }

{IDENTIFIER} { strncpy(yylval.identifier, yytext, MaxIdentLen-1);
               yylval.identifier[MaxIdentLen-1] = 0;
               return T_Identifier;
             }
{INTEGER} { yylval.intConstant = atoi(yytext);
            return T_IntConstant;
          }
{DOUBLE} { yylval.doubleConstant = atof(yytext);
           return T_DoubleConstant;
         }

[ \t] { /* Skip all whitespaces */ }
\n { /* Skip all change lines */ }

. { return yytext[0]; }

%%

int yywrap() {
  return 1;
}
