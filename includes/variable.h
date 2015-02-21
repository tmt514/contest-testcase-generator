#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <cstdio>
#include <cstring>
#include <map>
#include <string>

class Type;

class Variable
{
  public:
    static std::map<std::string, Variable *> *variablePool;
    static Variable* DeclareNewVariable(const char *str);
    char *name;
    Type *type;

    Variable(const char *str);
    void assignToType(Type *t);
    // int n;
    void dumpDecl(FILE *out, int indentation);
    // n
    void dumpUse(FILE *out);
    // printf("%d\n", n);
    void dumpPrint(FILE *out, int indentation);
    // n = rand()%100;
    void dumpGenOne(FILE *out, int indentation);
    // void genN()
    void dumpGenOneFunc(FILE *out);

    // for debugging
    void dumpDebug() { fprintf(stderr, "dump Variable Info: %s (%p)\n", name, type); }

};

#include "type.h"

#endif /* _VARIABLE_H_ */
