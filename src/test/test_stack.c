#include "test_calc.h"

START_TEST(stack_create) {
    struct my_stack *s = NULL;
    s = init_stack();
    ck_assert_ptr_ne(s, NULL);
    my_stack_free(s);
}
END_TEST

START_TEST(stack_push) {
    struct my_stack *s = NULL;
    s = init_stack();
    ck_assert_ptr_ne(s, NULL);

    for (int i = 0; i < STACK_SIZE; i++) {
        push(s, i);
        ck_assert_ldouble_eq(s->stack[i], i);
    }
    my_stack_free(s);
}
END_TEST

START_TEST(stack_pop) {
    struct my_stack *s = NULL;
    s = init_stack();
    ck_assert_ptr_ne(s, NULL);

    for (int i = 0; i < STACK_SIZE; i++) {
        push(s, i);
        ck_assert_ldouble_eq(s->stack[i], i);
    }

    for (int i = STACK_SIZE - 1; i >= 0; i--)
        ck_assert_ldouble_eq(pop(s), i);

    my_stack_free(s);
}
END_TEST

START_TEST(stack_is_empty) {
    struct my_stack *s = NULL;
    s = init_stack();
    ck_assert_ptr_ne(s, NULL);

    ck_assert_int_eq(is_empty(s), true);

    my_stack_free(s);
}
END_TEST

START_TEST(stack_peek) {
    struct my_stack *s = NULL;
    s = init_stack();
    ck_assert_ptr_ne(s, NULL);

    int val = 69;
    push(s, val);

    ck_assert_int_eq(is_empty(s), false);
    ck_assert_ldouble_eq(peek(s), val);
    ck_assert_ldouble_eq(pop(s), val);
    ck_assert_int_eq(is_empty(s), true);

    my_stack_free(s);
}
END_TEST

Suite *suite_stack(void) {
    Suite *s = suite_create("suite_stack");
    TCase *tc = tcase_create("stack");

    tcase_add_test(tc, stack_create);
    tcase_add_test(tc, stack_push);
    tcase_add_test(tc, stack_pop);
    tcase_add_test(tc, stack_is_empty);
    tcase_add_test(tc, stack_peek);

    suite_add_tcase(s, tc);
    return s;
}
