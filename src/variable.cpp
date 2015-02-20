#include "variable.h"

std::map<std::string, Variable *> *Variable::variablePool = new std::map<std::string, Variable *>();

/* Variable::DeclareNewVariable()
 * ------------------------------
 *  Check if the name is allowable
 *  and then return a new-created variable address
 */
Variable* Variable::DeclareNewVariable(const char *name) {
  Variable *var;
  fprintf(stderr, "name=%s\n", name);
  if (Variable::variablePool->count(name)) {
    fprintf(stderr, "Already used name!!!\n");
    var = (*Variable::variablePool)[name];
  } else {
    var = new Variable(name);
    fprintf(stderr, "Created new variable!!!\n");
    (*Variable::variablePool)[name] = var;
  }
  return var;
}

/* Variable::Variable()
 * --------------------
 *  constructor
 */
Variable::Variable(const char *str) {
  fprintf(stderr, "Create new variable %s\n", str);
  int n = strlen(str) + 1;
  name = new char[n];
  strncpy(name, str, n);
  type = NULL;
}

/* Variable::assignToType()
 * ------------------------
 *  give a type to that variable
 */
void Variable::assignToType(Type *t) {
  type = t;
}

/* Variable::dumpDecl()
 * --------------------
 *  output declaration for this specific variable
 *  TODO: how to specify local variable or?
 */
void Variable::dumpDecl(FILE *out) {
  if (type == NULL) {
    fprintf(stderr, "Unknown Type!");
  } else {
    type->dumpVariableDecl(out, *this);
  }
}

