#include "type.h"

IntType *IntType::intType = new IntType("int");
DoubleType *DoubleType::doubleType = new DoubleType("double");

Type::Type(const char *str) {
  int n = strlen(str);
  typeName = new char[n+1];
  // TODO: Error protection
  strncpy(typeName, str, n+1);
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
void PrimitiveType::dumpVariableDecl(FILE *out, Variable &var) {
  fprintf(out, "%s %s;\n", typeName, var.name); 
}

/* PrimitiveType::genGenOneFunc()
 * ------------------------------
 */
void PrimitiveType::genGenOneFunc(FILE *out, Constraint &c) {
  fprintf(out, "%s genUserType%s() {\n", typeName, typeName);
  genGenOneCode(out, c);
  fprintf(out, "  return value;\n");
  fprintf(out, "}\n\n");
}

/* PrimitiveType::genGenOneAndAssign()
 * -----------------------------------
 */
void PrimitiveType::genGenOneAndAssign(FILE *out, Variable &var, Constraint &c) {
  //TODO: check constraints
  fprintf(out, "%s = genUserType%s();\n", var.name, typeName);
}

/* IntType::genGenOneCode()
 * ------------------------
 */
void IntType::genGenOneCode(FILE *out, Constraint &c) {
  //TODO: check constraints
  fprintf(out, "int value = rand();\n");
}

/* DoubleType::genGenOneCode()
 * ---------------------------
 */
void DoubleType::genGenOneCode(FILE *out, Constraint &c) {
  //FIXME
  fprintf(out, "double value = rand() / (double)RAND_MAX;\n");
}
