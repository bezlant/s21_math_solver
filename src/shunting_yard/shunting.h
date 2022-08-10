/**
 * @file shunting.h
 *
 * Shunting yard algorithm implementation
 *
 */
#ifndef SHUNTING_H_
#define SHUNTING_H_

#include "../includes/common.h"
#include "../stack/stack.h"

/**
 * @brief Converts tokens to the reverse polish notation
 *
 * @param expression Tokens for our expression, i.e 'NUM ADD NUM'
 * @return Tokens in reverse polish notation
 */
struct Tokens *convert_to_rpn(struct Tokens *expression);

#endif  // SHUNTING_H_
