#ifndef TEST_CALC_H_
#define TEST_CALC_H_

#include "../stack/stack.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Suite *suite_stack(void);

void run_tests(void);
void run_testcase(Suite *testcase);

double get_rand(double min, double max);
#endif  //  TEST_CALC_H_
