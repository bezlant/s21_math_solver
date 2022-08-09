#include "calc.h"

long double calculate(struct Tokens *expr, long double x) {
    struct op_type operators[] = {
        {"+", 5, LEFT, eval_add},
        {"-", 5, LEFT, eval_sub},
        {"*", 8, LEFT, eval_mul},
        {"/", 8, LEFT, eval_div},
        {"^", 9, RIGHT, eval_pow},
        {"%", 8, LEFT, eval_mod},
        {"~", 10, RIGHT, eval_usub},
        {"#", 10, RIGHT, eval_uadd},
        {"cos", 3, LEFT, eval_cos},
        {"sin", 3, LEFT, eval_sin},
        {"tan", 3, LEFT, eval_tan},
        {"arccos", 3, LEFT, eval_arccos},
        {"arcsin", 3, LEFT, eval_arcsin},
        {"arctan", 3, LEFT, eval_arctan},
        {"sqrt", 3, LEFT, eval_sqrt},
        {"ln", 3, LEFT, eval_ln},
        {"log", 3, LEFT, eval_log},
        {"(", 0, NONE, NULL},
        {")", 0, NONE, NULL},
    };

    struct my_stack *s = init_stack();

    for (size_t i = 0; i < expr->size; i++) {
        if (expr->type[i] == NUM) {
            push(s, expr->value[i]);
        } else if (expr->type[i] == X) {
            push(s, x);
        } else if (is_fun(expr->type[i]) || is_unary(expr->type[i])) {
            long double a = pop(s);
            push(s, operators[expr->type[i]].eval(a, 0));
        } else {
            long double b = pop(s);
            long double a = pop(s);
            push(s, operators[expr->type[i]].eval(a, b));
        }
    }

    long double res = pop(s);
    my_stack_free(s);
    return res;
}

long double eval_add(long double a, long double b) {
    return a + b;
}

long double eval_sub(long double a, long double b) {
    return a - b;
}

long double eval_mul(long double a, long double b) {
    return a * b;
}

long double eval_div(long double a, long double b) {
    if (fabsl(b) < 1e-02) {
        if (b > 0)
            return INFINITY;
        else
            return -INFINITY;
    }
    return a / b;
}

long double eval_pow(long double a, long double b) {
    return powl(a, b);
}

long double eval_mod(long double a, long double b) {
    return fmodl(a, b);
}

long double eval_usub(long double a, long double b) {
    (void)b;
    return -a;
}

long double eval_uadd(long double a, long double b) {
    (void)b;
    return a;
}

long double eval_cos(long double a, long double b) {
    (void)b;
    return cosl(a);
}

long double eval_sin(long double a, long double b) {
    (void)b;
    return sinl(a);
}

long double eval_tan(long double a, long double b) {
    (void)b;
    if (fmodl(fabsl(a), M_PI_2) < 1e-02)
        return INFINITY;
    else if (fabsl(fmodl(fabsl(a), M_PI_2) - M_PI_2) < 1e-02)
        return -INFINITY;

    return tanl(a);
}

long double eval_arccos(long double a, long double b) {
    (void)b;
    return acosl(a);
}

long double eval_arcsin(long double a, long double b) {
    (void)b;
    return asinl(a);
}

long double eval_arctan(long double a, long double b) {
    (void)b;
    return atanl(a);
}

long double eval_sqrt(long double a, long double b) {
    (void)b;
    return sqrtl(a);
}

long double eval_ln(long double a, long double b) {
    (void)b;
    return logl(a);
}

long double eval_log(long double a, long double b) {
    (void)b;
    return log10l(a);
}
