#include <cstdlib>  // provides EXIT_SUCCESS
#include <iostream>

#include "analysis/disjoint_set.h"

using namespace std;
using namespace dsac::analysis;

int main() {
    // array of three function pointers.
    bool (*function[])(const vector<int>&, const vector<int>&, const vector<int>&) = {is_disjoint1,is_disjoint2};

    vector<int> A = {1, 3, 5};
    vector<int> B = {2, 4, 6, 8};
    vector<int> C = {1, 2, 3, 4, 5, 6, 7};
    vector<int> D = {1, 2, 3, 4};
    vector<int> E = {4, 5, 6, 7};
    vector<int> F = {9, 10};
    
    for (int f=0; f<2; f++) {
        cout << "Testing is_disjoint" << (f+1) << "..." << endl;

        if ((*function[f])(A,C,D))
            cout << "Test failed on A,B,D. 1 and 3 are common" << endl;

        if ((*function[f])(B,D,E))
            cout << "Test failed on B,D,E. 4 is common" << endl;

        if (!(*function[f])(A,B,C))
            cout << "Test failed on A,B,C. No common elements" << endl;

        if (!(*function[f])(A,C,B))
            cout << "Test failed on A,C,B. No common elements" << endl;

        if (!(*function[f])(A,B,F))
            cout << "Test failed on A,B,F. No common elements" << endl;

    }

    return EXIT_SUCCESS;
}
