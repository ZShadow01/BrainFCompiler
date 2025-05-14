#include "codegen.h"
#include "errors.h"

#include <stdio.h>
#include <stdlib.h>

void write_code(FILE *fptr, ASTNode *node) {
    if (node == NULL) {
        return;
    }

    switch (node->type) {
        case AST_POINTER_MOVE:
            fprintf(fptr, "    ptr += %d;\n", node->value);
            break;
        
        case AST_VALUE_CHANGE:
            fprintf(fptr, "    mem[ptr] += %d;\n", node->value);
            break;

        case AST_IO_OUTPUT:
            for (int i = 0; i < node->value; i++) {
                fprintf(fptr, "    putchar(mem[ptr]);\n");
            }
            break;

        case AST_IO_INPUT:
            for (int i = 0; i < node->value; i++) {
                fprintf(fptr, "    mem[ptr] = getchar();\n");
            }
            break;

        case AST_LOOP:
            fprintf(fptr, "    while (mem[ptr]) {\n");
            write_code(fptr, node->children);
            fprintf(fptr, "    }\n");
            break;
    }

    write_code(fptr, node->next);
}

void generate_c_code(char *output_filename, ASTNode *tree) {
    FILE *fptr = fopen(output_filename, "w+");
    if (fptr == NULL) {
        error("Could not open output.c");
    }

    fprintf(fptr,
        "#include <stdio.h>\n"
        "#include <stdint.h>\n"
        "int main() {\n"
        "    uint8_t mem[30000] = {0};\n"
        "    int ptr = 0;\n"
    );

    write_code(fptr, tree);

    fprintf(fptr, "}\n");
    fclose(fptr);
}


int compile_to_binary(char *input_filename, char *output_filename) {
    char command[512] = {0};
    snprintf(command, sizeof(command), "gcc -O2 -Wall %s -o %s", input_filename, output_filename);
    return system(command);
}
