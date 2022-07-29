#include "credit_calc.h"

long double differentiated_get_montly(long double total, unsigned int term) {
    return total / term;
}

long double differentiated_get_total(long double total_amount,
                                     unsigned int term,
                                     long double interest_rate) {
    long double fixed_montly_payment = total_amount / term;
    long double total_payment = 0.0L;
    for (size_t month = 0; month < term; month++) {
        long double left_to_pay = total_amount - (fixed_montly_payment * month);

        long double interest_payment = left_to_pay * (interest_rate / 100 / 12);

        long double montly_payment = fixed_montly_payment + interest_payment;

        total_payment += montly_payment;
    }
    return total_payment;
}

long double annuity_get_total(long double annuity, unsigned int term) {
    return annuity * term;
}

long double annuity_get_montly(long double interest_rate, unsigned long term,
                               long double total_amount) {
    long double monthly_percentage = interest_rate / 12 / 100;

    long double annuity_coefficent = monthly_percentage *
                                     powl(1 + monthly_percentage, term) /
                                     (powl(1 + monthly_percentage, term) - 1);

    long double annuity = annuity_coefficent * total_amount;

    return annuity;
}

long double get_overpayment(long double paid, long double loaned) {
    return paid - loaned;
}
