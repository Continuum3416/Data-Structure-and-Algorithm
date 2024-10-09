#include <cstdlib>       // provides EXIT_SUCCESS
#include <iostream>      // provides input/output streams

using namespace std;

/* This program inputs two integers and outputs their sum */
int main() {
    int x, y;
    cout << "Please enter two numbers: ";
    cin >> x >> y;                                   // input x and y
    int sum{x + y};                                  // compute and store their sum
    cout << "Their sum is " << sum << "." << endl;
    return EXIT_SUCCESS;                             // program terminates successfully
}
