#include "parser.h"
#include "tokenizer.h"
#include "errors.h"


void ast_print(ASTNode *node) {
    if (node == NULL) {
        return;
    }

    printf("%dx %d\n", node->value, node->type);

    ast_print(node->children);

    ast_print(node->next);
}


void parser_init(Parser *parser, const char *filename) {
    parser->tokenizer.fptr = NULL;

    tokenizer_init(&parser->tokenizer, filename);
    parser->_loops = 0;
}


ASTNode *parser_parse(Parser *parser) {
    TokenType current;

    // Skip unnecessary information
    while ((current = tokenizer_next(&parser->tokenizer)) == TOKEN_UNKNOWN) {}
    if (current == TOKEN_END_OF_FILE) {
        if (parser->_loops > 0) {
            error("Unexpected EOF: missing closing ']'");
        }
        return NULL;
    } else if (current == TOKEN_LOOP_CLOSE) {
        if (parser->_loops == 0) {
            error("Unmatched closing bracket ']'");
            return NULL;
        }
        parser->_loops--;
        return NULL;
    }

    ASTNode *node = ast_node_create();
    node->value = 1;

    switch (current) {
        case TOKEN_INCREMENT:
            node->type = AST_VALUE_CHANGE;
            parser_optimize_value(parser, node);
            break;

        case TOKEN_DECREMENT:
            node->type = AST_VALUE_CHANGE;
            node->value = -1;
            parser_optimize_value(parser, node);
            break;

        case TOKEN_MOVE_RIGHT:
            node->type = AST_POINTER_MOVE;
            parser_optimize_pointer(parser, node);
            break;

        case TOKEN_MOVE_LEFT:
            node->type = AST_POINTER_MOVE;
            node->value = -1;
            parser_optimize_pointer(parser, node);
            break;
        
        case TOKEN_OUTPUT:
            node->type = AST_IO_OUTPUT;
            parser_optimize_output(parser, node);
            break;

        case TOKEN_INPUT:
            node->type = AST_IO_INPUT;
            parser_optimize_input(parser, node);
            break;

        case TOKEN_LOOP_OPEN:
            parser->_loops++;
            node->type = AST_LOOP;
            node->children = parser_parse(parser);
            break;

        // Never reached
        default:
            break;
    }

    node->next = parser_parse(parser);
    return node;
}


void parser_optimize_value(Parser *parser, ASTNode *node) {
    TokenType type = tokenizer_peek(&parser->tokenizer);
    
    if (type == TOKEN_INCREMENT) {
        node->value++;
        tokenizer_next(&parser->tokenizer);
        parser_optimize_value(parser, node);
    } else if (type == TOKEN_DECREMENT) {
        node->value--;
        tokenizer_next(&parser->tokenizer);
        parser_optimize_value(parser, node);
    }
}


void parser_optimize_pointer(Parser *parser, ASTNode *node) {
    TokenType type = tokenizer_peek(&parser->tokenizer);

    if (type == TOKEN_MOVE_RIGHT) {
        node->value++;
        tokenizer_next(&parser->tokenizer);
        parser_optimize_pointer(parser, node);
    } else if (type == TOKEN_MOVE_LEFT) {
        node->value--;
        tokenizer_next(&parser->tokenizer);
        parser_optimize_pointer(parser, node);
    }
}


void parser_optimize_input(Parser *parser, ASTNode *node) {
    TokenType type = tokenizer_peek(&parser->tokenizer);

    if (type == TOKEN_INPUT) {
        node->value++;
        tokenizer_next(&parser->tokenizer);
        parser_optimize_input(parser, node);
    }
}


void parser_optimize_output(Parser *parser, ASTNode *node) {
    TokenType type = tokenizer_peek(&parser->tokenizer);

    if (type == TOKEN_OUTPUT) {
        node->value++;
        tokenizer_next(&parser->tokenizer);
        parser_optimize_output(parser, node);
    }
}
