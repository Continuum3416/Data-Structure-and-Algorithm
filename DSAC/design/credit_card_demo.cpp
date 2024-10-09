#include <cstdlib>            // provides EXIT_SUCCESS
#include <iostream>           // provides std::ostream
#include "credit_card.h"

using dsac::design::CreditCard;
using namespace std;

int main() {

    CreditCard wallet[] = {
        CreditCard("John Bowman", "California Savings", "5391 0375 9387 5309", 5000),
        CreditCard("John Bowman", "California Federal", "3485 0399 3395 1954", 3500),
        CreditCard("John Bowman", "California Finance", "5391 0375 9387 5309", 2500, 300)
    };

    for (int val = 1; val <= 16; val++) {
        wallet[0].charge(3 * val);
        wallet[1].charge(2 * val);
        wallet[2].charge(val);
    }

    for (CreditCard card : wallet) {
        cout << card;
        while (card.get_balance() > 200.0) {
            card.make_payment(200);
            cout << "New balance = " << card.get_balance() << endl;
        }
        cout << endl;
    }
        
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
