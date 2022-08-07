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

struct Tokens *convert_to_rpn(struct Tokens *expression);

bool is_fun(size_t op);
bool is_unary(size_t op);
bool is_op(size_t op);

float calculate(char **polish, float x);

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
