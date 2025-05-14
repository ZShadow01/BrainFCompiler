#include "ast.h"

#include <stdlib.h>


/**
 * Creates a AST node
 */
ASTNode *ast_node_create() {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (node == NULL) {
        return NULL;
    }

    node->value = 0;
    node->children = NULL;
    node->next = NULL;
    node->type = AST_VALUE_CHANGE;  // Default value: AST_VALUE_CHANGE
    return node;
}


/**
 * Destroys the AST by walking through the tree and freeing each node (in-order traversal)
 */
void ast_destroy(ASTNode *node) {
    if (node->children != NULL) {
        ast_destroy(node->children);
    }

    if (node->next != NULL) {
        ast_destroy(node->next);
    }

    free(node);
}