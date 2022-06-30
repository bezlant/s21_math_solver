#include "test_calc.h"

START_TEST(stack_create) {
}
END_TEST

Suite *suite_stack(void) {
    Suite *s = suite_create("suite_stack");
    TCase *tc = tcase_create("stack");

    tcase_add_test(tc, stack_create);

    suite_add_tcase(s, tc);
    return s;
}
