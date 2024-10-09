#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream> 

using namespace std;
using namespace std::chrono;

// Computes prefix averages such that result a[j] equals the average of x[0], ..., x[j].
vector<double> prefix_averages1(const vector<double>& x) {
    int n(x.size());
    vector<double> a(n);              // filled with n zeros by default                                                                                        
    for (int j = 0; j < n; j++) {
        double total{0.0};            // begin computing x[0] + ... + x[j]                                                                                     
        for (int i = 0; i <= j; i++)
            total += x[i];
        a[j] = total / (j + 1);       // record the average                                                                                                    
    }
    return a;
}

// Computes prefix averages such that result a[j] equals the average of x[0], ..., x[j].
vector<double> prefix_averages2(const vector<double>& x) {
    int n(x.size());
    vector<double> a(n);              // filled with n zeros by default                                                                                        
    double total{0};                  // compute prefix sum as x[0] + x[1] + ...                                                                               
    for (int j = 0; j < n; j++) {
        total += x[j];                // update prefix sum to include x[j]                                                                                     
        a[j] = total / (j + 1);       // computer average based on current sum                                                                                 
    }
    return a;
}

template <typename S>
ostream& operator << (ostream& os, const vector<S>& vector){
    for(auto element: vector){
        os << element << " ";
    }
    return os;
}

int main(){
    srand(time(0));

    vector<double> vec;
    
    // vec = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
    // vector<double> output = prefix_averages1(vec);

    // cout << "prefix_average1: " << output << endl;
    // output = prefix_averages2(vec);
    // cout << "prefix_average2: " <<output << endl;

    ofstream file("timing_data.txt");

    cout << left << setw(10) << "n" << setw(15) << "time (milliseconds)" << endl;
    cout << string(25, '-') << endl;

    file << "n,time_ms" << endl;
    for(int n = 10; n <= 100000; n *= 10) {
        vec.reserve(n); // Reserve space to avoid multiple allocations

        for (int i = 0; i < n; ++i) {
            //double r = (rand() / (double)RAND_MAX) * (upper - lower) + lower;
            double random_double = static_cast<double>(rand()) / RAND_MAX * 20000.0 - 10000.0;
            vec.push_back(random_double);
        }

        auto start = high_resolution_clock::now();
        prefix_averages1(vec);
        auto end = high_resolution_clock::now();

        auto duration_ms = duration_cast<duration<double, milli>>(end - start);
        //auto duration_us = duration_cast<microseconds>(end - start);

        cout << left << setw(10) << n << setw(20) << fixed << setprecision(6) << duration_ms.count() << endl;
        file << n << "," << fixed << setprecision(3) << duration_ms.count() << endl;

        vec.clear();
    }

    // Run: g++ p1.cpp -o p1.exe; ./p1.exe
    return 0;
}
