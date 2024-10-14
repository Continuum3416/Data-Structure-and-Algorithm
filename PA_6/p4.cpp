#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "heap_priority_queue.h"

#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace std::chrono;



int main(){
    std::ifstream infile_max("small1k.txt");
    HeapPriorityQueue<int, std::greater<int>> max_queue;
    std::string line;

    cout << "1000 values: \n";
    auto start = high_resolution_clock::now();
    int count = 0;
    while (infile_max >> line) {
        max_queue.insert(stoi(line));
        count++;
    }
    infile_max.close();
    vector<int> max_queue_vec; max_queue_vec.reserve(1000);
    for(int i = 0; i < count; i++){
        max_queue_vec[i] = max_queue.min();
        max_queue.remove_min();
    }
    cout << "First five: ";
    for(int i = 0; i < 5; i++)
        cout << max_queue_vec[i] << " ";

    cout << "\nLast five: ";
    for(int i = count - 5; i < count; i++)
        cout << max_queue_vec[i] << " ";
    count = 0;
    auto end = high_resolution_clock::now();
    auto duration_ms = duration_cast<duration<double, milli>>(end - start);

    cout << "\nRuntime: " << setprecision(6) << duration_ms.count() << " ms" << endl;



    start = high_resolution_clock::now();
    cout << "\n100,000 values: \n";
    std::ifstream infile_min("large100k.txt");
    HeapPriorityQueue<int> min_queue;


    while (infile_min >> line) {
        min_queue.insert(stoi(line));
        count++;
    }
    infile_min.close();
    vector<int> min_queue_vec; min_queue_vec.reserve(100000);
    for(int i = 0; i < count; i++){
        min_queue_vec[i] = min_queue.min();
        min_queue.remove_min();
    }
    cout << "First five: ";
    for(int i = 0; i < 5; i++)
        cout << min_queue_vec[i] << " ";

    cout << "\nLast five: ";
    for(int i = count - 5; i < count; i++)
        cout << min_queue_vec[i] << " ";
    end = high_resolution_clock::now();
    duration_ms = duration_cast<duration<double, milli>>(end - start);

    cout << "\nRuntime: " << setprecision(6) << duration_ms.count() << " ms"  << endl;
    
    // g++ p4.cpp -o p4.exe; ./p4.exe
    return 0;
}