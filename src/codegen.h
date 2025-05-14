#ifndef __CODEGEN__
#define __CODEGEN__

#include "ast.h"

void generate_c_code(char *output_filename, ASTNode *tree);
int compile_to_binary(char *input_filename, char *output_filename);

#endif  // __CODEGEN__
