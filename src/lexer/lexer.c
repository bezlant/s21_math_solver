#include "lexer.h"

struct Tokens *tokenize(char *str) {
    struct Tokens *tok = (struct Tokens *)calloc(1, sizeof(struct Tokens));
    CHECKMALLOC(tok);

    struct Lexer lex = {.source = str};

    while (lex.source[lex.cursor]) {
        read_number(&lex, tok);
        read_function(&lex, tok);
        read_symbol(&lex, tok);
    }

    replace_unary(tok);

    return tok;
}

void read_symbol(struct Lexer *lex, struct Tokens *tok) {
    skip_spaces(lex);
    if (!lex->source[lex->cursor] ||
        (isalnum(lex->source[lex->cursor]) && lex->source[lex->cursor] != 'x'))
        return;

    tok->type[tok->size] = get_symbol(lex->source[lex->cursor]);
    lex->cursor++;
    tok->size++;
}

size_t get_symbol(char c) {
    switch (c) {
    case 'x':
        return X;
    case '*':
        return MUL;
    case '%':
        return MOD;
    case '/':
        return DIV;
    case '+':
        return ADD;
    case '-':
        return SUB;
    case '^':
        return POW;
    case '(':
        return L_BRACKET;
    default:
        return R_BRACKET;
    }
}

void read_number(struct Lexer *lex, struct Tokens *tok) {
    skip_spaces(lex);
    if (!lex->source[lex->cursor] || !isdigit(lex->source[lex->cursor]))
        return;

    char token[32] = {0};

    for (int i = 0;
         isdigit(lex->source[lex->cursor]) || lex->source[lex->cursor] == '.';
         i++) {
        token[i] = lex->source[lex->cursor];
        lex->cursor++;
    }
    char *end = NULL;

    tok->type[tok->size] = NUM;
    tok->value[tok->size] = strtold(token, &end);
    tok->size++;
}

void read_function(struct Lexer *lex, struct Tokens *tok) {
    skip_spaces(lex);
    if (!lex->source[lex->cursor] || !isalpha(lex->source[lex->cursor]) ||
        lex->source[lex->cursor] == 'x')
        return;

    char token[8] = {0};

    for (int i = 0;
         isalpha(lex->source[lex->cursor]) && lex->source[lex->cursor] != 'x';
         i++) {
        token[i] = lex->source[lex->cursor];
        lex->cursor++;
    }
    tok->type[tok->size] = get_fun(token);
    tok->size++;
}

size_t get_fun(const char *fun) {
    if (!strcmp(fun, "sin"))
        return SIN;
    else if (!strcmp(fun, "cos"))
        return COS;
    else if (!strcmp(fun, "tan"))
        return TAN;
    else if (!strcmp(fun, "arccos"))
        return ARCCOS;
    else if (!strcmp(fun, "arctan"))
        return ARCTAN;
    else if (!strcmp(fun, "arcsin"))
        return ARCSIN;
    else if (!strcmp(fun, "sqrt"))
        return SQRT;
    else if (!strcmp(fun, "ln"))
        return LN;
    else
        return LOG;
}

void skip_spaces(struct Lexer *lex) {
    while (isspace(lex->source[lex->cursor]))
        lex->cursor++;
}

void free_Tokens(struct Tokens *tok) {
    assert(tok != NULL);
    free(tok);
}

void replace_unary(struct Tokens *tok) {
    bool is_prev_num = false;
    for (size_t i = 0; i < tok->size; i++) {
        size_t type = tok->type[i];
        if (type == NUM || type == X) {
            is_prev_num = true;
        } else if (type != L_BRACKET && type != R_BRACKET) {
            if (type == ADD && !is_prev_num)
                tok->type[i] = UNARY_ADD;
            if (type == SUB && !is_prev_num)
                tok->type[i] = UNARY_SUB;
            is_prev_num = false;
        }
    }
}
