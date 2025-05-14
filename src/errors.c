#include "errors.h"

#include <stdio.h>
#include <stdlib.h>


void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}
