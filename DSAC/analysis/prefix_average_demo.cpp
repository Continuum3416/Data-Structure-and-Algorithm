#include <cstdlib>  // provides EXIT_SUCCESS
#include <iostream>
#include <vector>

#include "analysis/prefix_average.h"

using namespace std;
using namespace dsac::analysis;

int main() {
    // array of three function pointers.
    vector<double> (*function[])(const vector<double>&) = {prefix_averages1,prefix_averages2};

    vector<double> A = {1, 3, 5, 4, 6, 2};
    
    for (int f=0; f<2; f++) {
        cout << "Using prefix_averages" << (f+1) << "..." << endl;
        vector<double> result{(*function[f])(A)};
        for (auto v : result)
            cout << " " << v;
        cout << endl;
    }

    return EXIT_SUCCESS;
}
