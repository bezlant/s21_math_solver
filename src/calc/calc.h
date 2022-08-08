#ifndef CALC_H_
#define CALC_H_

#include "../includes/common.h"
#include "../stack/stack.h"

long double calculate(struct Tokens *expr, long double x);

long double eval_add(long double a, long double b);
long double eval_sub(long double a, long double b);
long double eval_mul(long double a, long double b);
long double eval_div(long double a, long double b);
long double eval_pow(long double a, long double b);
long double eval_mod(long double a, long double b);
long double eval_uadd(long double a, long double b);
long double eval_usub(long double a, long double b);
long double eval_cos(long double a, long double b);
long double eval_sin(long double a, long double b);
long double eval_tan(long double a, long double b);
long double eval_arccos(long double a, long double b);
long double eval_arcsin(long double a, long double b);
long double eval_arctan(long double a, long double b);
long double eval_sqrt(long double a, long double b);
long double eval_ln(long double a, long double b);
long double eval_log(long double a, long double b);
#endif  // CALC_H_
