#include "errors.h"

#include <stdio.h>
#include <stdlib.h>


/**
 * Prints an error message and exits the program
 */
void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}
