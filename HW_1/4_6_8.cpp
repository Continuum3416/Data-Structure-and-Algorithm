#include <iostream>
#include <cstdlib> 
#include <vector>
#include <algorithm>

using namespace std;

string int_to_string_iterative(long long num){
    if(num == 0) return "0";
    char A[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    string output;
    bool isNegative = false;
    if(num < 0){
        num = -num;
        isNegative = true;
    }
    while(num != 0){
        int digit = num % 10;
        output = A[digit] + output;
        num /= 10;
    }
    if(isNegative)
        output = '-' + output;
    return output;
}

string int_to_string_recursion(long long num){
    string output;
    bool isNegative = false;
    if(num == 0) return "0";
    
    if(num < 0 && !isNegative){
        num = -num;
        isNegative = true;
    }

    if(num > 0){
        output = int_to_string_recursion(num / 10);
        output += ('0' + (num % 10));
        cout << num << " " << num%10 <<" " << output << endl;
    }

    if(isNegative)
        output[0] = '-';
    else
        output[0] ='\0';
    return output;

}

int main(){
    long long a = 12345;
    // cout << "Input: " << a << endl;
    // cout << "Output: " << int_to_string_iterative(a) << endl;

    cout << "Input: " << a << endl;
    cout << "Output: \n" << int_to_string_recursion(a) << endl;

    // Run: g++ 4_6_8.cpp -o 4_6_8.exe; ./4_6_8.exe   
    return 0;
}