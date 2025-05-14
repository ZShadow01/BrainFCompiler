#include "tokenizer.h"
#include "errors.h"

#include <ctype.h>

/**
 * Initializes the tokenizer
 */
void tokenizer_init(Tokenizer *tokenizer, const char *filename) {
    // Open the file and hold to allow streaming
    tokenizer->fptr = fopen(filename, "r");
    if (tokenizer->fptr == NULL) {
        error("Could not open file");
    }

    // Read the first character
    tokenizer->current = fgetc(tokenizer->fptr);
}


/**
 * Cleans up the tokenizer and closes the file
 */
void tokenizer_cleanup(Tokenizer *tokenizer) {
    fclose(tokenizer->fptr);
    tokenizer->fptr = NULL;
    tokenizer->current = 0;
}


/**
 * Returns the current token and reads the next character from the file
 */
TokenType tokenizer_next(Tokenizer *tokenizer) {
    if (tokenizer->fptr == NULL) {
        return TOKEN_END_OF_FILE;
    }

    TokenType type = tokenizer_peek(tokenizer);
    if (type != TOKEN_END_OF_FILE) {
        tokenizer->current = fgetc(tokenizer->fptr);
    }
    return type;
}


/**
 * Returns the current token without reading the next character from the file
 */
TokenType tokenizer_peek(Tokenizer *tokenizer) {
    switch (tokenizer->current) {
        case EOF:
            return TOKEN_END_OF_FILE;

        case '+':
            return TOKEN_INCREMENT;

        case '-':
            return TOKEN_DECREMENT;

        case '<':
            return TOKEN_MOVE_LEFT;

        case '>':
            return TOKEN_MOVE_RIGHT;

        case '.':
            return TOKEN_OUTPUT;

        case ',':
            return TOKEN_INPUT;

        case '[':
            return TOKEN_LOOP_OPEN;

        case ']':
            return TOKEN_LOOP_CLOSE;
        
        default:
            return TOKEN_UNKNOWN;
    }
}
