#include<iostream>
#include<cmath>
#define EPSILON 1000
using namespace std;


int main() {
    for(long i = 1000; i < 63000; i++){
        if(abs(i * log(i)/log(2) - 1000000) < EPSILON);
            cout << i << endl;
    }
    cout << "end" << endl;
    // g++ newton-rapson.cpp -o newton-rapson.cpp.exe;
    return 0;
}
