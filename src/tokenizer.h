#ifndef __TOKENIZER__
#define __TOKENIZER__

#include <stdio.h>


typedef struct {
    FILE *fptr;
    int current;
} Tokenizer;


typedef enum {
    TOKEN_INCREMENT,
    TOKEN_DECREMENT,
    TOKEN_MOVE_LEFT,
    TOKEN_MOVE_RIGHT,
    TOKEN_OUTPUT,
    TOKEN_INPUT,
    TOKEN_LOOP_OPEN,
    TOKEN_LOOP_CLOSE,

    TOKEN_UNKNOWN,
    TOKEN_END_OF_FILE
} TokenType;


void tokenizer_init(Tokenizer *tokenizer, const char *filename);
void tokenizer_cleanup(Tokenizer *tokenizer);

TokenType tokenizer_next(Tokenizer *tokenizer);
TokenType tokenizer_peek(Tokenizer *tokenizer);

#endif  // __TOKENIZER__
