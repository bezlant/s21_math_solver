/**
 * @file credit_calc.h
 *
 * Custom credit calculator implementation *WIP*
 *
 */
#ifndef CREDIT_CALC_H_
#define CREDIT_CALC_H_

#include "../includes/common.h"

enum {
    ANNUITY,
    DIFFERENTIATED
};

/**
 * @brief Calculates a montly payment for a differentiated loan
 *
 * @param total Total money loaned
 * @param term Over which period in months
 * @return Montly pay amount
 */
long double differentiated_get_montly(long double total, unsigned int term);

/**
 * @brief Calculate total amount owed
 *
 * @param total_amount Loaned amount
 * @param term Over which period in months
 * @param interest_rate
 * @return Total amount owed
 */
long double differentiated_get_total(long double total_amount,
                                     unsigned int term,
                                     long double interest_rate);

/**
 * @brief Total amount owed for a annuity loan
 *
 * @param annuity Montly payment
 * @param term Period in months
 * @return Total
 */
long double annuity_get_montly(long double interest_rate, unsigned long term,
                               long double total_amount);

/**
 * @brief Calculate montly payment for annuity loan
 *
 * @param interest_rate
 * @param term Period in months
 * @param total_amount Total loaned
 * @return Montly pay amount
 */
long double annuity_get_total(long double annuity, unsigned int term);

/**
 * @brief Calculate the amount overpaid
 *
 * @param paid Total amount paid
 * @param loaned Total amout loaned
 * @return Difference between \p paid and \p loaned
 */
long double get_overpayment(long double paid, long double loaned);

#endif  // CREDIT_CALC_H_
