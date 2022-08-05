#include "parser.h"

static struct op_type operators[] = {
    [UNARY_ADD] = {"~", 10, RIGHT, eval_usub},
    [UNARY_SUB] = {"#", 10, RIGHT, eval_uadd},
    [POW] = {"^", 9, RIGHT, eval_pow},
    [MUL] = {"*", 8, LEFT, eval_mul},
    [DIV] = {"/", 8, LEFT, eval_div},
    [MOD] = {"%", 8, LEFT, eval_mod},
    [ADD] = {"+", 5, LEFT, eval_add},
    [SUB] = {"-", 5, LEFT, eval_sub},
    [COS] = {"cos", 3, LEFT, eval_cos},
    [SIN] = {"sin", 3, LEFT, eval_sin},
    [TAN] = {"tan", 3, LEFT, eval_tan},
    [ARCCOS] = {"arccos", 3, LEFT, eval_arccos},
    [ARCSIN] = {"arcsin", 3, LEFT, eval_arcsin},
    [ARCTAN] = {"arctan", 3, LEFT, eval_arctan},
    [SQRT] = {"sqrt", 3, LEFT, eval_sqrt},
    [LN] = {"ln", 3, LEFT, eval_ln},
    [LOG] = {"log", 3, LEFT, eval_log},
    [L_BRACKET] = {"(", 0, NONE, NULL},
    [R_BRACKET] = {")", 0, NONE, NULL},
};

float calculate(char **polish, float x) {
    struct my_stack *s = init_stack();

    char *end = NULL;
    for (size_t i = 0; polish[i]; i++) {
        if (isdigit(polish[i][0]) || polish[i][0] == 'x') {
            push(s, strtof(polish[i], &end));
        } else if (is_fun(polish[i]) || is_unary(polish[i])) {
            float a = pop(s);
            push(s, get_op_type(polish[i])->eval(a, 0));
        } else {
            float b = pop(s);
            float a = pop(s);
            push(s, get_op_type(polish[i])->eval(a, b));
        }
    }

    float res = pop(s);
    my_stack_free(s);
    return res;
}

bool is_unary(const char *op) {
    return *op == '~' || *op == '#';
}

char **convert_to_rpn(char **tokens, size_t size) {

    char **res = (char **)calloc(256, sizeof(char *));
    CHECKMALLOC(res);
    char **ops = (char **)calloc(8, sizeof(char *));
    CHECKMALLOC(ops);

    size_t op_idx = 0;
    size_t idx = 0;

    for (size_t i = 0; i < size; i++) {
        char *tok = tokens[i];
        if (isdigit(tok[0]) || tok[0] == 'x') {
            res[idx] = tok;
            idx++;
        } else if (is_fun(tok) || tok[0] == '(') {
            ops[op_idx] = tok;
            op_idx++;
        } else if (tok[0] == ')') {
            while (ops[op_idx - 1][0] != '(') {
                op_idx--;
                res[idx] = get_op_type(ops[op_idx])->op;
                idx++;
            }
            op_idx--;

            if (op_idx > 0) {
                char *cur_op = get_op_type(ops[op_idx - 1])->op;
                if (is_fun(cur_op)) {
                    res[idx] = cur_op;
                    idx++;
                }
            }
        } else {
            while (op_idx > 0 && !is_fun(ops[op_idx - 1]) &&
                   ops[op_idx - 1][0] != '(' &&
                   get_op_type(ops[op_idx - 1])->precedence >=
                       get_op_type(tok)->precedence) {
                op_idx--;
                res[idx] = ops[op_idx];
                idx++;
            }
            ops[op_idx] = tok;
            op_idx++;
        }
    }

    while (op_idx) {
        op_idx--;
        res[idx] = ops[op_idx];
        idx++;
    }

    return res;
}

bool is_fun(const char *op) {
    return !strcmp(op, "sin") || !strcmp(op, "cos") || !strcmp(op, "tan") ||
           !strcmp(op, "arccos") || !strcmp(op, "arctan") ||
           !strcmp(op, "arcsin") || !strcmp(op, "sqrt") || !strcmp(op, "ln") ||
           !strcmp(op, "log");
}

struct op_type *get_op_type(char *op) {
    struct op_type *res = NULL;
    for (size_t i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (!strcmp(operators[i].op, op)) {
            res = operators + i;
            break;
        }
    }
    return res;
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
    return pow(a, b);
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
