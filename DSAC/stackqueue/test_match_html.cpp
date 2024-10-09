#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "stackqueue/match_html.h"
using namespace std;
using namespace dsac::stackqueue;

int main() {
    ostringstream sstream;
    sstream << cin.rdbuf();

    if (is_html_matched(sstream.str()))
        cout << "The input was matched" << endl;
    else
        cout << "The input was not matched" << endl;
    
    return EXIT_SUCCESS;
}
