/**
 * @file calc.h
 *
 * Math expression evalutator (from reverse polish notation to result)
 *
 */
#ifndef SRC_CALC_CALC_H_
#define SRC_CALC_CALC_H_

#include "../includes/common.h"
#include "../stack/stack.h"

/**
 * @brief Reverse polish notation to result
 *
 * @param expr Expression in reverse polish notation
 * @param x If drawing a graph current X value
 */
long double calculate(struct Tokens *expr, long double x);

/**
 * @brief Simply sums up two values
 *
 * @param a Value to sum up
 * @param b Value to sum up
 */
long double eval_add(long double a, long double b);

/**
 * @brief Simply subtracts two values
 *
 * @param a Minuend
 * @param b Subtrahend
 */
long double eval_sub(long double a, long double b);

/**
 * @brief Simply sums up two values
 *
 * @param a Value to sum up
 * @param b Value to sum up
 */
long double eval_mul(long double a, long double b);

/**
 * @brief Simply multiplies two values
 *
 * @param a Value to multiply
 * @param b Value to multiply
 */
long double eval_div(long double a, long double b);

/**
 * @brief Simply divides two values
 *
 * @param a Dividend
 * @param b Divisor
 */
long double eval_pow(long double a, long double b);

/**
 * @brief Rases the base to the power of exponent
 *
 * @param a Base
 * @param b Exponent
 */
long double eval_mod(long double a, long double b);

/**
 * @brief Gets remainder of the divison
 *
 * @param a Divident
 * @param b Divisor
 */
long double eval_uadd(long double a, long double b);

/**
 * @brief Result of unary addition
 *
 * @param a Value to apply unary addition on
 * @param b Always zero in this case
 */
long double eval_usub(long double a, long double b);

/**
 * @brief Result of unary subtraction
 *
 * @param a Value to apply unary subtraction on
 * @param b Always zero in this case
 */
long double eval_cos(long double a, long double b);

/**
 * @brief Get cos of a given value
 *
 * @param a Value for cos
 * @param b Always zero in this case
 */
long double eval_sin(long double a, long double b);

/**
 * @brief Get sin of a given value
 *
 * @param a Value for sin
 * @param b Always zero in this case
 */
long double eval_tan(long double a, long double b);

/**
 * @brief Get tan of a given value
 *
 * @param a Value for tan
 * @param b Always zero in this case
 */
long double eval_arccos(long double a, long double b);

/**
 * @brief Get arcsin of a give value
 *
 * @param a Value for arcsin
 * @param b Always zero in this case
 */
long double eval_arcsin(long double a, long double b);

/**
 * @brief Get arctan of a given value
 *
 * @param a Value for arctan
 * @param b Always zero in this case
 */
long double eval_arctan(long double a, long double b);

/**
 * @brief Get square root of a given value
 *
 * @param a Value for sqrt
 * @param b Always zero in this case
 */
long double eval_sqrt(long double a, long double b);

/**
 * @brief Evaluate logarithm base e
 *
 * @param a Value for ln
 * @param b Always zero in this case
 */
long double eval_ln(long double a, long double b);

/**
 * @brief Evaluate logarithm base 10
 *
 * @param a Value for log
 * @param b Always zero in this case
 */
long double eval_log(long double a, long double b);

#endif  // SRC_CALC_CALC_H_
