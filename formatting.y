
%{
#include "formatting.h"
%}

%token INTEGER
%token LINE

%%

line: LINE { printf("line!\n"); }
    ;

%%
