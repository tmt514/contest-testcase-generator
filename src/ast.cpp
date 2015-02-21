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

}
