#include <cstdlib>
#include <iostream>

#include "sample_functions.h"

using namespace std;
using namespace dsac::primer;

int main() {

    string state{"Mississippi"};
    cout << state << " has " << count(state, 'i') << " i's" << endl;
    remove_all(state, 'i');
    cout << "After they are removed, what remains is " << state << endl;

    return EXIT_SUCCESS;
}
