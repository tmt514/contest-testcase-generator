#ifndef _GENERATOR_PROGRAM_H_
#define _GENERATOR_PROGRAM_H_

#include <cstdio>
#include <string>
#include "macro.h"
#include "variable.h"
#include "type.h"
#include "constraint.h"
#include "ast.h"

#define LIB_DIR "./lib"
#define SRC_DIR "./src"
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)

class GeneratorProgram {
  public:
    void outputTo(const std::string &);
    void setFormatting(Formatting *);
  private:
    FILE *program;
    Formatting *formatting;

    void dumpHeader();
    void dumpUserCodeDecl();
    void dumpVarDecl();
    void genCode();
    void dumpMain();
    void dumpUserCode();
};

#endif
