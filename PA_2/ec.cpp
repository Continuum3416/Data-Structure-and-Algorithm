#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream> 
#include <string> 

using namespace std;
using namespace std::chrono;

typedef int (*Function_Vector) (const vector<int> A);

// output the largest sum found in a sub-array
// there should be sum_{i = 0}^{size} binom(size, i) = 2^n sub-arrays
// and there should be 1 + 2 + ... + n = n(n + 1)/2 consecutive sub-arrays
int maximumSummation1(const vector<int> A) {
    if (A.size() == 0) return 0;

    int maxSoFar = A[0];
    int maxEndingHere = A[0];

    for (int i = 1; i < A.size(); i++) {
        maxEndingHere = std::max(A[i], maxEndingHere + A[i]);   // O(1)
        maxSoFar = std::max(maxSoFar, maxEndingHere);           // O(1)
    }

    return maxSoFar;
}

int maximumSummation2(const vector<int> A){
    if (A.size() == 0) return 0;

    int max = A[0];
    for(int i = 0; i < A.size(); i++){
        int sum = 0;
        for(int j = i; j < A.size(); j++){
            sum += A[j];
            if(sum > max)
                max = sum;
        }
    }
    return max;
}   

int maximumSummation3(const vector<int> A){
    if (A.size() == 0) return 0;

    int max = A[0];
    for(int i = 0; i < A.size(); i++){
        for(int j = i; j < A.size(); j++){
            int sum = 0;
            for(int k = i; k <= j; k++){
                sum += A[k];
            }
            if(sum > max)
                max = sum;
        }
    }
    return max;
}

Function_Vector f[] = {maximumSummation1, maximumSummation2, maximumSummation3};


int main(){
    vector <int> A;
    A = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84}; // 187
    // A = {31, 41, 59, 26, 53, 58, 97, 93, 23, 84}; // 565

    // cout << "maximumSummation1: " << maximumSummation1(A) << endl;
    // cout << "maximumSummation2: " << maximumSummation2(A) << endl;
    // cout << "maximumSummation3: " << maximumSummation3(A) << endl;

    int upper_bound = 10000;
    int lower_bound = -10000;

    
    for(int j = 0; j < 3; j++){
        string fileName = "python/timing_data" + to_string(j + 1)+".txt";
        ofstream file(fileName);

        cout << left << setw(10) << "n" << setw(15) << "time (milliseconds)" << endl;
        cout << string(25, '-') << endl;

        file << "n,time_ms" << endl;
        for(int n = 1; n <= 500; n += 1) {
            srand(time(0) + n);
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