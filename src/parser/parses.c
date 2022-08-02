#include "parser.h"

int main(int argc, char *argv[]) {

    char str[] = "5 + sin(x) * ln(23) / 25";
    TRACE_PRINT("%s", str);

    struct Tokens *tok = tokenize(str);

    free(tok);
    return 0;
}

struct Tokens *tokenize(char *str) {
    // Match math expression ^[a-z0-1 \(\)\*\-\+\%\/\^]+$
    // TODO: Figure out how to match a mathematical expression with regex.h
    regex_t regex;
    if (regcomp(&regex, "^[a-z0-1 \\(\\)\\*\\-\\+\\%\\/\\^]+$", REG_EXTENDED)) {
        fprintf(stderr, "Can't compile the regular expression");
        exit(EXIT_FAILURE);
    }

    // Integrate this into imgui so we don't exit the program,
    // just wait for a valid input
    if (regexec(&regex, str, 0, NULL, 0) == REG_NOMATCH) {
        fprintf(stderr, "Please input a valid expression");
        exit(EXIT_FAILURE);
    }

    regfree(&regex);

    struct Tokens *tok = (struct Tokens *)calloc(1, sizeof(struct Tokens));
    // struct Lexer *lex = (struct Lexer *)calloc(1, sizeof(struct Lexer));
    // lex->source = str;
    // lex->cursor = 0;
    //
    // while (lex->source[lex->cursor]) {
    //     read_x(lex, tok);
    //     read_number(lex, tok);
    //     read_function(lex, tok);
    //     read_symbol(lex, tok);
    // }
    //
    // free(lex);
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
    if (!lex->source[lex->cursor])
        return;

    skip_spaces(lex);

    char *token = (char *)calloc(32, sizeof(char));

    while (isdigit(lex->source[lex->cursor]) ||
           lex->source[lex->cursor] == '.') {
        *token = lex->source[lex->cursor];
        lex->cursor++;
        token++;
    }

    tok->token[tok->size] = token;
    tok->size++;
}

void read_function(struct Lexer *lex, struct Tokens *tok) {
    if (!lex->source[lex->cursor])
        return;

    skip_spaces(lex);

    char *token = (char *)calloc(8, sizeof(char));

    while (isalpha(lex->source[lex->cursor]) &&
           lex->source[lex->cursor] != 'x') {
        *token = lex->source[lex->cursor];
        lex->cursor++;
        token++;
    }

    tok->token[tok->size] = token;
    tok->size++;
}

void read_symbol(struct Lexer *lex, struct Tokens *tok) {
    if (!lex->source[lex->cursor])
        return;

    skip_spaces(lex);

    char *token = (char *)calloc(2, sizeof(char));

    while (!isalnum(lex->source[lex->cursor])) {
        *token = lex->source[lex->cursor];
        lex->cursor++;
        token++;
    }

    tok->token[tok->size] = token;
    tok->size++;
}

void skip_spaces(struct Lexer *lex) {
    while (isspace(lex->source[lex->cursor]))
        lex->cursor++;
}
