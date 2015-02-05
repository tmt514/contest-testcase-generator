#ifndef _FORMATTING_H_
#define _FORMATTING_H_

#include <cstdio>

enum TokenTypes {
  T_Void = 1024,
  T_Integer,
  T_Line
};

extern char *yytext;

int yylex();

void yyerror(const char *str);
{
  fprintf(stderr,"error: %s\n",str);
}

#endif
