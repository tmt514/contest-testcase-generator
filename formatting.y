
%{
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

  std::vector<Variable *> *variableList;
  Variable *variable;
  Type *type;
  Constraint *constraint, *fullRangeConstraint;
}

%type <variableList> VariableList
%type <variable> Variable
%type <type> Type
%type <constraint> RangeConstraints
%type <fullRangeConstraint> FullRangeConstraint

%%

InputSpec : TypeDecl T_Delim Formatting T_Delim Constraints {
              fprintf(stderr, "HI!!!!!!\n");
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

VarDecl : VariableList ':' Type                           {
          //assign all variable in the list to that type
            ($3)->dumpDebug();
            fprintf(stderr, "list size = %d\n", (int)$1->size());
            for (int i = 0; i < (int)($1->size()); i++) {
              fprintf(stderr, "list item = %p\n", (*$1)[i]);
              (*$1)[i]->dumpDebug();
              (*$1)[i]->assignToType($3);
            }
          }
        | VariableList ':' Type '(' RangeConstraints ')'  {
          //assign all variable in the list to that type
          //TODO: apply constraints
            for (int i = 0; i < (int)($1->size()); i++) {
              (*$1)[i]->assignToType($3);
            }
          }
        ;

VariableList : Variable                   { ($$ = new std::vector<Variable*>())->push_back($1); }
             | VariableList ',' Variable  { ($$ = $1)->push_back($3); }
             ;

RangeConstraints : { $$ = NULL; }
                 ;
FullRangeConstraint : { $$ = NULL; }
                    ;

Variable : T_Identifier { $$ = Variable::DeclareNewVariable($1); }
         | T_Identifier '[' FullRangeConstraint ']' {
                $$ = Variable::DeclareNewVariable($1);
                //TODO add constraint
              }
         ;

Type : T_Int      { $$ = IntType::intType; }
     | T_Double   { $$ = DoubleType::doubleType; }
     | T_String   { $$ = new IntType("string"); }
     | T_Grid     { $$ = new IntType("grid"); }
     | Type T_Dim { $$ = new IntType("array"); }
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
