#include "parser.h"

static struct op_type operators[] = {
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

long double calculate(struct Tokens *expr, long double x) {
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

struct Tokens *convert_to_rpn(struct Tokens *expression) {
    size_t *res = (size_t *)calloc(256, sizeof(size_t));
    CHECKMALLOC(res);

    struct my_stack *s = init_stack();
    struct Tokens *rpn = (struct Tokens *)calloc(1, sizeof(struct Tokens));

    for (size_t i = 0; i < expression->size;) {
        if (expression->type[i] == NUM) {
            rpn->type[rpn->size] = expression->type[i];
            rpn->value[rpn->size] = expression->value[i];
            rpn->size++;
            i++;
        } else if (expression->type[i] == X) {
            rpn->type[rpn->size] = X;
            rpn->size++;
            i++;
        } else if (is_fun(expression->type[i]) ||
                   expression->type[i] == L_BRACKET) {
            push(s, expression->type[i]);
            i++;
        } else if (is_op(expression->type[i])) {
            while (!is_empty(s) && is_op(peek(s)) &&
                   ((operators[(size_t)peek(s)].precedence >
                     operators[(size_t)expression->type[i]].precedence) ||
                    (operators[(size_t)peek(s)].precedence ==
                         operators[(size_t)expression->type[i]].precedence &&
                     operators[expression->type[i]].associativity == LEFT))) {
                rpn->type[rpn->size] = pop(s);
                rpn->size++;
            }
            push(s, expression->type[i]);
            i++;
        } else if (expression->type[i] == R_BRACKET) {
            while (!is_empty(s) && peek(s) != L_BRACKET) {
                rpn->type[rpn->size] = pop(s);
                rpn->size++;
            }

            pop(s);

            if (!is_empty(s) && is_fun(peek(s))) {
                rpn->type[rpn->size] = pop(s);
                rpn->size++;
            }
            i++;
        }
    }

    while (!is_empty(s)) {
        size_t op = pop(s);
        if (op == L_BRACKET || op == R_BRACKET)
            return NULL;
        else
            rpn->type[rpn->size] = op;
        rpn->size++;
    }
    return rpn;
}

bool is_op(size_t op) {
    return op == ADD || op == SUB || op == MUL || op == DIV || op == POW ||
           op == MOD || op == UNARY_SUB || op == UNARY_ADD;
}

bool is_fun(size_t op) {
    return op == SIN || op == COS || op == TAN || op == ARCSIN ||
           op == ARCCOS || op == ARCTAN || op == LN || op == LOG || op == SQRT;
}

bool is_unary(size_t op) {
    return op == UNARY_SUB || op == UNARY_ADD;
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
