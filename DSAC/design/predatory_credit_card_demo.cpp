#include <cstdlib>            // provides EXIT_SUCCESS
#include <iostream>           // provides std::ostream
#include "predatory_credit_card.h"

using dsac::design::PredatoryCreditCard;
using namespace std;

int main() {
    PredatoryCreditCard card("Michael", "Payday", "1111 1111 1111 1111", 2500, 0, 0.0825);
    card.charge(1000);
    cout << card;
    card.process_month();             // interest charged
    cout << card;
    card.charge(10000);               // should be rejected, with penalty
    cout << card;

    return EXIT_SUCCESS;
}
