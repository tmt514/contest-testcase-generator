
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

%token T_If T_Else T_Then T_Do T_While T_End T_Repeat
%token <charConstant> T_CharConstant

%union {
  char charConstant;
  int intConstant;
  bool boolConstant;
  double doubleConstant;
  char *stringConstant;
  char identifier[MaxIdentLen+1];

  std::vector<Variable *> *variableList;
  Variable *variable;
  Type *type;
  Constraint *constraint, *fullRangeConstraint;
  Formatting *formatting;
  std::vector<Node *> *stmtList;
  Node *node, *identOrChar;
  VariableNode *variableNode;
  RepeatExpr *repeatExpr;
  std::vector<RepeatExpr *> *repeatExprList;
}

%type <variableList> VariableList
%type <variable> Variable
%type <type> Type
%type <constraint> RangeConstraints
%type <fullRangeConstraint> FullRangeConstraint

%type <formatting> Formatting
%type <node> Stmt
%type <repeatExpr> RepeatExpr
%type <repeatExprList> RepeatExprList
%type <identOrChar> IdentOrChar
%type <stmtList> StmtList

%%

InputSpec : TypeDecl T_Delim Formatting T_Delim Constraints {
              fprintf(stderr, "HI!!!!!!\n");
              GeneratorProgram *gp = new GeneratorProgram();
              VerifierProgram *vp = new VerifierProgram();
              gp->setFormatting($3);
              gp->outputTo(gpFilename);
              vp->outputTo(vpFilename);
              printf("Input Format Correct!\n");
            }
          ;

/* --------------- Type Decl ------------------- */ 

TypeDecl : TypeDecl Decl { fprintf(stderr, "TypeDecl: DONE!\n"); }
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

Formatting : StmtList { $$ = new Formatting($1); }
           ;

StmtList : StmtList Stmt { ($$ = $1)->push_back($2); }
         | Stmt { ($$=new std::vector<Node*>())->push_back($1); }
         ;

Stmt       : T_Repeat RepeatExprList T_Do Formatting T_End { $$ = new RepeatNode($2, $4); }
           | IdentOrChar { $$ = $1; }
           ;

/*| T_If IfExpr T_Then T_Do Formatting T_End { $$ = new IfNode($2, $5); }
           | T_If IfExpr T_Then T_Do Formatting T_End T_Else T_Do Formatting T_End { $$ = new IfNode($2, $5, $9); } */

RepeatExprList : RepeatExpr { ($$ = new std::vector<RepeatExpr*>())->push_back($1); }
               | RepeatExprList ',' RepeatExpr { ($$=$1)->push_back($3); }
               ;

RepeatExpr : '$' Variable { $$ = new RepeatExpr(new VariableExpr($2, false)); }
           ;

IdentOrChar : T_CharConstant { fprintf(stderr, ">>>>>> here %c\n", $1); $$ = new CharNode($1); }
            | Variable { fprintf(stderr, ">>>>>>> there %s\n", $1->name); $$ = new VariableNode($1); }
            ;

/* -------------- Constraints -------------------- */
Constraints :
            ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}
