#include <string>
#include <cstring>
#include "formatting.h"

extern std::string gpFilename, vpFilename;

void helper() {
  /* Here outputs the helper message */
}

int main(int argc, char *argv[]) {
  
  /* If there is a helper flag */
  for (int i = 1; i < argc; i++) if(strncmp(argv[i], "-h", 2) == 0) { helper(); return 0; }

  /* Set Default Flags */
  gpFilename = "generator.cpp";
  vpFilename = "verifier.cpp";

  /* Collect flags */
  for (int i = 1; i < argc-1; i++) {
    /* Generator File Name */
    if(strncmp(argv[i], "-G", 2) == 0) { gpFilename = argv[i+1]; }
    /* Verifier File Name */
    if(strncmp(argv[i], "-V", 2) == 0) { vpFilename = argv[i+1]; }
  }

  yyparse();

  return 0;
}
