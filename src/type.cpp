#include "type.h"
#include "util.h"

int Type::ID = 0;
IntType *IntType::intType = new IntType("int");
DoubleType *DoubleType::doubleType = new DoubleType("double");

Type::Type(const char *str) {
  id = ++Type::ID;
  typeName = strdup(str);
  hasGenOneFunc = std::set<int>();
  /*
  int n = strlen(str);
  typeName = new char[n+1];
  // TODO: Error protection
  strncpy(typeName, str, n+1);*/
}

/* PrimitiveType::dumpDecl()
 * -------------------------
 *  we don't need any declaration for C/C++ primitive types
 */
void PrimitiveType::dumpDecl(FILE *out) {
}

/* PrimitiveType::dumpVariableDecl()
 * ----------------------------
 */
void PrimitiveType::dumpVariableDecl(FILE *out, int indentation, Variable &var) {
  Utility::PrintIndentation(out, indentation);
  fprintf(out, "%s %s;\n", typeName, var.name); 
}

/* PrimitiveType::genGenOneFunc()
 * ------------------------------
 */
void PrimitiveType::genGenOneFunc(FILE *out, Constraint *c) {
  int cid = 0;
  if (c != NULL) {
    cid = c->getID();
  }
  
  if (hasGenOneFunc.count(cid)) return;
  hasGenOneFunc.insert(cid);

  fprintf(out, "%s gen_T%d_C%d() {\n", typeName, id, cid);
  //fprintf(out, "%s genUserType%s() {\n", typeName, typeName);
  genGenOneCode(out, 1, c);
  fprintf(out, "  return value;\n");
  fprintf(out, "}\n\n");
}

/* PrimitiveType::genGenOneAndAssign()
 * -----------------------------------
 */
void PrimitiveType::genGenOneAndAssign(FILE *out, int indentation, Variable &var, Constraint *c) {

  int cid = 0;
  if (c != NULL) {
    cid = c->getID();
  }
  //TODO: check constraints
  Utility::PrintIndentation(out, indentation);
  fprintf(out, "%s = gen_T%d_C%d();\n", var.name, id, cid);
  //fprintf(out, "%s = genUserType%s();\n", var.name, typeName);
}

/* IntType::genGenOneCode()
 * ------------------------
 */
void IntType::genGenOneCode(FILE *out, int indentation, Constraint *c) {
  //TODO: check constraints
  Utility::PrintIndentation(out, indentation);
  fprintf(out, "int value = rand();\n");
}

/* IntType::genPrintOne()
 * ----------------------
 */
void IntType::genPrintOne(FILE *out, int indentation, Variable &var, Constraint *c) {
  Utility::PrintIndentation(out, indentation);
  fprintf(out, "printf(\"%%d\", %s);\n", var.name);
}

/* DoubleType::genGenOneCode()
 * ---------------------------
 */
void DoubleType::genGenOneCode(FILE *out, int indentation, Constraint *c) {
  //FIXME
  Utility::PrintIndentation(out, indentation);
  fprintf(out, "double value = rand() / (double)RAND_MAX;\n");
}

/* DoubleType::genPrintOne()
 * -------------------------
 */
void DoubleType::genPrintOne(FILE *out, int indentation, Variable &var, Constraint *c) {
  Utility::PrintIndentation(out, indentation);
  fprintf(out, "printf(\"%%.6f\", %s);\n", var.name);
}
