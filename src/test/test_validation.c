#include "test_calc.h"

START_TEST(validate_regex_1) {
    char str[] = "sin(x) * cos(x) * hello";
    ck_assert_int_eq(is_valid(str), false);
}
END_TEST

START_TEST(validate_regex_2) {
    char str[] = "sin(x) * cos(x) * x + ln(x) + 32.323211";
    ck_assert_int_eq(is_valid(str), true);
}
END_TEST

START_TEST(validate_brackets_1) {
    char str[] = "sin(x)) * cos (x) * x";
    ck_assert_int_eq(operators_ok(tokenize(str)), true);
    ck_assert_int_eq(brackets_ok(tokenize(str)), false);
}
END_TEST

START_TEST(validate_brackets_2) {
    char str[] = "(sin(x)) * cos (x) * x + 32.12 - (-1)";
    ck_assert_int_eq(operators_ok(tokenize(str)), true);
    ck_assert_int_eq(brackets_ok(tokenize(str)), true);
}
END_TEST

START_TEST(validate_brackets_3) {
    char str[] = "((())))())))";
    ck_assert_int_eq(operators_ok(tokenize(str)), true);
    ck_assert_int_eq(brackets_ok(tokenize(str)), false);
}
END_TEST

START_TEST(validate_brackets_4) {
    char str[] = ")";
    ck_assert_int_eq(operators_ok(tokenize(str)), true);
    ck_assert_int_eq(brackets_ok(tokenize(str)), false);
}
END_TEST

START_TEST(validate_brackets_5) {
    char str[] = "()";
    ck_assert_int_eq(operators_ok(tokenize(str)), true);
    ck_assert_int_eq(brackets_ok(tokenize(str)), false);
}
END_TEST

START_TEST(validate_operators_1) {
    char str[] = "1 + 1 * 3";
    ck_assert_int_eq(operators_ok(tokenize(str)), true);
    ck_assert_int_eq(brackets_ok(tokenize(str)), true);
}
END_TEST

START_TEST(validate_operators_2) {
    char str[] = "1 + 1 * 3 * ";
    ck_assert_int_eq(operators_ok(tokenize(str)), false);
    ck_assert_int_eq(brackets_ok(tokenize(str)), true);
}
END_TEST

START_TEST(validate_operators_3) {
    char str[] = "-1 + 1 * (-3) * 1";
    ck_assert_int_eq(brackets_ok(tokenize(str)), true);
    ck_assert_int_eq(operators_ok(tokenize(str)), true);
}
END_TEST

START_TEST(validate_operators_4) {
    char str[] = "-1 + 1 * (-3) * 1 * sin(x) + ((x + 23))";
    ck_assert_int_eq(brackets_ok(tokenize(str)), true);
    ck_assert_int_eq(operators_ok(tokenize(str)), true);
}
END_TEST

START_TEST(validate_operators_5) {
    char str[] = "-1 + 1 * (-3) * 1 * sin(x) + ((x + ))";
    ck_assert_int_eq(brackets_ok(tokenize(str)), true);
    ck_assert_int_eq(operators_ok(tokenize(str)), false);
}
END_TEST

START_TEST(validate_numbers_1) {
    char str[] = "32..43 + 3.2";
    ck_assert_int_eq(is_valid(str), false);
}
END_TEST

START_TEST(validate_numbers_2) {
    char str[] = "3.5 * 3.9";
    ck_assert_int_eq(is_valid(str), true);
}
END_TEST

START_TEST(validate_numbers_3) {
    char str[] = "3.5 * 3.9 45";
    ck_assert_int_eq(numbers_ok(tokenize(str)), false);
}
END_TEST

START_TEST(validate_numbers_4) {
    char str[] = "3.5 * 3.9 * 32 + 3 3";
    ck_assert_int_eq(numbers_ok(tokenize(str)), false);
}
END_TEST

START_TEST(validate_numbers_5) {
    char str[] = "3.5 * 3.9 * 32 + 3 x";
    ck_assert_int_eq(numbers_ok(tokenize(str)), false);
}
END_TEST

Suite *suite_validation(void) {
    Suite *s = suite_create("suite_validation");
    TCase *tc = tcase_create("validation");

    tcase_add_test(tc, validate_regex_1);
    tcase_add_test(tc, validate_regex_2);
    tcase_add_test(tc, validate_brackets_1);
    tcase_add_test(tc, validate_brackets_2);
    tcase_add_test(tc, validate_brackets_3);
    tcase_add_test(tc, validate_brackets_4);
    tcase_add_test(tc, validate_brackets_5);
    tcase_add_test(tc, validate_operators_1);
    tcase_add_test(tc, validate_operators_2);
    tcase_add_test(tc, validate_operators_3);
    tcase_add_test(tc, validate_operators_4);
    tcase_add_test(tc, validate_operators_5);
    tcase_add_test(tc, validate_numbers_1);
    tcase_add_test(tc, validate_numbers_2);
    tcase_add_test(tc, validate_numbers_3);
    tcase_add_test(tc, validate_numbers_4);
    tcase_add_test(tc, validate_numbers_5);

    suite_add_tcase(s, tc);
    return s;
}
