#pragma once
#include <iostream>           // provides std::ostream
#include <string>             // provides std::string
#include <vector>

namespace dsac::design {

/// A customer credit card
class CreditCard {
  private:
    std::string customer;     // name of the customer (e.g., "John Bowman")
    std::string bank;         // name of the bank (e.g., "California Savings")
    std::string account;      // account identifier (e.g., "5391 0375 9387 5309")
    int limit;                // credit limit (measured in dollars)
    static int object_count;
  protected:
    double balance;           // current balance (measured in dollars)
    

  public:
    /// Constructs a new credit card. The initial balance is 0.0 by default.
    CreditCard(std::string cust, std::string bk, std::string acnt, int lim, double initial_bal = 0.0):
        customer{cust}, // customer name 
        bank {bk},       // bank name
        account {acnt},  // account num
        limit  {lim},     // credit limit
        balance{initial_bal}{
            object_count++;
        } // balance
        

    
    void printOjbCounter(){
        std::cout << "Credit card #" << object_count << std::endl;
    }
    
    //we don't need multiple constructors like in java, any value that's not invoked is automatically set to 0
    // do that (above) or this:
    
    // CreditCard(std::string cust, std::string bk, std::string acnt, int lim, double initial_bal = 0.0) {
    //     customer = cust;  // assignment
    //     bank = bk;        // assignment
    //     account = acnt;   // assignment
    //     limit = lim;      // assignment
    //     balance = initial_bal; // assignment
    // }
        
    // ------------- Accessors -------------
    
    std::string get_customer() const { return customer; }
    std::string get_bank() const { return bank; }
    std::string get_account() const { return account; }
    int get_limit() const { return limit; }
    double get_balance() const { return balance; }
    double get_initial_balance() const { return balance; }

    // ------------- Mutators -------------

    /// Charges the give price to the card, assuming sufficient credit limit.
    /// @param price  the amount to be charged
    /// @return true if charge was accepted; false if charge was denied
    bool charge(double price) {
        if (price + balance > limit)                      // if charge would surpass limit
            return false;                                 // refuse the charge
        // at this point, the charge is successful
        balance += price;                                 // update the balance
        return true;                                      // announce the good news
    }

    /// Processes customer payment to reduce the balance
    /// @param amount the amount to pay down the balance
    void make_payment(double amount) { 
        balance -= amount; 
    }
    
    double addMonthlyInterest(){
        if(balance <= 0)
            return 0;
        double interest_rate = 0.15;  // 15% annualy interest rate
        double interest =  (balance * interest_rate)/12;
        balance = balance + interest;
        return interest;
    }

    // ------------- Overloaded output operator (as friend) -------------

    /// Displays the credit card to an output stream
    /// @param out the output stream
    /// @param c the credit card
    /// @return the resulting output stream
    friend std::ostream& operator<<(std::ostream& out, const CreditCard& c) {
        out << "Customer = " << c.customer << std::endl;
        out << "Bank = " << c.bank << std::endl;
        out << "Account = " << c.account << std::endl;
        out << "Balance = " << c.balance << std::endl;
        out << "Limit = " << c.limit << std::endl;
        return out;
    }
    

}; // CreditCard class

}  // namespace dsac::design
