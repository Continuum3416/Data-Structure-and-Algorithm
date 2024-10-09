#include <cstdlib>                          // provides EXIT_SUCCESS
#include <iostream>
#include <string>

#include "array/caesar_cipher.h"

using namespace dsac::array;
using namespace std;

int main() {
    CaesarCipher cipher{3};
    string message{"THE EAGLE IS IN PLAY; MEET AT JOE'S."};
    string coded{cipher.encrypt(message)};
    cout << "Secret:  " << coded << endl;
    string answer{cipher.decrypt(coded)};
    cout << "Message: " << answer << endl;  // should be plaintext again

    return EXIT_SUCCESS;
}
