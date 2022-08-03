#include "parser.h"

int main(int argc, char *argv[]) {

    char str[] = "5 + sin(x) * ln(23) / 25.233 * cos(sin(ln(x)))";
    TRACE_PRINT("%s", str);

    struct Tokens *tok = tokenize(str);
    for (int i = 0; i < tok->size; i++)
        printf("%s\n", tok->token[i]);

    for (int i = 0; i < tok->size; i++)
        free(tok->token[i]);
    free(tok);
    return 0;
}

struct Tokens *tokenize(char *str) {
    // Integrate this into imgui so we don't exit the program,
    // just wait for a valid input

    if (!is_valid(str)) {
        fprintf(stderr, "Please input a valid expression");
        exit(EXIT_FAILURE);
    }

    struct Tokens *tok = (struct Tokens *)calloc(1, sizeof(struct Tokens));
    struct Lexer *lex = (struct Lexer *)calloc(1, sizeof(struct Lexer));
    lex->source = str;
    lex->cursor = 0;

    while (lex->source[lex->cursor]) {
        read_x(lex, tok);
        read_number(lex, tok);
        read_function(lex, tok);
        read_symbol(lex, tok);
    }

    free(lex);
    return tok;
}

void read_x(struct Lexer *lex, struct Tokens *tok) {
    if (!lex->source[lex->cursor])
        return;

    skip_spaces(lex);

    if (lex->source[lex->cursor] == 'x') {
        tok->token[tok->size] = (char *)calloc(2, sizeof(char));
        tok->token[tok->size][0] = 'x';
        tok->size++;
        lex->cursor++;
    }
}

void read_number(struct Lexer *lex, struct Tokens *tok) {
    if (!lex->source[lex->cursor] || !isdigit(lex->source[lex->cursor]))
        return;

    skip_spaces(lex);

    char *token = (char *)calloc(32, sizeof(char));

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

    for (int i = 0;
         isalpha(lex->source[lex->cursor]) && lex->source[lex->cursor] != 'x';
         i++) {
        token[i] = lex->source[lex->cursor];
        lex->cursor++;
    }

    tok->token[tok->size] = token;
    tok->size++;
}

void read_symbol(struct Lexer *lex, struct Tokens *tok) {
    if (!lex->source[lex->cursor] || isalnum(lex->source[lex->cursor]))
        return;

    skip_spaces(lex);

    if (!isalnum(lex->source[lex->cursor])) {
        char *token = (char *)calloc(2, sizeof(char));
        token[0] = lex->source[lex->cursor];
        lex->cursor++;
        tok->token[tok->size] = token;
        tok->size++;
    }
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
    if (!reg) {
        fprintf(stderr, "Can't compile the regular expression");
        exit(EXIT_FAILURE);
    }

    if (pcre_exec(reg, NULL, str, strlen(str), 0, 0, NULL, 0))
        ret = false;

    pcre_free(reg);
    return ret;
}
