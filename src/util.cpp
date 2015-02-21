#include "util.h"

namespace Utility {
  void PrintIndentation(FILE *out, int indent) {
    for(int i = 0; i < indent; i++)
      fprintf(out, "  ");
  }
}
