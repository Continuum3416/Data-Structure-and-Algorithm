#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "quicksort.h"

using namespace std;
using namespace dsac::sorting;

void run_sort_and_print(vector<int>& data, const string& label) {
    SortStats stats;
    auto start = chrono::high_resolution_clock::now();
    quick_sort_in_place(data, less<int>(), stats);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << label << ":\n";
    cout << "Comparisons: " << stats.comparisons << "\n";
    cout << "Data Moves: " << stats.dataMoves << "\n";
    cout << "Running Time: " << duration.count() << " ms\n";

    if (data.size() <= 10) {
        cout << "Original List (10 values): ";
        for (int val : data) cout << val << " ";
        cout << "\n";
    } else {
        cout << "First 5 values: ";
        for (int i = 0; i < 5; ++i) cout << data[i] << " ";
        cout << "\nLast 5 values: ";
        for (int i = data.size() - 5; i < data.size(); ++i) cout << data[i] << " ";
        cout << "\n";
    }
}

void load_file_data(const string& filename, vector<int>& data) {
    ifstream file(filename);
    int value;
    while (file >> value) {
        data.push_back(value);
    }
    file.close();
}

int main() {
    // Small list of 10 integers
    vector<int> small_list = {4, 3, 1, 0, 9, 8, 6, 7, 5, 2};
    cout << "Sorting Small List (10 elements)\n";
    run_sort_and_print(small_list, "Small List");

    // Load and sort small1k.txt
    vector<int> small1k;
    load_file_data("small1k.txt", small1k);
    cout << "\nSorting small1k.txt (1,000 elements)\n";
    run_sort_and_print(small1k, "small1k.txt");

    // Load and sort large100k.txt
    vector<int> large100k;
    load_file_data("large100k.txt", large100k);
    cout << "\nSorting large100k.txt (100,000 elements)\n";
    run_sort_and_print(large100k, "large100k.txt");

    // g++ p3.cpp -o p3.exe; ./p3.exe

    return 0;
}
