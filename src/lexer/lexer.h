/**
 * @file lexer.h
 *
 * Lexer implementation. Divides the string into an array of lexems & does minor
 * validation.
 *
 */
#ifndef SRC_LEXER_LEXER_H_
#define SRC_LEXER_LEXER_H_

#include "../includes/common.h"

struct Lexer {
    /**
     * @brief String source
     */
    char *source;
    /**
     * @brief Current index of the string pointer
     */
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

/**
 * @brief Getting a symbol in enum representation (* becomes MUL, 123 becomes
 * NUM)
 *
 * @param c Symbol to convert
 * @return Enum representation
 */
size_t get_symbol(char c);

/**
 * @brief Getting a function in enum representation (sin becomes SIN, etc)
 *
 * @param fun String to convert
 * @return Enum representation
 */
size_t get_fun(const char *fun);

#endif  // SRC_LEXER_LEXER_H_
