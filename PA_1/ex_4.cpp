#include <cstdlib>            // provides EXIT_SUCCESS
#include <iostream>           // provides std::iostream
#include "credit_card.h"
#include <iomanip>

using dsac::design::CreditCard;
using namespace std;

void CreditCard_(CreditCard card){
    //cc.printOjbCounter();
    for (int month = 1; month <= 6; month++) {
        int num_of_charges;
        std::cout << "Enter numbers of charges: ";
        std::cin >> num_of_charges;
        std::cout << "Number of Charge for Month " << month << ": " << num_of_charges<< std::endl;
        for (int c = 1; c <= num_of_charges; c++) {
            double charge_amount;
            std::cout << "Enter amount of charge: ";
            std::cin >> charge_amount;
            std::cout << "Charge " << c << " Amount: " << charge_amount << std::endl;
            card.charge(charge_amount);
        }
        double payment_amount;
        std::cout << "Enter payment amount: ";
        std::cin >> payment_amount;
        std::cout << "Payment Amount: " << payment_amount << std::endl;
        card.make_payment(payment_amount);
        std::cout << "Current Balance: " << card.get_balance() << std::endl;
        std::cout << "Interest for this Month: " << card.addMonthlyInterest() << std::endl;
        std::cout << "Current Balance: " << card.get_balance() << std::endl << std::endl;
    }
}

int dsac::design::CreditCard::object_count = 0;

int main() {
    cout << std::fixed << std::setprecision(2);
    CreditCard card1 = CreditCard("John Bowman", "Bofa", "5391 0375 9387 5309", 2000, 0);
    card1.printOjbCounter();
    CreditCard_(card1);
    
    CreditCard card2 = CreditCard("Clark Kent", "Bofa", "5391 0375 9387 5309", 3000, 100);
    card2.printOjbCounter();
    CreditCard_(card2);

    

    return EXIT_SUCCESS;
}







/*
Output of main:

Customer = John Bowman
Bank = California Savings
Account = 5391 0375 9387 5309
Balance = 408
Limit = 5000
New balance = 208
New balance = 8
Customer = John Bowman
Bank = California Federal
Account = 3485 0399 3395 1954
Balance = 272
Limit = 3500
New balance = 72
Customer = John Bowman
Bank = California Finance
Account = 5391 0375 9387 5309
Balance = 436
Limit = 2500
New balance = 236
New balance = 36

*/
