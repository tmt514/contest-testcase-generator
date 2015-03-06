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

 /* for FORMATTING part */
CODE_SEGMENT      ("\n- ")
CODE_INJECT       ("\n-- ")
CODE_INJECT_BLOCK_BEGIN ("%{")
CODE_INJECT_BLOCK_END   ("%}")
LAZY_EXPR         ("${"[^}]*"}")


%x FORMATTING CONDITION FORMATEXPR
%x CODESEG CODEINJ CODEIJB

%%

<*>"\r"                 { /* ignore all carrage return */ }

<INITIAL>"###"          { BEGIN(FORMATTING);
                          return T_Delim; }
<FORMATTING>"###"       { BEGIN(CONDITION);
                          return T_Delim; }

 /* Primitive types, specialized for testcases */
<INITIAL,CONDITION>int|integer  { return T_Int; }
<INITIAL,CONDITION>double|float { return T_Double; }
<INITIAL,CONDITION>string       { return T_String; }
<INITIAL,CONDITION>grid         { return T_Grid; }
<INITIAL,CONDITION>tree         { return T_Tree; }
<INITIAL,CONDITION>graph        { return T_Graph; }

 /* Comparson, relational, dimension tokens */
<*>"[]" { return T_Dim; }
<*>"<=" { return T_LessEqual; }
<*>">=" { return T_GreaterEqual; }
<*>"==" { return T_Equal; }
<*>"!=" { return T_NotEqual; }

<INITIAL,FORMATEXPR,CODESEG,CONDITION>{INTEGER} { yylval.intConstant = atoi(yytext);
            return T_IntConstant;
          }
<INITIAL,FORMATEXPR,CODESEG,CONDITION>{DOUBLE} { yylval.doubleConstant = atof(yytext);
           return T_DoubleConstant;
         }

<INITIAL,CODESEG,CONDITION>[ \t] { /* Skip all whitespaces */ }
<INITIAL,CONDITION>"\n" { /* Skip all change lines */ }

<FORMATTING>{CODE_SEGMENT} { BEGIN(CODESEG); }
<FORMATTING>{CODE_INJECT} { BEGIN(CODEINJ); }
<FORMATTING>{CODE_INJECT_BLOCK_BEGIN} { BEGIN(CODEIJB); }
<CODESEG,CODEINJ>"\n" { unput('\n'); BEGIN(FORMATTING); }
<CODEIJB>{CODE_INJECT_BLOCK_END} { BEGIN(FORMATTING); }
<CODESEG>"REPEAT"|"repeat"   { return T_Repeat; }
<CODESEG>"DO"|"do"           { return T_Do; }
<CODESEG>"END"|"end"         { fprintf(stderr, "END!\n"); return T_End; }
<CODESEG>"IF"|"if"           { return T_If; }
<CODESEG>"THEN"|"then"       { return T_Then; }
<CODESEG>"ELSE"|"else"       { return T_Else; }
<CODESEG>"WHILE"|"while"     { return T_While; }
<CODEINJ,CODEIJB>.          { yylval.charConstant = yytext[0]; return T_CharConstant; }

<*>{IDENTIFIER} { strncpy(yylval.identifier, yytext, MaxIdentLen);
               yylval.identifier[MaxIdentLen] = 0;
               return T_Identifier;
             }

<CODESEG>{LAZY_EXPR}  { yylval.stringConstant = strndup(yytext+2, strlen(yytext)-3); return T_LazyExpr; }
<CODESEG>.          { return yytext[0]; }
<FORMATTING>"$"     { return '$'; }
<FORMATTING>"${"    { BEGIN(FORMATEXPR); return T_FormatExprBegin; }
<FORMATEXPR>"}"     { BEGIN(FORMATTING); return T_FormatExprEnd; }
<FORMATTING>"\\\n"  { /* Skip line break */ }
<FORMATTING>"\\$"   { yylval.charConstant = yytext[1]; return T_CharConstant; }
<FORMATTING>"\n"    { yylval.charConstant = yytext[0]; return T_CharConstant; }
<FORMATTING>"\\{"   { yylval.charConstant = yytext[0]; return T_CharConstant; }
<FORMATTING>"\\}"   { yylval.charConstant = yytext[0]; return T_CharConstant; }
<FORMATTING>.       { yylval.charConstant = yytext[0]; return T_CharConstant; }

<*>. { fprintf(stderr, "READ [%c]\n", yytext[0]); return yytext[0]; }

%%

int yywrap() {
  return 1;
}
