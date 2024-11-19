#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "matrix_chain.h"

using namespace std;
using namespace dsac::text;


int main() {
    // Test case 1: Matrices with dimensions 2x10, 10x50, and 50x20
    vector<int> d1 = {2, 10, 50, 20};
    auto result1 = matrix_chain(d1);
    cout << "Minimum number of operations for the first test case: " << result1[0][result1.size() - 1] << std::endl;
    
    // Test case 2: Matrices with dimensions 10x5, 5x2, 2x20, 20x12, 12x4, 4x60
    vector<int> d2 = {10, 5, 2, 20, 12, 4, 60};
    auto result2 = matrix_chain(d2);
    cout << "Minimum number of operations for the second test case: " << result2[0][result2.size() - 1] << std::endl;

    // Run: g++ p4.cpp -o p4.exe; ./p4.exe
    return 0;
}
