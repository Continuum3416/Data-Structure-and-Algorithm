#include <iostream>

using namespace std;

int sum_odd_to_n(int n){
    int sum = 0;
    for(int i = 1; i <= n; i += 2){
        sum += i;
    }
    return sum;
}

int sum_odd_to_n_fast(int n){
    if(n % 2 == 0) n--;
    return (n + 1) * (n + 1)/4;
}

int main()
{
    int num = 8;
    cout << sum_odd_to_n(num) << endl;
    cout << sum_odd_to_n_fast(num) << endl;

    // Run: g++ 1_10_15.cpp -o 1_10_15.exe; ./1_10_15.exe
    return 0;
}