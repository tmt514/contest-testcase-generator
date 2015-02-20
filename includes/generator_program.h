#ifndef _GENERATOR_PROGRAM_H_
#define _GENERATOR_PROGRAM_H_

#include <cstdio>
#include <string>
#include "macro.h"
#include "variable.h"
#include "type.h"
#include "constraint.h"

#define LIB_DIR "./lib"
#define SRC_DIR "./src"
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)

class GeneratorProgram {
  public:
    void outputTo(const std::string &);
  private:
    FILE *program;
    void dumpHeader();
    void dumpUserCodeDecl();
    void dumpVarDecl();
    void genCode();
    void dumpMain();
    void dumpUserCode();
};

#endif
