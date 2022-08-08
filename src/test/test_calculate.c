#include "test_calc.h"

START_TEST(simple) {
    char str[] = "1 * 5";
    struct Tokens *tok = tokenize(str);
    struct Tokens *res = convert_to_rpn(tok);

    ck_assert_float_eq(5.0f, calculate(res, 0));

    free_Tokens(tok);
}
END_TEST

START_TEST(medium) {
    char str[] = "(5 * 4 + 3 * 2) - 1";
    struct Tokens *tok = tokenize(str);
    size_t expected[23] = {L_BRACKET, NUM, MUL,       NUM, ADD, NUM,
                           MUL,       NUM, R_BRACKET, SUB, NUM};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    struct Tokens *res = convert_to_rpn(tok);
    size_t expected_polish[23] = {NUM, NUM, MUL, NUM, NUM, MUL, ADD, NUM, SUB};
    for (size_t i = 0; i < 9; i++)
        ck_assert_uint_eq(res->type[i], expected_polish[i]);

    ck_assert_float_eq(25.0f, calculate(res, 0));

    free_Tokens(tok);
}
END_TEST

START_TEST(funcs) {
    char str[] = "sin(x) * 1";
    struct Tokens *tok = tokenize(str);
    size_t expected[23] = {SIN, L_BRACKET, X, R_BRACKET, MUL, NUM};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    struct Tokens *res = convert_to_rpn(tok);
    size_t expected_polish[23] = {X, SIN, NUM, MUL};
    for (size_t i = 0; i < res->size; i++)
        ck_assert_uint_eq(res->type[i], expected_polish[i]);

    ck_assert_float_eq(0, calculate(res, 0));

    free_Tokens(tok);
}
END_TEST

START_TEST(pow_test) {
    char str[] = "5^2^3";
    struct Tokens *tok = tokenize(str);
    size_t expected[23] = {NUM, POW, NUM, POW, NUM};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    struct Tokens *res = convert_to_rpn(tok);
    size_t expected_polish[23] = {NUM, NUM, NUM, POW, POW};
    for (size_t i = 0; i < res->size; i++)
        ck_assert_uint_eq(res->type[i], expected_polish[i]);

    ck_assert_float_eq(390625, calculate(res, 0));

    free_Tokens(tok);
}
END_TEST

START_TEST(unary) {
    char str[] = "-5 * -3";
    struct Tokens *tok = tokenize(str);

    size_t expected[23] = {UNARY_SUB, NUM, MUL, UNARY_SUB, NUM};
    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    struct Tokens *res = convert_to_rpn(tok);
    size_t expected_polish[23] = {NUM, UNARY_SUB, NUM, UNARY_SUB, MUL};
    for (size_t i = 0; i < res->size; i++)
        ck_assert_uint_eq(res->type[i], expected_polish[i]);

    ck_assert_float_eq(15, calculate(res, 0));

    free_Tokens(tok);
}
END_TEST

Suite *suite_calculate(void) {
    Suite *s = suite_create("suite_calculate");
    TCase *tc = tcase_create("calculate");

    tcase_add_test(tc, simple);
    tcase_add_test(tc, medium);
    tcase_add_test(tc, funcs);
    tcase_add_test(tc, pow_test);
    tcase_add_test(tc, unary);

    suite_add_tcase(s, tc);
    return s;
}
