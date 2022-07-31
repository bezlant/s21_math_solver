#include "deposit_calc.h"

/**
 * @brief Get earnings before taxes
 *
 * @param sum Initial deposit
 * @param term Deposit time
 * @param interest_rate Percentage
 * @param capitalized Whether reinvest or not
 * @param periodicity Montly or Yearly
 * @param replenish How much we replenish monthly
 * @param withdraw How much we withdraw monthly
 * @return Amount of earnings
 */
long double get_earnings(long double *sum, size_t term,
                         long double interest_rate, bool capitalized,
                         bool periodicity, long double replenish,
                         long double withdraw) {
    long double earnings = 0;
    // Implement replenishment & withdrawal
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

/**
 * @brief Calculate taxes according to yearly tax rate
 *
 * @param earnings Overall earning
 * @param tax_rate Yearly tax rate in percentages
 * @return Amount of taxes need to be paid
 */
long double get_tax(long double earnings, long double tax_rate) {
    return earnings * tax_rate / 100;
}

/**
 * @brief Get deposit amount by the end of the period
 *
 * @param base Initial Deposit
 * @param earnings Earnings before tax
 * @return Current balance before tax
 */
long double get_overall(long double base, long double earnings) {
    return base + earnings;
}
