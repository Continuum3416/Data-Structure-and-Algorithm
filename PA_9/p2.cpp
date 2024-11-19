/*  Program:    
    Author:     
    Class:      
    Date:       
    Description: 
    I certify that the code below is my own work.
    Exception(s): N/A
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "mergesort.h"  

using namespace std;
using namespace std::chrono;
using namespace dsac::sorting;

// Global counters for key comparisons and data moves
size_t keyComparisons = 0;
size_t dataMoves = 0;

template <typename T, typename Compare>
void merge_with_count(const std::vector<T>& S1, const std::vector<T>& S2, std::vector<T>& S, Compare comp) {
    S.resize(S1.size() + S2.size());
    int i{0}, j{0}, k{0};
    while (k < S.size()) {
        keyComparisons++;  // Count comparisons
        if (j == S2.size() || (i < S1.size() && comp(S1[i], S2[j]))) {
            S[k++] = S1[i++];  // Count data move
            dataMoves++;
        } else {
            S[k++] = S2[j++];
            dataMoves++;
        }
    }
}

// Wraps merge_sort with counting
template <typename T, typename Compare>
void merge_sort_with_count(std::vector<T>& S, Compare comp) {
    int n(S.size());
    if (n < 2) return;
    int mid = n / 2;
    std::vector<T> S1(S.begin(), S.begin() + mid);
    std::vector<T> S2(S.begin() + mid, S.end());
    merge_sort_with_count(S1, comp);
    merge_sort_with_count(S2, comp);
    merge_with_count(S1, S2, S, comp);
}

// Measure and print test results
template <typename T>
void test_merge_sort(std::vector<T>& data, bool bottomUp) {
    keyComparisons = 0;
    dataMoves = 0;
    
    auto start = std::chrono::steady_clock::now();
    if (bottomUp) {
        merge_sort_bottom_up(data, std::less<T>());
    } else {
        merge_sort_with_count(data, std::less<T>());
    }
    auto end = std::chrono::steady_clock::now();
    
    auto duration = chrono::duration_cast<std::chrono::duration<std::double, std::milli>>(end - start).count(); 
    std::cout << "Sorted Data (first 5 values): ";
    for (size_t i = 0; i < 5 && i < data.size(); ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "\nSorted Data (last 5 values): ";
    for (size_t i = data.size() - 5; i < data.size(); ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "\nComparisons: " << keyComparisons;
    std::cout << "\nData moves: " << dataMoves;
    std::cout << std::setprecision(5) << std::fixed << "\nRunning time: " << duration << " ms\n";
}

// Function to read file data
std::vector<int> read_file(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<int> data;
    int value;
    while (file >> value) {
        data.push_back(value);
    }
    return data;
}

int main() {
    // Small list test
    std::vector<int> smallList = {4, 3, 1, 0, 9, 8, 6, 7, 5, 2};
    std::cout << "Original list: ";
    for (int val : smallList) std::cout << val << " ";
    std::cout << "\n";

    test_merge_sort(smallList, false);  // Test with top-down merge sort

    // Test with small1k.txt and large100k.txt
    std::vector<int> small1k = read_file("small1k.txt");
    std::cout << "\nTesting small1k.txt:\n";
    test_merge_sort(small1k, false);

    std::vector<int> large100k = read_file("large100k.txt");
    std::cout << "\nTesting large100k.txt:\n";
    test_merge_sort(large100k, false);


    // g++ p2.cpp -o p2.exe; ./p2.exe

    return 0;
}
