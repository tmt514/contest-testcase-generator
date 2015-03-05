#include "ast.h"
#include "util.h"

/* ==================== Formatting =================== */

/* Formatting::genGenOneCode()
 * ---------------------------
 *  output the whole tree
 */
void Formatting::genGenOneCode(FILE *out, int indentation) {
  FOR(it, children) {
    (*it)->genGenOneCode(out, indentation);
  }
}

 
/* ==================== CharNode =================== */

/* CharNode::genGenOneCode()
 * -------------------------
 *  just print print that character
 */
void CharNode::genGenOneCode(FILE *out, int indentation) {
  fprintf(stderr, "CharNode::genGenOneCode()\n");
  Utility::PrintIndentation(out, indentation);
  fprintf(out, "putchar(%d);\n", (int)c);
}

/* ==================== VariableNode ================== */

/* VariableNode::genGenOneCode()
 * -----------------------------
 */
void VariableNode::genGenOneCode(FILE *out, int indentation) {
  var->dumpGenOne(out, indentation);
  var->dumpPrint(out, indentation);
}

/* VariableNode::getVariable()
 * ---------------------------
 */
Variable* VariableNode::getVariable() {
  return var;
}

/* ==================== VariableUseNode ================== */

/* VariableUseNode::genGenOneCode()
 * -----------------------------
 */
void VariableUseNode::genGenOneCode(FILE *out, int indentation) {
  var->dumpPrint(out, indentation);
}

/* ==================== RepeatNode ================= */

/* RepeatNode::genGenOneCode()
 * ---------------------------
 */
void RepeatNode::genGenOneCode(FILE *out, int indentation) {
  int depth = 0;
  FOR(it, exprList) {
    (*it)->genGenOneCodeBegin(out, indentation + depth);
    depth++;
  }
  stmt->genGenOneCode(out, indentation + depth);
  FOR(it, exprList) {
    --depth;
    (*it)->genGenOneCodeEnd(out, indentation + depth);
  }
}

/* ==================== RepeatExpr ================= */

/* RepeatExpr::RepeatExpr()
 * ------------------------
 *  automatically define index
 */
RepeatExpr::RepeatExpr(Expr *_expr) : expr(_expr) {
  static int cnt = 0;
  char name[10];
  ++cnt;
  sprintf(name, "_idx%02d", cnt);
  idx = Variable::DeclareNewVariable(name);
  idx->assignToType(IntType::intType);
  fprintf(stderr, "DECLARE NEW INDEX VARIABLE %s\n", name);
}

/* RepeatExpr::genGenOneCode()
 * ---------------------------
 *  I don't know what to do with this. (useful?)
 */
void RepeatExpr::genGenOneCode(FILE *out, int indentation) {
  fprintf(stderr, "ERROR! DONT USE THIS FUNCTION!");
}

/* RepeatExpr::genGenOneCodeBegin()
 * --------------------------------
 *  generate a simple for loop
 */
void RepeatExpr::genGenOneCodeBegin(FILE *out, int indentation) {
  Utility::PrintIndentation(out, indentation);
  fprintf(out, "for(%s = 0; %s < (", idx->name, idx->name);
  expr->genGenOneCode(out, indentation);
  fprintf(out, "); %s++) {\n", idx->name);
}

/* RepeatNode::genGenOneCodeEnd()
 * ------------------------------
 *  generate end of a loop
 */
void RepeatExpr::genGenOneCodeEnd(FILE *out, int indentation) {
  Utility::PrintIndentation(out, indentation);
  fprintf(out, "}\n");
}

/* ==================== RootExpr ==================== */

/* RootExpr::genGenOneCode()
 * ---------------------------
 *  this method will print a print method to print the expression
 *  in order to know how to print, we must know the type of expr first.
 */
void RootExpr::genGenOneCode(FILE *out, int indentation) {
  //fprintf(stderr, "!!!RootExpr::genGenOneCode() Not Done Yet\n");
  //TODO
  type = getType();
  if (type) {
    type->genPrintExpr(out, indentation, expr);
  }
}

/* RootExpr::getAllVariableInvolved()
 * -----------------------------------
 */
void RootExpr::getAllVariableInvolved(VARLIST &varList) {
  expr->getAllVariableInvolved(varList);
}

/* RootExpr::getType()
 * --------------------
 */
Type* RootExpr::getType() {
  if (type) return type;
  type = expr->getType();
  return type;
}


/* ==================== VariableExpr ================== */

/* VariableExpr::genGenOneCode()
 * -----------------------------
 */
void VariableExpr::genGenOneCode(FILE *out, int indentation) {
  fprintf(out, "%s", var->name);
}

/* VariableExpr::getAllVariableInvolved()
 * --------------------------------------
 *  This is for repeat expression to use, retrieve all
 *  variable involved first, and re-genernate one if necessary.
 */
void VariableExpr::getAllVariableInvolved(VARLIST &varList) {
  varList.push_back(var);
}

/* VariableExpr::getType()
 * ------------------------
 *  same as the variable's type
 */
Type* VariableExpr::getType() {
  if (type) return type;
  type = var->type;
  return type;
}

/* ==================== LazyExpr ================== */

/* LazyExpr::genGenOneCode()
 * -------------------------
 *  Just print out the string
 */
void LazyExpr::genGenOneCode(FILE *out, int indentation) {
  fprintf(out, "%s", str);
}

/* LazyExpr::getAllVariableInvolved()
 * ----------------------------------
 *  just do nothing
 */
void LazyExpr::getAllVariableInvolved(VARLIST &varList) {
}

/* LazyExpr::getType()
 * -------------------
 *  return NULL
 */
Type* LazyExpr::getType() {
  return NULL;
}

/* ==================== CompoundExpr ==================== */

/* CompoundExpr::genGenOneCode()
 * -----------------------------
 */
void CompoundExpr::genGenOneCode(FILE *out, int indentation) {
  // TODO: what about graph * graph? string xor string? define functions?
  if (left) {
    fprintf(out, "(");
    left->genGenOneCode(out, indentation);
    fprintf(out, ")");
  }
  if (op) op->genGenOneCode(out, indentation);
  if (right) {
    fprintf(out, "(");
    right->genGenOneCode(out, indentation);
    fprintf(out, ")");
  }
}

/* CompoundExpr::getAllVariableInvolved()
 * --------------------------------------
 *  just recursively call
 */
void CompoundExpr::getAllVariableInvolved(VARLIST &varList) {
  left->getAllVariableInvolved(varList);
  right->getAllVariableInvolved(varList);
}

/* CompoundExpr::getType()
 * -----------------------
 *  needs auto detect the return type
 */
Type* CompoundExpr::getType() {
  //TODO: comparability
  if (type) return type;
  if (left->getType() == right->getType())
    type = left->getType();
  return type;
}

/* ================= CompoundOperator ================= */

/* CompoundOperator::genGenOneCode()
 * ---------------------------------
 */
void CompoundOperator::genGenOneCode(FILE *out, int indentation) {
  //TODO: this should be deprecated, we must use functions for non-primitive operators
  fprintf(out, "%s", op);
}

/* ================= IntConstantExpr ================== */

/* IntConstantExpr::genGenOneCode()
 * --------------------------------
 */
void IntConstantExpr::genGenOneCode(FILE *out, int indentation) {
  fprintf(out, "%d", val);
}

/* IntConstantExpr::getType()
 * --------------------------
 */
Type* IntConstantExpr::getType() {
  return IntType::intType;
}
