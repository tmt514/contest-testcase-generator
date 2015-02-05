%{
#include "formatting.h"
%}

%%

[0-9]* { return T_Integer; }
[^\n]*\n { return T_Line; }

%%

