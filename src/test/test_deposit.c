#include "test_calc.h"

// long double get_earnings(long double *sum, size_t term,
//                          long double interest_rate, bool capitalized,
//                          bool periodicity, long double replenish,
//                          long double withdraw);
//
// long double get_tax(long double earnings, long double tax_rate);
//
// long double get_overall(long double base, long double earnings);

START_TEST(deposit) {
    long double init = 69420.0;
    long double interest_rate = 6.9;
    long double replenish = 690;
    size_t term = 69;
    long double tax_rate = 0;
    char buff[40] = "";

    long double earned =
        get_earnings(&init, term, interest_rate, 0, MONTHLY, replenish, 0);

    snprintf(buff, sizeof(buff), "%.2Lf", earned);
    sscanf(buff, "%Lf", &earned);

    ck_assert_ldouble_eq(earned, 36850.14L);

    long double tax = get_tax(earned, tax_rate);
    ck_assert_ldouble_eq(tax, 0L);

    long double overall = get_overall(init, earned);
    ck_assert_ldouble_eq_tol(overall, 153880.14, 1e-2);
}
END_TEST

START_TEST(deposit_capitalization) {
    long double init = 69420.0;
    long double interest_rate = 6.9;
    long double replenish = 690;
    size_t term = 69;
    long double tax_rate = 4.20;
    char buff[40] = "";

    long double earned =
        get_earnings(&init, term, interest_rate, 1, MONTHLY, replenish, 0);

    snprintf(buff, sizeof(buff), "%.2Lf", earned);
    sscanf(buff, "%Lf", &earned);

    ck_assert_ldouble_eq(earned, 44314.66L);

    long double tax = get_tax(earned, tax_rate);
    snprintf(buff, sizeof(buff), "%.2Lf", tax);
    sscanf(buff, "%Lf", &tax);

    ck_assert_ldouble_eq(tax, 1861.22L);

    long double overall = get_overall(init, earned);
    snprintf(buff, sizeof(buff), "%.2Lf", overall - tax);
    sscanf(buff, "%Lf", &overall);
    ck_assert_ldouble_eq_tol(overall, 203798L, 1e0);
}
END_TEST

START_TEST(deposit_yearly) {
    long double init = 69420.0;
    long double interest_rate = 6.9;
    long double withdraw = 100;
    size_t term = 69;
    long double tax_rate = 4.20;
    char buff[40] = "";

    long double earned =
        get_earnings(&init, term, interest_rate, 0, YEARLY, 0, withdraw);

    snprintf(buff, sizeof(buff), "%.2Lf", earned);
    sscanf(buff, "%Lf", &earned);

    ck_assert_ldouble_eq(earned, 136259.82L);

    long double tax = get_tax(earned, tax_rate);
    snprintf(buff, sizeof(buff), "%.2Lf", tax);
    sscanf(buff, "%Lf", &tax);

    ck_assert_ldouble_eq(tax, 5722.91L);

    long double overall = get_overall(init, earned);
    snprintf(buff, sizeof(buff), "%.2Lf", overall - tax);
    sscanf(buff, "%Lf", &overall);
    ck_assert_ldouble_eq_tol(overall, 117156.91L, 1e0);
}
END_TEST

Suite *suite_deposit(void) {
    Suite *s = suite_create("suite_deposit");
    TCase *tc = tcase_create("deposit");

    tcase_add_test(tc, deposit);
    tcase_add_test(tc, deposit_yearly);
    tcase_add_test(tc, deposit_capitalization);

    suite_add_tcase(s, tc);
    return s;
}
