#include "test_calc.h"

START_TEST(simple) {
    char str[] = "sin(x) + 3 - 1 * 69 / sin(cos(ln(x))) % 15";
    struct Tokens *tok = tokenize(str);
    size_t expected[23] = {
        SIN,       L_BRACKET, X,         R_BRACKET, ADD,       NUM,
        SUB,       NUM,       MUL,       NUM,       DIV,       SIN,
        L_BRACKET, COS,       L_BRACKET, LN,        L_BRACKET, X,
        R_BRACKET, R_BRACKET, R_BRACKET, MOD,       NUM,
    };

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

START_TEST(not_simple) {
    char str[] = "1 + 3 + x - 2 / 7 * sin(x) + cos(2 / sin(x))";
    struct Tokens *tok = tokenize(str);
    size_t expected[24] = {
        NUM, ADD, NUM,       ADD, X,         SUB,      NUM, DIV,       NUM,
        MUL, SIN, L_BRACKET, X,   R_BRACKET, ADD,      COS, L_BRACKET, NUM,
        DIV, SIN, L_BRACKET, X,   R_BRACKET, R_BRACKET};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

START_TEST(no_spaces) {
    char str[] = "3*2+3*2";
    struct Tokens *tok = tokenize(str);
    size_t expected[24] = {NUM, MUL, NUM, ADD, NUM, MUL, NUM};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

START_TEST(unary_minus) {
    char str[] = "-(3 + 2)";
    struct Tokens *tok = tokenize(str);
    size_t expected[24] = {UNARY_SUB, L_BRACKET, NUM, ADD, NUM, R_BRACKET};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

START_TEST(complex_unary_minus) {
    char str[] = "3-(-(3 + 2))";
    struct Tokens *tok = tokenize(str);
    size_t expected[24] = {NUM, SUB, L_BRACKET, UNARY_SUB, L_BRACKET,
                           NUM, ADD, NUM,       R_BRACKET, R_BRACKET};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

START_TEST(unary_plus) {
    char str[] = "+3 - 2";
    struct Tokens *tok = tokenize(str);
    size_t expected[24] = {UNARY_ADD, NUM, SUB, NUM};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

START_TEST(complex_unary_plus) {
    char str[] = "+3+(+(3 + 2))";
    struct Tokens *tok = tokenize(str);
    size_t expected[24] = {UNARY_ADD, NUM, ADD, L_BRACKET, UNARY_ADD, L_BRACKET,
                           NUM,       ADD, NUM, R_BRACKET, R_BRACKET};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

START_TEST(complex_unary_plus_x) {
    char str[] = "sin(x)+3+(+(3 + 2))";
    struct Tokens *tok = tokenize(str);
    size_t expected[24] = {SIN, L_BRACKET, X,         R_BRACKET, ADD,
                           NUM, ADD,       L_BRACKET, UNARY_ADD, L_BRACKET,
                           NUM, ADD,       NUM,       R_BRACKET, R_BRACKET};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

START_TEST(simple_sin) {
    char str[] = "sin(x) + 1";
    struct Tokens *tok = tokenize(str);
    size_t expected[24] = {SIN, L_BRACKET, X, R_BRACKET, ADD, NUM};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

START_TEST(sincos) {
    char str[] = "sin(cos(x))";
    struct Tokens *tok = tokenize(str);
    size_t expected[24] = {SIN, L_BRACKET, COS,      L_BRACKET,
                           X,   R_BRACKET, R_BRACKET};

    for (size_t i = 0; i < tok->size; i++)
        ck_assert_uint_eq(tok->type[i], expected[i]);

    free_Tokens(tok);
}
END_TEST

Suite *suite_lexer(void) {
    Suite *s = suite_create("suite_lexer");
    TCase *tc = tcase_create("lexer");

    tcase_add_test(tc, simple);
    tcase_add_test(tc, not_simple);
    tcase_add_test(tc, no_spaces);
    tcase_add_test(tc, unary_minus);
    tcase_add_test(tc, complex_unary_minus);
    tcase_add_test(tc, unary_plus);
    tcase_add_test(tc, complex_unary_plus);
    tcase_add_test(tc, complex_unary_plus_x);
    tcase_add_test(tc, simple_sin);
    tcase_add_test(tc, sincos);

    suite_add_tcase(s, tc);
    return s;
}
