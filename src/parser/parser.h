#ifndef PARSER_H_
#define PARSER_H_

#include "../includes/common.h"
#include "../stack/stack.h"

struct op_type {
    char op[8];
    short precedence;
    short associativity;
    float (*eval)(float a, float b);
};

enum {
    RIGHT,
    LEFT,
    NONE
};

enum {
    ADD = 0,
    SUB,
    MUL,
    DIV,
    POW,
    MOD,
    UNARY_ADD,
    UNARY_SUB,
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
    R_BRACKET
};

char **convert_to_rpn(char **tokens, size_t size);
struct op_type *get_op_type(char *op);
float calculate(char **polish);
bool is_fun(const char *op);
bool is_unary(const char *op);

float eval_add(float a, float b);
float eval_sub(float a, float b);
float eval_mul(float a, float b);
float eval_div(float a, float b);
float eval_pow(float a, float b);
float eval_mod(float a, float b);
float eval_uadd(float a, float b);
float eval_usub(float a, float b);
float eval_cos(float a, float b);
float eval_sin(float a, float b);
float eval_tan(float a, float b);
float eval_arccos(float a, float b);
float eval_arcsin(float a, float b);
float eval_arctan(float a, float b);
float eval_sqrt(float a, float b);
float eval_ln(float a, float b);
float eval_log(float a, float b);

#endif  // PARSER_H_
