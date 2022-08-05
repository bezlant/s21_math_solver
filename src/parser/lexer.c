#include "lexer.h"

struct Tokens *tokenize(char *str) {
    if (!is_valid(str))
        return NULL;

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
    if (!lex->source[lex->cursor] ||
        (isalnum(lex->source[lex->cursor]) && lex->source[lex->cursor] != 'x'))
        return;

    skip_spaces(lex);

    if (lex->source[lex->cursor] == 'x' || !isalnum(lex->source[lex->cursor])) {
        char *token = (char *)calloc(2, sizeof(char));
        CHECKMALLOC(token);
        token[0] = lex->source[lex->cursor];
        lex->cursor++;
        tok->token[tok->size] = token;
        tok->size++;
    }
}

void read_number(struct Lexer *lex, struct Tokens *tok) {
    if (!lex->source[lex->cursor] || !isdigit(lex->source[lex->cursor]))
        return;

    skip_spaces(lex);

    char *token = (char *)calloc(32, sizeof(char));
    CHECKMALLOC(token);

    for (int i = 0;
         isdigit(lex->source[lex->cursor]) || lex->source[lex->cursor] == '.';
         i++) {
        token[i] = lex->source[lex->cursor];
        lex->cursor++;
    }

    tok->token[tok->size] = token;
    tok->size++;
}

void read_function(struct Lexer *lex, struct Tokens *tok) {
    if (!lex->source[lex->cursor] || !isalpha(lex->source[lex->cursor]) ||
        lex->source[lex->cursor] == 'x')
        return;

    skip_spaces(lex);

    char *token = (char *)calloc(8, sizeof(char));
    CHECKMALLOC(token);

    for (int i = 0;
         isalpha(lex->source[lex->cursor]) && lex->source[lex->cursor] != 'x';
         i++) {
        token[i] = lex->source[lex->cursor];
        lex->cursor++;
    }

    tok->token[tok->size] = token;
    tok->size++;
}

void skip_spaces(struct Lexer *lex) {
    while (isspace(lex->source[lex->cursor]))
        lex->cursor++;
}

bool is_valid(char *str) {
    bool ret = true;
    const char *error = NULL;
    int erroffset = 0;
    pcre *reg = pcre_compile("^[a-z0-9 \\.\\(\\)\\*\\-\\+\\%\\/\\^]+$", 0,
                             &error, &erroffset, NULL);
    assert(reg != NULL);

    if (pcre_exec(reg, NULL, str, strlen(str), 0, 0, NULL, 0))
        ret = false;

    pcre_free(reg);
    return ret;
}

void free_Tokens(struct Tokens *tok) {
    assert(tok != NULL);
    for (size_t i = 0; i < tok->size; i++)
        free(tok->token[i]);

    free(tok);
}

void replace_unary(struct Tokens *tok) {
    bool is_prev_num = false;
    for (size_t i = 0; i < tok->size; i++) {
        if (isdigit(tok->token[i][0]) || tok->token[i][0] == 'x') {
            is_prev_num = true;
        } else if (tok->token[i][0] != ')' && tok->token[i][0] != '(') {
            if (tok->token[i][0] == '+' && !is_prev_num)
                tok->token[i][0] = '#';
            if (tok->token[i][0] == '-' && !is_prev_num)
                tok->token[i][0] = '~';
            is_prev_num = false;
        }
    }
}
