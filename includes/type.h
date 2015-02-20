#ifndef _TYPE_H_
#define _TYPE_H_

#include <vector>
#include <cstdio>
#include <cstring>
#include "variable.h"
#include "constraint.h"

class Type
{
  protected:
    bool isDeclared;
    char *typeName;
    std::vector<Variable *> setOfVariables;

  public:
    Type(const char *str);
    //Declare the type if not primitive
    virtual void dumpDecl(FILE *out) = 0;
    //Must initialize data also
    virtual void dumpVariableDecl(FILE *out, Variable &var) = 0;
    // type gen()
    virtual void genGenOneFunc(FILE *out, Constraint &c) = 0;
    // var = gen();
    virtual void genGenOneAndAssign(FILE *out, Variable &var, Constraint &c) = 0;
    //register this variable to the set
    void addVariable(Variable *var) { setOfVariables.push_back(var); } 
    void dumpDebug() { fprintf(stderr, "dumpDebug for type %s\n", typeName); }
};

class PrimitiveType : public Type
{
  public:
    PrimitiveType(const char *str) : Type(str) {}
    virtual void genGenOneCode(FILE *out, Constraint &c) = 0;
    void genGenOneFunc(FILE *out, Constraint &c);
    void genGenOneAndAssign(FILE *out, Variable &var, Constraint &c);
    void dumpDecl(FILE *out);
    void dumpVariableDecl(FILE *out, Variable &var);
};

class IntType : public PrimitiveType
{
  public:
    static IntType *intType;
    IntType(const char *str) : PrimitiveType(str) {}
    void genGenOneCode(FILE *out, Constraint &c);
};

class DoubleType : public PrimitiveType
{
  public:
    static DoubleType *doubleType;
    DoubleType(const char *str) : PrimitiveType(str) {}
    void genGenOneCode(FILE *out, Constraint &c);
};

/*
class StringType : public Type
{
  public:
    static StringType *stringType;
};

class ArrayType : public Type
{
  protected:
    Type *arrayElementType;

  public:
    static ArrayType *intArrayType, *doubleArrayType;
    Type(const char *str, Type *innerType);
};

class ParameteredType : public Type
{
  proected:
    std::vector<Variable *> parameters;

  public:
    Type(const char *str, std::vector<Variable *> &params);
};

class GridType : public ParameteredType
{
  protected:
    Type *gridElementType;

  public:
    static GridType *charGridType, *intGridType;
};

*/

#endif /* _TYPE_H_ */
