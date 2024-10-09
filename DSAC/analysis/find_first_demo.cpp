#include <cstdlib>    // provides EXIT_SUCCESS
#include <vector>
#include <iostream>

#include "analysis/find_first.h"

using namespace std;
using namespace dsac::analysis;

int main() {
    vector<int> A = {14, 11, 23, 12, 14, 11, 18};

    int tests[][2] = { {14, 0},
                       {11, 1},
                       {23, 2},
                       {12, 3},
                       {18, 6},
    };
                          

    for (int t=0; t < 5; t++) {
        int result = find_first(A, tests[t][0]);
        if (result != tests[t][1])
            cout << "Error: find_first(A," << tests[t][0] << ") returned " << result << " not " << tests[t][1] << endl;
    }

    return EXIT_SUCCESS;
}
