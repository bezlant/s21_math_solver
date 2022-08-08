#ifndef COMMON_H_
#define COMMON_H_

#include "debug.h"
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    ADD = 0,
    SUB,
    MUL,
    DIV,
    POW,
    MOD,
    UNARY_SUB,
    UNARY_ADD,
    COS,
    SIN,
    TAN,
    ARCCOS,
    ARCSIN,
    ARCTAN,
    SQRT,
    LN,
    LOG,
    L_BRACKET,
    R_BRACKET,
    NUM,
    X,
};

struct Tokens {
    size_t type[256];
    float value[256];
    size_t size;
};

#define CHECKMALLOC(var)                                                       \
    if ((var) == NULL) {                                                       \
        fprintf(stderr, "ERROR: Memory allocation failed\n");                  \
        abort();                                                               \
    }

#endif  // COMMON_H_
