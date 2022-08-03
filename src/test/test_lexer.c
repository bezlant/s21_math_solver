#include "test_calc.h"

START_TEST(simple) {
    char str[] = "sin(x) + 3 - 1 * 69 / sin(cos(ln(x))) % 15";
    struct Tokens *tok = tokenize(str);
    char expected[][23] = {
        "sin", "(",   "x", ")",  "+", "3", "-", "1", "*", "69", "/",  "sin",
        "(",   "cos", "(", "ln", "(", "x", ")", ")", ")", "%",  "15",
    };

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_str_eq(tok->token[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

START_TEST(not_simple) {
    char str[] = "1 + 3 + x - 2 / 7 * sin(x) + cos(2 / sin(x))";
    struct Tokens *tok = tokenize(str);
    char expected[][24] = {
        "1", "+", "3", "+",   "x", "-", "2", "/",   "7", "*", "sin", "(",
        "x", ")", "+", "cos", "(", "2", "/", "sin", "(", "x", ")",   ")",
    };

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_str_eq(tok->token[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

START_TEST(error) {
    char str[] = "____ 1 + 3 + x - 2 / 7 * sin(x) + cos(2 / sin(x))";
    struct Tokens *tok = tokenize(str);

    ck_assert_ptr_null(tok);
}
END_TEST

Suite *suite_lexer(void) {
    Suite *s = suite_create("suite_lexer");
    TCase *tc = tcase_create("lexer");

    tcase_add_test(tc, simple);
    tcase_add_test(tc, not_simple);
    tcase_add_test(tc, error);

    suite_add_tcase(s, tc);
    return s;
}
