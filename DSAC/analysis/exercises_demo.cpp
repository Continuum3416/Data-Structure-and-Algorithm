#include <cstdlib>    // provides EXIT_SUCCESS
#include <vector>

#include "analysis/exercises.h"

using namespace std;
using namespace dsac::analysis;

int main() {
    vector<int> A = {14, 11, 23, 12, 14, 11, 18};

    // just testing that things compile and run, but not testing results
    example1(A);
    example2(A);
    example3(A);
    example4(A);
    example5(A,A);

    return EXIT_SUCCESS;
}
