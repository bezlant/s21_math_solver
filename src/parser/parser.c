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

// float calculate(char **polish, float x) {
//     struct my_stack *s = init_stack();
//
//     char *end = NULL;
//
//     for (size_t i = 0; polish[i]; i++) {
//         if (isdigit(polish[i][0])) {
//             push(s, strtof(polish[i], &end));
//         } else if (polish[i][0] == 'x') {
//             push(s, x);
//         } else if (is_fun(polish[i]) || is_unary(polish[i])) {
//             float a = pop(s);
//             push(s, get_op_type(polish[i])->eval(a, 0));
//         } else {
//             float b = pop(s);
//             float a = pop(s);
//             push(s, get_op_type(polish[i])->eval(a, b));
//         }
//     }
//
//     float res = pop(s);
//     my_stack_free(s);
//     return res;
// }
//

struct Tokens *convert_to_rpn(struct Tokens *expression) {
    size_t *res = (size_t *)calloc(256, sizeof(size_t));
    CHECKMALLOC(res);

    struct my_stack *s = init_stack();
    struct Tokens *rpn = (struct Tokens *)calloc(1, sizeof(struct Tokens));

    for (size_t i = 0; i < expression->size;) {
        // TRACE_VALUE("", expression->type[i]);
        if (expression->type[i] == NUM || expression->type[i] == X) {
            rpn->type[rpn->size] = expression->type[i] == NUM ? NUM : X;
            rpn->value[rpn->size] = expression->value[i];
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
                i++;
            }

            pop(s);

            if (!is_empty(s) && is_fun(peek(s))) {
                rpn->type[rpn->size] = pop(s);
                rpn->size++;
                i++;
            }
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
           op == MOD;
}

bool is_fun(size_t op) {
    return op == SIN || op == COS || op == TAN || op == ARCSIN ||
           op == ARCCOS || op == ARCTAN || op == LN || op == LOG || op == SQRT;
}

bool is_unary(size_t op) {
    return op == UNARY_SUB || op == UNARY_ADD;
}

float eval_add(float a, float b) {
    return a + b;
}

float eval_sub(float a, float b) {
    return a - b;
}

float eval_mul(float a, float b) {
    return a * b;
}

float eval_div(float a, float b) {
    return a / b;
}

float eval_pow(float a, float b) {
    return powf(a, b);
}

float eval_mod(float a, float b) {
    return (long long)a % (long long)b;
}

float eval_usub(float a, float b) {
    (void)b;
    return -a;
}

float eval_uadd(float a, float b) {
    (void)b;
    return a;
}

float eval_cos(float a, float b) {
    (void)b;
    return cosf(a);
}

float eval_sin(float a, float b) {
    (void)b;
    return sinf(a);
}

float eval_tan(float a, float b) {
    (void)b;
    return tanf(a);
}

float eval_arccos(float a, float b) {
    (void)b;
    return acosf(a);
}

float eval_arcsin(float a, float b) {
    (void)b;
    return asinf(a);
}

float eval_arctan(float a, float b) {
    (void)b;
    return atanf(a);
}

float eval_sqrt(float a, float b) {
    (void)b;
    return sqrtf(a);
}

float eval_ln(float a, float b) {
    (void)b;
    return logf(a);
}

float eval_log(float a, float b) {
    (void)b;
    return log10f(a);
}
