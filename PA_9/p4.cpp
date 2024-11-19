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
void merge_with_count(const vector<T>& S1, const vector<T>& S2, vector<T>& S, Compare comp) {
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
void merge_sort_with_count(vector<T>& S, Compare comp) {
    int n(S.size());
    if (n < 2) return;
    int mid = n / 2;
    vector<T> S1(S.begin(), S.begin() + mid);
    vector<T> S2(S.begin() + mid, S.end());
    merge_sort_with_count(S1, comp);
    merge_sort_with_count(S2, comp);
    merge_with_count(S1, S2, S, comp);
}

// Measure and print test results
template <typename T>
void test_merge_sort(vector<T>& data, bool bottomUp) {
    keyComparisons = 0;
    dataMoves = 0;
    
    auto start = chrono::steady_clock::now();
    if (bottomUp) {
        merge_sort_bottom_up(data, less<T>());
    } else {
        merge_sort_with_count(data, less<T>());
    }
    auto end = chrono::steady_clock::now();
    
    auto duration = chrono::duration_cast<chrono::duration<double, milli>>(end - start).count(); 
    cout << "Sorted Data (first 5 values): ";
    for (size_t i = 0; i < 5 && i < data.size(); ++i) {
        cout << data[i] << " ";
    }
    cout << "\nSorted Data (last 5 values): ";
    for (size_t i = data.size() - 5; i < data.size(); ++i) {
        cout << data[i] << " ";
    }
    cout << "\nComparisons: " << keyComparisons;
    cout << "\nData moves: " << dataMoves;
    cout << std::setprecision(5) << fixed << "\nRunning time: " << duration << " ms\n";
}

// Function to read file data
vector<int> read_file(const string& filename) {
    ifstream file(filename);
    vector<int> data;
    int value;
    while (file >> value) {
        data.push_back(value);
    }
    return data;
}

int main() {
    // Small list test
    vector<int> smallList = {4, 3, 1, 0, 9, 8, 6, 7, 5, 2};
    cout << "Original list: ";
    for (int val : smallList) cout << val << " ";
    cout << "\n";

    test_merge_sort(smallList, false);  // Test with top-down merge sort

    // Test with small1k.txt and large100k.txt
    vector<int> small1k = read_file("small1k.txt");
    cout << "\nTesting small1k.txt:\n";
    test_merge_sort(small1k, false);

    vector<int> large100k = read_file("large100k.txt");
    cout << "\nTesting large100k.txt:\n";
    test_merge_sort(large100k, false);

    // g++ p4.cpp -o p4.exe; ./p4.exe

    return 0;
}
