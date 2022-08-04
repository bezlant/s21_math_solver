#ifndef CALC_H_
#define CALC_H_

#include "../credit_calc/credit_calc.h"
#include "../deposit_calc/deposit_calc.h"
#include "../parser/lexer.h"
#include "../parser/parser.h"
#include "common.h"

/**
 * @brief Helps figure out what error occured in glfw
 *
 * @param error Error code
 * @param description String with error description
 */
void glfw_error_callback(int error, const char *description);

/**
 * @brief Deposit calc gui implementation
 *
 * @param show_deposit_window Switch show / hide
 */
void show_deposit_calc(bool &show_deposit_window);

/**
 * @brief Deposit calc gui implementation
 *
 * @param show_credit_window Switch show / hide
 */
void show_credit_calc(bool &show_credit_window);

/**
 * @brief Draws a table with all available operators & functions
 *
 * @param height Height of each column
 */
void draw_help_table(float height);

#endif  // CALC_H_
