#ifndef VALIDATION_H_
#define VALIDATION_H_

#include "../includes/common.h"
#include "../stack/stack.h"
#include <pcre.h>

/**
 * @brief Checks if the string only has allowed characters
 *
 * @param str Given string
 * @return 1 if valid otherwise 0
 */
bool is_valid(char *str);

/**
 * @brief Check if brackets are all correct, i.e no ')())'
 *
 * @param tok All the tokens parsed
 * @return true if correct, false if incorrect
 */
bool brackets_ok(struct Tokens *tok);

/**
 * @brief Check if operators are in valid order, i.e no '*3+*1'
 *
 * @param tok All the tokens parsed
 * @return true if correct, false if incorrect
 */
bool operators_ok(struct Tokens *tok);

/**
 * @brief Check if numbers are all valid, i.e no '432 4332 + (4324'
 *
 * @param tok All the tokens parsed
 * @return true if correct, false if incorrect
 */
bool numbers_ok(struct Tokens *tok);

/**
 * @brief Check if functions are valie, i.e no 'sinx*cos'
 *
 * @param tok All the tokens parsed
 * @return true if correct, false otherwise
 */
bool functions_ok(struct Tokens *tok);
#endif  // VALIDATION_H_
