#ifndef __AST_H_
#define __AST_H_

/* Nothing at all. */

#include <cstdio>
#include <vector>
#include "macro.h"
#include "variable.h"
#include "type.h"
#include "constraint.h"

class RepeatExpr;
class Expr;

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
    std::vector<RepeatExpr *> *exprList;
    Formatting *stmt;
  public:
    RepeatNode(std::vector<RepeatExpr *> *_expr, Formatting *_stmt) : exprList(_expr), stmt(_stmt) {}
    void genGenOneCode(FILE *out, int indentation);
}; 

class RepeatExpr : public Node {
  protected:
    Expr *expr;
    Variable *idx;
  public:
    RepeatExpr(Expr *_expr);
    RepeatExpr(Expr *_expr, Variable *var) : expr(_expr), idx(var) {}
    void genGenOneCode(FILE *out, int indentation);
    void genGenOneCodeBegin(FILE *out, int indentation);
    void genGenOneCodeEnd(FILE *out, int indentation);
};

/* =============== Expr ================= */

typedef std::vector<Variable *> VARLIST;

class Expr : public Node {
  protected:
    
  public:
    Expr() : Node() {}
    virtual void genGenOneCode(FILE *out, int indentation) = 0;
    virtual void getAllVariableInvolved(VARLIST &varList) = 0;
};

class VariableExpr : public Expr {
  protected:
    Variable *var;
    bool needRegenerate;
  public:
    VariableExpr(Variable *_var, bool _regen) : var(_var), needRegenerate(_regen) {}
    void genGenOneCode(FILE *out, int indentation);
    void getAllVariableInvolved(VARLIST &varList);
};


#endif
