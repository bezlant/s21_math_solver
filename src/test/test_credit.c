#include "test_calc.h"

START_TEST(annuity) {
    long double loan_amount = 42069.69;
    long double interest_rate = 4.20;
    size_t term = 69;
    char buff[40] = "";
    long double montly = annuity_get_montly(interest_rate, term, loan_amount);

    snprintf(buff, sizeof(buff), "%.2Lf", montly);
    sscanf(buff, "%Lf", &montly);

    ck_assert_ldouble_eq(montly, 687.35L);
    long double total = annuity_get_total(montly, term);
    ck_assert_ldouble_eq(total, 47427.15L);
    long double overpaid = get_overpayment(total, loan_amount);
    ck_assert_ldouble_eq_tol(overpaid, 5357.46L, 1e-2);
}
END_TEST

START_TEST(differentiated) {
    long double loan_amount = 42069.69;
    long double interest_rate = 4.20;
    size_t term = 69;
    char buff[40] = "";
    long double total =
        differentiated_get_total(loan_amount, term, interest_rate);
    snprintf(buff, sizeof(buff), "%.2Lf", total);
    sscanf(buff, "%Lf", &total);
    ck_assert_ldouble_eq(total, 47223.23L);

    long double montly = differentiated_get_montly(total, term);
    snprintf(buff, sizeof(buff), "%.2Lf", montly);
    sscanf(buff, "%Lf", &montly);
    ck_assert_ldouble_eq(montly, 684.39L);

    long double overpaid = get_overpayment(total, loan_amount);
    ck_assert_ldouble_eq_tol(overpaid, 5153.54L, 1e-2);
}
END_TEST

Suite *suite_credit(void) {
    Suite *s = suite_create("suite_credit");
    TCase *tc = tcase_create("credit");

    tcase_add_test(tc, annuity);
    tcase_add_test(tc, differentiated);

    suite_add_tcase(s, tc);
    return s;
}
