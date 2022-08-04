#include "deposit_calc.h"

long double get_earnings(long double *sum, size_t term,
                         long double interest_rate, bool capitalized,
                         bool periodicity, long double replenish,
                         long double withdraw) {
    long double earnings = 0;
    size_t period = (periodicity == MONTHLY ? 12 : 1);
    replenish = (periodicity == MONTHLY ? replenish : replenish * 12);
    withdraw = (periodicity == MONTHLY ? withdraw : withdraw * 12);

    for (size_t i = 0; i < term; i++) {
        long double current_earnings = *sum * interest_rate / 100 / period;
        *sum += replenish;
        *sum -= withdraw;

        if (capitalized)
            *sum += current_earnings;

        earnings += current_earnings;
    }
    return earnings;
}

long double get_tax(long double earnings, long double tax_rate) {
    return earnings * tax_rate / 100;
}

long double get_overall(long double base, long double earnings) {
    return base + earnings;
}
