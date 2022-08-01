#ifndef TEST_CALC_H_
#define TEST_CALC_H_

#include "../credit_calc/credit_calc.h"
#include "../deposit_calc/deposit_calc.h"
#include "../stack/stack.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Suite *suite_stack(void);
Suite *suite_deposit(void);
Suite *suite_credit(void);

void run_tests(void);
void run_testcase(Suite *testcase);

double get_rand(double min, double max);

#endif  //  TEST_CALC_H_
