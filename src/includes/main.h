/**
 * @file main.h
 *
 * All the includes needed for the main
 *
 */
#ifndef MAIN_H_
#define MAIN_H_

#include "../calc/calc.h"
#include "../credit_calc/credit_calc.h"
#include "../deposit_calc/deposit_calc.h"
#include "../lexer/lexer.h"
#include "../shunting_yard/shunting.h"
#include "../validation/validation.h"
#include "common.h"
#include "gui.h"

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

#endif  // MAIN_H_
