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

bool brackets_ok(struct Tokens *tok);

bool operators_ok(struct Tokens *tok);

bool numbers_ok(struct Tokens *tok);

bool functions_ok(struct Tokens *tok);
#endif  // VALIDATION_H_
