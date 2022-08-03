#include "lexer.h"

// int main(int argc, char *argv[]) {
//
//     char str[] = "5 + sin(x) * ln(23) / 25.233 * cos(sin(ln(x)))";
//     TRACE_PRINT("%s", str);
//
//     struct Tokens *tok = tokenize(str);
//     for (int i = 0; i < tok->size; i++)
//         printf("%s\n", tok->token[i]);
//
//     for (int i = 0; i < tok->size; i++)
//         free(tok->token[i]);
//     free(tok);
//     return 0;
// }

/**
 * @brief Tokenizes the string  *
 * @param str Given string
 * @return returns a struct with the array of tokens & size
 */
struct Tokens *tokenize(char *str) {
    // Integrate this into imgui so we don't exit the program,
    // just wait for a valid input

    if (!is_valid(str))
        return NULL;

    struct Tokens *tok = (struct Tokens *)calloc(1, sizeof(struct Tokens));
    struct Lexer *lex = (struct Lexer *)calloc(1, sizeof(struct Lexer));
    lex->source = str;
    lex->cursor = 0;

    while (lex->source[lex->cursor]) {
        read_number(lex, tok);
        read_function(lex, tok);
        read_symbol(lex, tok);
    }

    free(lex);
    return tok;
}

/**
 * @brief Reads a symbol i.e. *, /, x
 *
 * @param lex Structure with the string and current position
 * @param tok Structure where the tokens will be written to and its size
 */
void read_symbol(struct Lexer *lex, struct Tokens *tok) {
    if (!lex->source[lex->cursor] ||
        (isalnum(lex->source[lex->cursor]) && lex->source[lex->cursor] != 'x'))
        return;

    skip_spaces(lex);

    if (lex->source[lex->cursor] == 'x' || !isalnum(lex->source[lex->cursor])) {
        char *token = (char *)calloc(2, sizeof(char));
        token[0] = lex->source[lex->cursor];
        lex->cursor++;
        tok->token[tok->size] = token;
        tok->size++;
    }
}

/**
 * @brief Reads a number from the string i.e 3, 42.069
 *
 * @param lex Structure with the string and current position
 * @param tok Structure where the tokens will be written to and its size
 */
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

/**
 * @brief Reads a function i.e sin, cos, ln
 *
 * @param lex Structure with the string and current position
 * @param tok Structure where the tokens will be written to and its size
 */
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

/**
 * @brief Skips spaces in the given string
 *
 * @param lex Structure with the string and current position
 */
void skip_spaces(struct Lexer *lex) {
    while (isspace(lex->source[lex->cursor]))
        lex->cursor++;
}

/**
 * @brief Checks if the string only has allowed characters
 *
 * @param str Given string
 * @return 1 if valid otherwise 0
 */
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

/**
 * @brief Frees up memory allocated for the struct Tokens
 *
 * @param tok Pointer to the Tokens
 */
void free_Tokens(struct Tokens *tok) {
    assert(tok != NULL);
    for (size_t i = 0; i < tok->size; i++)
        free(tok->token[i]);

    free(tok);
}
