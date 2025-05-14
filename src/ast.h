#ifndef __AST__
#define __AST__

typedef enum {
    AST_POINTER_MOVE,
    AST_VALUE_CHANGE,
    AST_IO_OUTPUT,
    AST_IO_INPUT,
    AST_LOOP
} ASTNodeType;


typedef struct ASTNode {
    int value;
    ASTNodeType type;
    struct ASTNode *children;
    struct ASTNode *next;
} ASTNode;


ASTNode *ast_node_create();
void ast_destroy(ASTNode *node);

#endif  // __AST__
