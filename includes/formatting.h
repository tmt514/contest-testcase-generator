#ifndef _FORMATTING_H_
#define _FORMATTING_H_

#include <cstdio>
#include <string>
#include <vector>

#define MaxIdentLen 31

#include "variable.h"
#include "type.h"
#include "constraint.h"
#include "parser.hh"

extern char *yytext;

int yylex();
void yyerror(const char *s);


#endif
