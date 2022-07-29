#ifndef CREDIT_CALC_H_
#define CREDIT_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    ANNUITY,
    DIFFERENTIATED
};

long double differentiated_get_montly(long double total, unsigned int term);
long double differentiated_get_total(long double total_amount,
                                     unsigned int term,
                                     long double interest_rate);
long double annuity_get_montly(long double interest_rate, unsigned long term,
                               long double total_amount);
long double annuity_get_total(long double annuity, unsigned int term);
long double get_overpayment(long double paid, long double loaned);

#endif  // CREDIT_CALC_H_
