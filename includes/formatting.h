#ifndef _FORMATTING_H_
#define _FORMATTING_H_

#include <cstdio>

#define MaxIdentLen 31

#include "parser.hh"

extern char *yytext;

int yylex();
void yyerror(const char *s);


#endif
