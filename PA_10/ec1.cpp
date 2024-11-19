#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include "pattern_match.h"

using namespace std;
using namespace dsac::text;


string read_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        exit(1);
    }

    string text;
    string line;
    while (getline(file, line)) {
        text += line + '\n';
    }
    file.close();
    return text;
}

int main() {
    // Test case file names
    vector<pair<string, string>> test_cases = {
        {"USDeclIndFormatted.txt", "computer"},
        {"USDeclIndFormatted.txt", "therein"},
        {"humanDNA.txt", "CAAATGGCCTG"},
        {"humanDNA.txt", "CAAATGGGCCTG"}
    };

    int test_case_num = 1;
    int print_length = 30;
    for (const auto& [filename, pattern] : test_cases) {
        string T = read_file(filename);

        // string P;
        // cout << "Enter the pattern to search: ";
        // cin >> P;
        // pattern = P

        cout << "Test case " << test_case_num++ << ":\n";
        int comparisons = 0;
        
        // brute force algorithm
        int index = find_brute(T, pattern, comparisons);
        cout << "Brute Force: T=\"" << T.substr(0, print_length) << "...\", P=\"" << pattern << "\", Index=" << index << ", Comparisons=" << comparisons << "\n";

        comparisons = 0;
        // Boyer-Moore algorithm
        index = find_boyer_moore(T, pattern, comparisons);
        cout << "Boyer-Moore: T=\"" << T.substr(0, print_length) << "...\", P=\"" << pattern << "\", Index=" << index << ", Comparisons=" << comparisons << "\n";

        comparisons = 0;
        // KMP algorithm
        index = find_kmp(T, pattern, comparisons);
        cout << "KMP:         T=\"" << T.substr(0, print_length) << "...\", P=\"" << pattern << "\", Index=" << index << ", Comparisons=" << comparisons << "\n";
        
        cout << "-------------------------------------------\n\n";
    }

    // Run: g++ ec1.cpp -o ec1.exe; ./ec1.exe
    return 0;
}
