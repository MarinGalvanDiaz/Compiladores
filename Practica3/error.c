#include <stdio.h>
#include <stdlib.h>

void execerror(const char *s, const char *t) {
    fprintf(stderr, "Error: %s %s\n", s, t);
    exit(1);
}