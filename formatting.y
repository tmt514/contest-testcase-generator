
%{
#include <string>
#include "formatting.h"

#include "generator_program.h"
#include "verifier_program.h"

std::string gpFilename, vpFilename;
%}

%token T_Delim
%token T_Int T_Double T_String T_Grid T_Graph T_Tree
%token T_Dim T_LessEqual T_GreaterEqual T_Equal T_NotEqual
%token <identifier> T_Identifier
%token <intConstant> T_IntConstant
%token <doubleConstant> T_DoubleConstant

%union {
  int intConstant;
  bool boolConstant;
  double doubleConstant;
  char *stringConstant;
  char identifier[MaxIdentLen+1];
}

%%

InputSpec : TypeDecl T_Delim Formatting T_Delim Constraints {
              GeneratorProgram *gp = new GeneratorProgram();
              VerifierProgram *vp = new VerifierProgram();
              gp->outputTo(gpFilename);
              vp->outputTo(vpFilename);
              printf("Input Format Correct!\n");
            }
          ;

/* --------------- Type Decl ------------------- */ 

TypeDecl : TypeDecl Decl {}
         | {}
         ;

/* Declaration of variables, currently allow variable declaration. */
Decl : VarDecl {}
     ;

VarDecl : VariableList ':' Type                           {}
        | VariableList ':' Type '(' RangeConstraints ')'  {}
        ;

VariableList : Variable                   {}
             | VariableList ',' Variable  {}
             ;

RangeConstraints : {}
                 ;
FullRangeConstraint : {}
                    ;

Variable : T_Identifier {}
         | T_Identifier '[' FullRangeConstraint ']' {}
         ;

Type : T_Int      {}
     | T_Double   {}
     | T_String   {}
     | T_Grid     {}
     | Type T_Dim {}
     ;

/* -------------- Formatting Languages ------------------ */
Formatting :
           ;


/* -------------- Constraints -------------------- */
Constraints :
            ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "%s\n", s);
}
