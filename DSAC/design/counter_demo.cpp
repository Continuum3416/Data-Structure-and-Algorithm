#include <cstdlib>
#include <iostream>
#include "counter.h"
using namespace std;
using dsac::design::Counter;

int main() {
    Counter c;                  // declares a Counter instance with default value 0
    c.increment();              // increases value to 1
    c.increment(3);             // increases value from 1 to 4
    int temp{c.get_value()};    // will be 4
    c.reset();                  // value becomes 0
    cout << temp << endl;       // temp is still 4
    Counter d{5};               // declares and constructs a Counter with initial value 5
    d.increment();              // d's value becomes 6
    Counter e{d};               // New counter e is independent copy of d
    temp = e.get_value();       // will be 6
    e.increment(2);             // e increases to 8; d remains at 6

    cout << "d=" << d.get_value() << ", e=" << e.get_value() << endl;

    return EXIT_SUCCESS;
}
