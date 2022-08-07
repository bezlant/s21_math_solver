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
    struct Tokens *res = convert_to_rpn(tok);

    ck_assert_float_eq(25.0f, calculate(res, 0));

    free_Tokens(tok);
}
END_TEST

// START_TEST(funcs) {
//     char str[] = "sin(x) * 1";
//     struct Tokens *tok = tokenize(str);
//     char expected[][25] = {"x", "sin", "1", "*"};
//     char **res = convert_to_rpn(tok->token, tok->size);
//
//     for (size_t i = 0; i < tok->size - 2; i++)
//         ck_assert_str_eq(res[i], expected[i]);
//
//     ck_assert_float_eq(0, calculate(res, 0));
//
//     free_Tokens(tok);
// }
// END_TEST
//
// START_TEST(pow_test) {
//     char str[] = "5^2^3";
//     struct Tokens *tok = tokenize(str);
//     char expected[][25] = {"5", "2", "3", "^", "^"};
//     char **res = convert_to_rpn(tok->token, tok->size);
//
//     for (size_t i = 0; i < tok->size; i++)
//         ck_assert_str_eq(res[i], expected[i]);
//
//     ck_assert_float_eq(390625.0f, calculate(res, 0));
//
//     free_Tokens(tok);
// }
// END_TEST
//
// START_TEST(unary) {
//     char str[] = "-5 * -3";
//     struct Tokens *tok = tokenize(str);
//     char expected[][25] = {"5", "~", "3", "~", "*"};
//     char **res = convert_to_rpn(tok->token, tok->size);
//
//     for (size_t i = 0; i < tok->size; i++)
//         ck_assert_str_eq(res[i], expected[i]);
//
//     ck_assert_float_eq(15, calculate(res, 0));
//
//     free_Tokens(tok);
// }
// END_TEST
//
Suite *suite_calculate(void) {
    Suite *s = suite_create("suite_calculate");
    TCase *tc = tcase_create("calculate");

    tcase_add_test(tc, simple);
    tcase_add_test(tc, medium);
    // tcase_add_test(tc, funcs);
    // tcase_add_test(tc, pow_test);
    // tcase_add_test(tc, unary);

    suite_add_tcase(s, tc);
    return s;
}
