#ifndef DEPOSIT_CALC_H_
#define DEPOSIT_CALC_H_

#include "../includes/common.h"

enum {
    MONTHLY,
    YEARLY
};

long double get_earnings(long double *sum, size_t term,
                         long double interest_rate, bool capitalized,
                         bool periodicity, long double replenish,
                         long double withdraw);

long double get_tax(long double earnings, long double tax_rate);

long double get_overall(long double base, long double earnings);

#endif  // DEPOSIT_CALC_H_
