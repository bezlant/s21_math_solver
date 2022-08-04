#ifndef PARSER_H_
#define PARSER_H_

#include "../includes/common.h"
#include "../stack/stack.h"

enum {
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    MOD,
    PLUS,
    MINUS,
    COS,
    SIN,
    TAN,
    ARCCOS,
    ARCSIN,
    ARCTAN,
    SQRT,
    LN,
    LOG,
};

char *convert_to_rpn(char **tokens, size_t size);

#endif  // PARSER_H_
