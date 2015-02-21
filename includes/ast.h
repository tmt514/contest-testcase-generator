#ifndef __AST_H_
#define __AST_H_

/* Nothing at all. */

#include <cstdio>
#include <vector>
#include "macro.h"
#include "variable.h"
#include "type.h"
#include "constraint.h"

class Node {
  public:
    Node() {}
    virtual void genGenOneCode(FILE *out, int indentation) = 0;
};

class Formatting : public Node {
  protected:
    std::vector<Node *> *children;
  public:
    Formatting(std::vector<Node *> *_children) : children(_children) {}
    void genGenOneCode(FILE *out, int indentation);
};

class CharNode : public Node {
  protected:
    char c;
  public:
    CharNode(char _c) : c(_c) {}
    void genGenOneCode(FILE *out, int indentation);
};

class VariableNode : public Node {
  protected:
    Variable *var;
  public:
    VariableNode(Variable *_var) : var(_var) {}
    void genGenOneCode(FILE *out, int indentation);
    Variable* getVariable();
};

class VariableUseNode : public VariableNode {
  public:
    VariableUseNode(Variable *_var) : VariableNode(_var) {}
    void genGenOneCode(FILE *out, int indentation);
};

class RepeatNode : public Node {
  protected:
    VariableNode *expr;
    Formatting *stmt;
  public:
    RepeatNode(VariableNode *_expr, Formatting *_stmt) : expr(_expr), stmt(_stmt) {}
    void genGenOneCode(FILE *out, int indentation);
    Variable* getVariable();
};

#endif
