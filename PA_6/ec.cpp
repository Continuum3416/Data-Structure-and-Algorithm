#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "heap_priority_queue.h"

#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;


int main(){
    std::ifstream infile_max("small1k.txt");
    HeapPriorityQueue<string, std::greater<string>> max_queue;
    std::string line;


    ofstream file("data.txt");

    cout << "1000 values: \n";
    int count = 0;
    while (infile_max >> line) {
        max_queue.insert(line);
        count++;
    }
    infile_max.close();
    vector<string> max_queue_vec; max_queue_vec.reserve(1000);

    int five_per_line = 0;
    for(int i = 0; i < count; i++){
        cout << max_queue.min() << " ";
        file << max_queue.min() << " ";
        max_queue.remove_min();

        five_per_line++;
        if(five_per_line == 5){
            cout << '\n';
            file << '\n';
            five_per_line = 0;
        }
        
    }
 

    // g++ ec.cpp -o ec.exe; ./ec.exe
    return 0;
}