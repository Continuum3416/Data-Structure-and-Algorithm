/*  Program:    
    Author:     
    Class:      
    Date:       
    Description: 
    I certify that the code below is my own work.
    Exception(s): N/A
*/
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>

using namespace std;
using namespace std::chrono;
int comparisons = 0;
int dataMoves = 0;

void insertionSort(int array[], int size) {
    int scan, unsortedValue;
    for (int index = 1; index < size; index++) {
        unsortedValue = array[index];
        scan = index;
        dataMoves++; // For assigning unsortedValue

        // Loop for finding the position to insert
        while (scan > 0) {
            comparisons++; // Every comparison in the loop
            if (array[scan - 1] <= unsortedValue)
                break;
            
            array[scan] = array[scan - 1]; // Move element to the right
            dataMoves++;
            scan--;
        }
        
        array[scan] = unsortedValue; // Insert the unsorted value in its place
        dataMoves++;
    }
}


int countInversions(int array[], int size) {
    int numInversions = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] > array[j]) {
                numInversions++;
            }
        }
    }
    return numInversions;
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

void testInsertionSort(int array[], int size) {
    comparisons = 0;
    dataMoves = 0;

    int numInversions = countInversions(array, size);
    cout << "Original list: ";
    printArray(array, size);
    
    insertionSort(array, size);
    cout << "Sorted list: ";
    printArray(array, size);
    
    cout << "Number of inversions: " << numInversions << endl;
    cout << "Number of comparisons: " << comparisons << endl;
    cout << "Number of data moves: " << dataMoves << endl;
}

void measureSortingPerformance(const string& filename, int array[], int size) {
    comparisons = 0;
    dataMoves = 0;

    auto start = high_resolution_clock::now();
    insertionSort(array, size);
    auto end = high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::duration<double, milli>>(end - start).count(); 

    int numInversions = countInversions(array, size);

    cout << "First 5 values: ";
    for (int i = 0; i < 5; i++) {
        cout << array[i] << " ";
    }
    cout << "\nLast 5 values: ";
    for (int i = size - 5; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << "\nNumber of inversions: " << numInversions << endl;
    cout << "Number of comparisons: " << comparisons << endl;
    cout << "Number of data moves: " << dataMoves << endl;
    cout << std::setprecision(5) << fixed << "Running time (ms): " << duration << endl; // Use .count() here
}


int main() {
    int smallArray[] = {4, 3, 1, 0, 9, 8, 6, 7, 5, 2};
    int size = 10;

    cout << "Testing on small array:\n";
    testInsertionSort(smallArray, size);

    cout << "\nSorting already sorted small array:\n";
    testInsertionSort(smallArray, size);

    cout << "\nReversing and sorting descending small array:\n";
    reverse(smallArray, smallArray + size);
    testInsertionSort(smallArray, size);

    // Load 1,000 values from "small1k.txt"
    ifstream file("small1k.txt");
    if (!file) {
        cerr << "Error opening file.\n";
        return 1;
    }
    vector<int> bigArray;
    int value;
    while (file >> value) {
        bigArray.push_back(value);
    }
    file.close();

    cout << "\nTesting on 1,000 values in random order:\n";
    measureSortingPerformance("small1k.txt", bigArray.data(), bigArray.size());

    cout << "\nSorting already sorted 1,000 values:\n";
    measureSortingPerformance("small1k.txt", bigArray.data(), bigArray.size());


    // g++ p1.cpp -o p1.exe; ./p1.exe

    return 0;
}
