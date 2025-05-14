#ifndef __PARSER__
#define __PARSER__

#include "tokenizer.h"
#include "ast.h"

typedef struct {
    Tokenizer tokenizer;
    unsigned int _loops;
} Parser;

void ast_print(ASTNode *node);

void parser_init(Parser *parser, const char *filename);
ASTNode *parser_parse(Parser *parser);

void parser_optimize_value(Parser *parser, ASTNode *node);
void parser_optimize_pointer(Parser *parser, ASTNode *node);
void parser_optimize_input(Parser *parser, ASTNode *node);
void parser_optimize_output(Parser *parser, ASTNode *node);


#endif  // __PARSER__
