#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "pattern_match.h"

using namespace std;
using namespace dsac::text;


int main() {
    vector<pair<string, string>> test_cases = {
        {"aaaaaaaaaaaaaaaaabbbbbbbbbbbbbb", "aaaab"},
        {"aaaaaaaaaaaaaaaaabbbbbbbbbbbbbb", "aabaa"},
        {"a pattern matching algorithm", "rithm"},
        {"a pattern matching algorithm", "rithn"},
        {"GTTTATGTAGCTTACCTCCTCAAAGCAATACACTGAAAA", "CTGA"},
        {"GTTTATGTAGCTTACCTCCTCAAAGCAATACACTGAAAA", "CTGG"}
    };


    int test_case_num = 1;
    for (const auto& [T, P] : test_cases) {
        cout << "Test case " << test_case_num++ << ":\n";
        int comparisons = 0;
        int index = find_brute(T, P, comparisons);
        cout << "Brute Force: T=\"" << T << "\", P=\"" << P << "\", Index=" << index << ", Comparisons=" << comparisons << "\n";

        comparisons = 0;
        index = find_boyer_moore(T, P, comparisons);
        cout << "Boyer-Moore: T=\"" << T << "\", P=\"" << P << "\", Index=" << index << ", Comparisons=" << comparisons << "\n";

        comparisons = 0;
        index = find_kmp(T, P, comparisons);
        cout << "KMP:         T=\"" << T << "\", P=\"" << P << "\", Index=" << index << ", Comparisons=" << comparisons << "\n";
        cout << "-------------------------------------------\n\n";
       
    }

    // Run: g++ p2.cpp -o p2.exe; ./p2.exe
    return 0;
}
