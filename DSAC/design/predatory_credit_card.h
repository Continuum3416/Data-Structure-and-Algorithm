#pragma once
#include <iostream>           // provides std::ostream
#include <string>             // provides std::string
#include <cmath>              // provides pow function
#include "credit_card.h"

namespace dsac::design {

/// A credit card that charges monthly interest and assesses fees
class PredatoryCreditCard : public CreditCard {
  private:
    double apr;               // annual percentage rate

  public:
    /// Constructs a new predatory credit card.
    PredatoryCreditCard(std::string cust, std::string bk, std::string acnt, int lim, double initial_bal, double rate)
        : CreditCard{cust, bk, acnt, lim, initial_bal}, apr{rate} {}

    /// Performs end-of-month processing, including compiling interest on an outstanding balance
    void process_month() {
        if (balance > 0) {               // only charge interest on a positive balance
            double monthly_factor = pow(1 + apr, 1.0/12);      // compute monthly rate
            balance *= monthly_factor;                         // assess interest
        }
    }
    
    /// Attempts to charge the give amount, assessing a $5 penalty if the charge fails
    /// @param price the amount to be charged
    /// @return a boolean which is true if the charge was successful, and false if the charge failed
    bool charge(double price) {
        bool is_success{CreditCard::charge(price)};            // call inherited version
        if (!is_success)
            balance += 5;                                      // assess a $5 penalty
        return is_success;
    }    

}; // PredatoryCreditCard class

}  // namespace dsac::design
