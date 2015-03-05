#ifndef __AST_H_
#define __AST_H_

/* Nothing at all. */

#include <cstdio>
#include <vector>

class RepeatExpr;
class Expr;

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
    Type *type;
  public:
    Expr() : Node() { type = NULL; }
    virtual void genGenOneCode(FILE *out, int indentation) = 0;
    virtual void getAllVariableInvolved(VARLIST &varList) = 0;
    virtual Type* getType() = 0;
};

class RootExpr : public Expr {
  protected:
    Expr *expr;
  public:
    RootExpr(Expr *_expr) : Expr(), expr(_expr) {}
    void genGenOneCode(FILE *out, int indentation);
    void getAllVariableInvolved(VARLIST &varList);
    Type* getType();
};

class VariableExpr : public Expr {
  protected:
    Variable *var;
    bool needRegenerate;
  public:
    VariableExpr(Variable *_var, bool _regen) : Expr(), var(_var), needRegenerate(_regen) {}
    void genGenOneCode(FILE *out, int indentation);
    void getAllVariableInvolved(VARLIST &varList);
    Type* getType();
};

class LazyExpr : public Expr {
  protected:
    const char *str;
  public:
    LazyExpr(const char *_str) : Expr(), str(_str) {}
    void genGenOneCode(FILE *out, int indentation);
    void getAllVariableInvolved(VARLIST &varList);
    Type* getType();
};

class CompoundOperator : public Node {
  protected:
    const char *op;
  public:
    CompoundOperator(const char *_op) : op(_op) {}
    void genGenOneCode(FILE *out, int indentation);
};

class CompoundExpr : public Expr {
  protected:
    Expr *left, *right;
    CompoundOperator *op;
  public:
    CompoundExpr(Expr *_left, CompoundOperator *_op, Expr *_right) : Expr(), left(_left), right(_right), op(_op) {}
    void genGenOneCode(FILE *out, int indentation);
    void getAllVariableInvolved(VARLIST &varList);
    Type* getType();
};

class IntConstantExpr : public Expr {
  protected:
    int val;
  public:
    IntConstantExpr(int _val) : Expr(), val(_val) {}
    void genGenOneCode(FILE *out, int indentation);
    void getAllVariableInvolved(VARLIST &varList) {}
    Type* getType();
};


/* ================ Constraint ================= */


#endif
