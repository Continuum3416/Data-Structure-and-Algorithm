#include <cstdlib>    // provides EXIT_SUCCESS
#include <iostream>

#include "recursion/ruler.h"

using namespace std;
using namespace dsac::recursion;

int main() {
    cout << endl << endl << "Ruler of length 2 with major tick length 4" << endl << endl;
    draw_ruler(2, 4);
    cout << endl << endl << "Ruler of length 1 with major tick length 5" << endl << endl;
    draw_ruler(1, 5);
    cout << endl << endl << "Ruler of length 3 with major tick length 3" << endl << endl;
    draw_ruler(3, 3);

    return EXIT_SUCCESS;
}
