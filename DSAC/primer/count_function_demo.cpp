#include <cstdlib>       // provides EXIT_SUCCESS
#include <iostream>      // provides input/output streams

#include "sample_functions.h"

using namespace std;
using namespace dsac::primer;

int main() {
    string s;
    char target;
    cout << "Enter a string: ";
    getline(cin, s);
    cout << "Enter target character: ";
    cin >> target;

    cout << "The target appears " << count(s,target) << " times" << endl;

    cout << "The target appears " << count(s.c_str(), s.size(),target) << " times" << endl;

    
    return EXIT_SUCCESS;
}
