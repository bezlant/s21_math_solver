#include "shunting.h"

struct Tokens *convert_to_rpn(struct Tokens *expression) {
    struct op_type operators[] = {
        {"+", 5, LEFT, NULL},      {"-", 5, LEFT, NULL},
        {"*", 8, LEFT, NULL},      {"/", 8, LEFT, NULL},
        {"^", 9, RIGHT, NULL},     {"%", 8, LEFT, NULL},
        {"~", 10, RIGHT, NULL},    {"#", 10, RIGHT, NULL},
        {"cos", 3, LEFT, NULL},    {"sin", 3, LEFT, NULL},
        {"tan", 3, LEFT, NULL},    {"arccos", 3, LEFT, NULL},
        {"arcsin", 3, LEFT, NULL}, {"arctan", 3, LEFT, NULL},
        {"sqrt", 3, LEFT, NULL},   {"ln", 3, LEFT, NULL},
        {"log", 3, LEFT, NULL},    {"(", 0, NONE, NULL},
        {")", 0, NONE, NULL},
    };

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

            if (is_empty(s))
                return NULL;

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

bool is_unary(size_t op) {
    return op == UNARY_SUB || op == UNARY_ADD;
}

bool is_op(size_t op) {
    return op == ADD || op == SUB || op == MUL || op == DIV || op == POW ||
           op == MOD || op == UNARY_SUB || op == UNARY_ADD;
}

bool is_fun(size_t op) {
    return op == SIN || op == COS || op == TAN || op == ARCSIN ||
           op == ARCCOS || op == ARCTAN || op == LN || op == LOG || op == SQRT;
}
