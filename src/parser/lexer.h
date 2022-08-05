#ifndef LEXER_H_
#define LEXER_H_

#include "../includes/common.h"
#include <pcre.h>

struct Tokens {
    char *token[256];
    size_t size;
};

struct Lexer {
    char *source;
    size_t cursor;
};

/**
 * @brief Tokenizes the string  *
 * @param str Given string
 * @return returns a struct with the array of tokens & size
 */
struct Tokens *tokenize(char *str);

/**
 * @brief Reads a symbol i.e. *, /, x
 *
 * @param lex Structure with the string and current position
 * @param tok Structure where the tokens will be written to and its size
 */
void read_number(struct Lexer *lex, struct Tokens *tok);

/**
 * @brief Reads a number from the string i.e 3, 42.069
 *
 * @param lex Structure with the string and current position
 * @param tok Structure where the tokens will be written to and its size
 */
void read_function(struct Lexer *lex, struct Tokens *tok);

/**
 * @brief Reads a function i.e sin, cos, ln
 *
 * @param lex Structure with the string and current position
 * @param tok Structure where the tokens will be written to and its size
 */
void read_symbol(struct Lexer *lex, struct Tokens *tok);

/**
 * @brief Skips spaces in the given string
 *
 * @param lex Structure with the string and current position
 */
void skip_spaces(struct Lexer *lex);

/**
 * @brief Checks if the string only has allowed characters
 *
 * @param str Given string
 * @return 1 if valid otherwise 0
 */
bool is_valid(char *str);

/**
 * @brief Replaces unary operators - becomes ~, + becomes #
 *
 * @param tok Pointer to the tokens structure
 */
void replace_unary(struct Tokens *tok);

/**
 * @brief Frees up memory allocated for the struct Tokens
 *
 * @param tok Pointer to the Tokens
 */
void free_Tokens(struct Tokens *tok);

#endif  // LEXER_H_
