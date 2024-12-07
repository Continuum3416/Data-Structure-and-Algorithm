#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream> 
#include <string> 
#include "maximum_summation.h"

using namespace std;
using namespace std::chrono;




int main(){
    vector <int> A;
    A = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84}; // 187
    // A = {31, 41, 59, 26, 53, 58, 97, 93, 23, 84}; // 565

    // cout << "maximumSummation1: " << maximumSummation1(A) << endl;
    // cout << "maximumSummation2: " << maximumSummation2(A) << endl;
    // cout << "maximumSummation3: " << maximumSummation3(A) << endl;

    int lower_bound = -10000;
    int upper_bound = 10000;
    

    
    for(int j = 0; j < 3; j++){
        string fileName = "python/timing_data" + to_string(j + 1)+".txt";
        ofstream file(fileName);

        cout << left << setw(10) << "n" << setw(15) << "time (milliseconds)" << endl;
        cout << string(25, '-') << endl;
        srand(time(0));

        file << "n,time_ms" << endl;
        for(int n = 1; n <= 500; n += 1) {
            A.reserve(n); 

            for (int i = 0; i < n; ++i) {
                int random_int = (rand()%(upper_bound - lower_bound)) + lower_bound;
                A.push_back(random_int);
            }

            auto start = high_resolution_clock::now();
            f[j](A);
            auto end = high_resolution_clock::now();

            auto duration_ms = duration_cast<duration<double, milli>>(end - start);

            cout << left << setw(10) << n << setw(20) << fixed << setprecision(6) << duration_ms.count() << endl;
            file << n << "," << fixed << setprecision(3) << duration_ms.count() << endl;

            A.clear();
            
        }
    }

    // Run: g++ ec.cpp -o ec.exe; ./ec.exe
    return 0;
}