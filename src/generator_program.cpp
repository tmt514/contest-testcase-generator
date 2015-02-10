#include "generator_program.h"

void GeneratorProgram::outputTo(const std::string &filename) {

  fprintf(stderr, "Generator Program receive filename = %s\n", filename.c_str());
  
  program = fopen(filename.c_str(), "w");

  dumpHeader();
  dumpUserCodeDecl();
  dumpVarDecl();
  genCode();
  dumpMain();
  dumpUserCode();

  fclose(program);
}

/* GeneratorProgram::dumpHeader()
 * ------------------------------
 * This function generate a copy of _gen_header.cpp
 * which should includes all definitions of headers
 * and common macros.
 */

void GeneratorProgram::dumpHeader() {
  fputs("\n\n#line 1 \"_gen_header.cpp\"\n\n", program);
  FILE *header = fopen(SRC_DIR "/_gen_header.cpp", "r");
  DEBUG("succesfully open header = %p\n", header);
/* TODO: header == NULL */
  int ch;
  while ((ch = fgetc(header)) != EOF) {
    fputc(ch, program);
  }
  fclose(header);
  fputs("", program);
}

/* GeneratorProgram::dumpUserCodeDecl()
 * ------------------------------------
 *  There are some user defined functions, classes, interfaces
 *  so that we can put it here as a global definition.
 */

void GeneratorProgram::dumpUserCodeDecl() {
}

/* GeneratorProgram::dumpVarDecl()
 * -------------------------------
 *  This function dumps all variables in the spec file
 *  this should include all variables that does NOT specified in
 *  the first part of spec. (inherent variables)
 */

void GeneratorProgram::dumpVarDecl() {
}

/* GeneratorProgram::genCode()
 * ---------------------------
 *  This function is generating the gen() function
 *  this should follow the spec formatting part
 *  which is just traversing the AST.
 *
 *  Also, this part will generate checker functions
 *  I'm thinking that to put the checker function
 *  into an object so that verifier can also use that
 *  as well.
 */

void GeneratorProgram::genCode() {
}

/* GeneratorProgram::dumpMain()
 * ----------------------------
 *  The main function of the generator program
 *  this is a copy from _gen_main.cpp
 *
 *  This includes the some optional flags
 *  and parsing the argument or config file.
 *  Before generate the code, if an user specified initialize() function
 *  is created, then we have to call it. (set the random seed, ...etc.)
 */

void GeneratorProgram::dumpMain() {
  fputs("\n\n#line 1 \"_gen_main.cpp\"\n\n", program);
  FILE *mainfunc = fopen(SRC_DIR "/_gen_main.cpp", "r");
  DEBUG("succesfully open mainfunc = %p\n", mainfunc);
/* TODO: mainfunc == NULL */
  int ch;
  while ((ch = fgetc(mainfunc)) != EOF) {
    fputc(ch, program);
  }
  fclose(mainfunc);
  fputs("", program);
}

/* GeneratorProgram::dumpUserCode()
 * ---------------------------------
 *  if user wants to check their own condition,
 *  they would put their code here.
 */

void GeneratorProgram::dumpUserCode() {
}
