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


%x FORMATTING CONDITION
%x CODESEG

%%

<INITIAL>"###"          { BEGIN(FORMATTING);
                          return T_Delim; }
<FORMATTING>"###"       { fprintf(stderr, "HERE!!!####\n"); BEGIN(CONDITION);
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

<INITIAL,CONDITION>{INTEGER} { yylval.intConstant = atoi(yytext);
            return T_IntConstant;
          }
<INITIAL,CONDITION>{DOUBLE} { yylval.doubleConstant = atof(yytext);
           return T_DoubleConstant;
         }

<INITIAL,CONDITION>[ \t] { /* Skip all whitespaces */ }
<INITIAL,CONDITION>"\n" { /* Skip all change lines */ }

<FORMATTING>{CODE_SEGMENT} { BEGIN(CODESEG); }
<CODESEG>"\n" { unput('\n'); BEGIN(FORMATTING); }
<CODESEG>"REPEAT"|"repeat"   { return T_Repeat; }
<CODESEG>"DO"|"do"           { return T_Do; }
<CODESEG>"END"|"end"         { return T_End; }
<CODESEG>"IF"|"if"           { return T_If; }
<CODESEG>"THEN"|"then"       { return T_Then; }
<CODESEG>"ELSE"|"else"       { return T_Else; }
<CODESEG>"WHILE"|"while"     { return T_While; }
<CODESEG>.          { return yytext[0]; }

<*>{IDENTIFIER} { strncpy(yylval.identifier, yytext, MaxIdentLen);
               yylval.identifier[MaxIdentLen] = 0;
               return T_Identifier;
             }

<FORMATTING>"$"     { return '$'; }
<FORMATTING>"\\\n"  { /* Skip line break */ }
<FORMATTING>"\\$"   { yylval.charConstant = yytext[1]; return T_CharConstant; }
<FORMATTING>"\n"    { yylval.charConstant = yytext[0]; return T_CharConstant; }
<FORMATTING>.       { yylval.charConstant = yytext[0]; return T_CharConstant; }

<*>. { return yytext[0]; }

%%

int yywrap() {
  return 1;
}
