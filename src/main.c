#include "errors.h"
#include "parser.h"
#include "codegen.h"

#include "string.h"


int main(int argc, char **argv) {
    if (argc < 2) {
        printf(
            "Use\n\n"
            "\tbrainf <file-to-compile> [-o <output-path>]\n\n"
            "to compile your .bf file"
        );
        return 0;
    }

    char *output_path = NULL;

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-o") && i + 1 < argc) {
            output_path = argv[i + 1];
        }
    }

    // Initialize the parser
    Parser parser;
    parser_init(&parser, argv[1]);

    // Generate the (optimized) Abstract Syntax Tree
    ASTNode *tree = parser_parse(&parser);

    // Generate a C code and write to (temporary) output.c
    generate_c_code("output.c", tree);

    // Compile the C code to an executable file
    if (compile_to_binary("output.c", output_path == NULL ? "output" : output_path)) {
        error("Failed to compile C code");
    }

    // Remove the generated output.c file
    remove("output.c");

    // Free memory taken by the AST
    ast_destroy(tree);
    return 0;
}
