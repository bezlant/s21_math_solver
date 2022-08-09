#include "validation.h"

static bool is_precision_ok(char *str) {
    size_t len = strlen(str);
    bool ret = true;
    if (ret && (str[0] == '.' || str[len - 1] == '.'))
        ret = false;

    for (size_t i = 1; i < len - 1 && ret; i++) {
        if (str[i] == '.' && (!isdigit(str[i - 1]) || !isdigit(str[i + 1])))
            ret = false;
    }
    return ret;
}

bool is_valid(char *str) {
    bool ret = true;
    const char *error = NULL;
    int erroffset = 0;
    pcre *reg = pcre_compile(
        "^(sin|cos|tan|arccos|arctan|arcsin|sqrt|ln|log|x|[0-9 \\.\\(\\)\\*\\-\\+\\%\\/\\^])+$",
        0, &error, &erroffset, NULL);
    assert(reg != NULL);

    if (pcre_exec(reg, NULL, str, strlen(str), 0, 0, NULL, 0))
        ret = false;

    pcre_free(reg);

    if (ret)
        ret = is_precision_ok(str);

    return ret;
}

bool brackets_ok(struct Tokens *tok) {
    struct my_stack *s = init_stack();
    bool is_ok = true;
    for (size_t i = 0; i < tok->size && is_ok; i++) {
        if (tok->type[i] == L_BRACKET) {
            push(s, L_BRACKET);
        } else if (tok->type[i] == R_BRACKET) {
            if (is_empty(s)) {
                is_ok = false;
                break;
            }
            pop(s);
        }

        if (tok->size - 1 && tok->type[i] == L_BRACKET &&
            tok->type[i + 1] == R_BRACKET)
            is_ok = false;
    }
    if (!is_empty(s))
        is_ok = false;

    return is_ok;
}

bool operators_ok(struct Tokens *tok) {
    bool is_ok = true;

    if ((is_op(tok->type[0]) && !is_unary(tok->type[0])) ||
        is_op(tok->type[tok->size - 1]))
        is_ok = false;

    for (size_t i = 1; i < tok->size - 1 && is_ok; i++) {
        int left = tok->type[i - 1];
        int right = tok->type[i + 1];

        if (is_op(tok->type[i]) && !is_unary(tok->type[i])) {
            if (left != NUM && left != X && left != R_BRACKET)
                is_ok = false;

            if (right != NUM && right != X && !is_fun(right) &&
                right != L_BRACKET)
                is_ok = false;
        }
    }

    return is_ok;
}

bool numbers_ok(struct Tokens *tok) {
    bool is_ok = true;
    for (size_t i = 1; i < tok->size && is_ok; i++) {
        size_t left = tok->type[i - 1];
        size_t right = tok->type[i + 1];
        if (tok->type[i] == NUM &&
            (left == NUM || left == X || right == NUM || right == X))
            is_ok = false;
    }

    return is_ok;
}

bool functions_ok(struct Tokens *tok) {
    bool is_ok = true;

    if (is_fun(tok->type[tok->size - 1]))
        is_ok = false;

    for (size_t i = 1; i < tok->size - 1 && is_ok; i++) {
        if (is_fun(tok->type[i])) {
            if (tok->type[i + 1] != L_BRACKET || tok->type[i - 1] == R_BRACKET)
                is_ok = false;
        }
    }
    return is_ok;
}
