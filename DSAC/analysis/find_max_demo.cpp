#include <cstdlib>  // provides EXIT_SUCCESS
#include <vector>
#include <iostream>

#include "analysis/find_max.h"

using namespace std;
using namespace dsac::analysis;

int main() {
    vector<int> A = {14, 11, 23, 12, 15, 18};
    cout << find_max(A) << endl;

    vector<int> B = {7, 0, -9};
    cout << find_max(B) << endl;

    vector<int> C = {12};
    cout << find_max(C) << endl;

    vector<int> D = {1, 2, 3, 4};
    cout << find_max(D) << endl;

    return EXIT_SUCCESS;
}
