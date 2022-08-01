#ifndef CALC_H_
#define CALC_H_

#include "../credit_calc/credit_calc.h"
#include "../deposit_calc/deposit_calc.h"
#include "../stack/stack.h"
#include "common.h"

void glfw_error_callback(int error, const char *description);
void show_deposit_calc(bool &show_deposit_window);
void show_credit_calc(bool &show_credit_window);

#endif  // CALC_H_
