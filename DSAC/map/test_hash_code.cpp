#include "hash_code.h"

#include <iostream>
using namespace std;
using namespace dsac::map;

int main() {
    string token;
    while (cin >> token) {
        cout << "hash_code(\"" << token << "\") is " << hash_code(token) << endl;
    }

}
