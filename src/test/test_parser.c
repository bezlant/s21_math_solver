#include "test_calc.h"

// START_TEST(simple) {
//     char str[] = "1 * 5";
//     struct Tokens *tok = tokenize(str);
//
//     size_t expected[] = {NUM, NUM, MUL};
//     struct Tokens *res = convert_to_rpn(tok);
//
//     for (size_t i = 0; i < res->size; i++)
//         ck_assert_uint_eq(res->type[i], expected[i]);
//
//     free_Tokens(tok);
// }
// END_TEST

START_TEST(simple_brackets) {
    char str[] = "( 1 + 5 ) * 3";
    struct Tokens *tok = tokenize(str);

    size_t expected[] = {NUM, NUM, ADD, NUM, MUL};
    struct Tokens *res = convert_to_rpn(tok);

    for (size_t i = 0; i < res->size; i++)
        ck_assert_uint_eq(res->type[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

// START_TEST(medium) {
//     char str[] = "(5 * 4 + 3 * 2) - 1";
//     struct Tokens *tok = tokenize(str);
//
//     size_t expected[] = {NUM, NUM, MUL, NUM, NUM, MUL, ADD, NUM, SUB};
//     struct Tokens *res = convert_to_rpn(tok);
//
//     for (size_t i = 0; i < tok->size - 2; i++)
//         ck_assert_uint_eq(res->type[i], expected[i]);
//
//     free_Tokens(tok);
// }
// END_TEST

// START_TEST(funcs) {
//     char str[] = "sin(x) * 1";
//     struct Tokens *tok = tokenize(str);
//     char expected[][25] = {"x", "sin", "1", "*"};
//     char **res = convert_to_rpn(tok->token, tok->size);
//
//     for (size_t i = 0; i < tok->size - 2; i++)
//         ck_assert_str_eq(res[i], expected[i]);
//
//     free_Tokens(tok);
// }
// END_TEST
//
// START_TEST(sincos) {
//     char str[] = "sin(cos(x))";
//     struct Tokens *tok = tokenize(str);
//     char expected[][25] = {"x", "cos", "sin"};
//     char **res = convert_to_rpn(tok->token, tok->size);
//
//     for (size_t i = 0; i < tok->size - 4; i++)
//         //     printf("%s\n", res[i]);
//         // puts("");
//         ck_assert_str_eq(res[i], expected[i]);
//
//     free_Tokens(tok);
// }
// END_TEST
//
Suite *suite_parser(void) {
    Suite *s = suite_create("suite_parser");
    TCase *tc = tcase_create("parser");

    // tcase_add_test(tc, simple);
    tcase_add_test(tc, simple_brackets);
    // tcase_add_test(tc, medium);
    // tcase_add_test(tc, funcs);
    // tcase_add_test(tc, sincos);

    suite_add_tcase(s, tc);
    return s;
}
