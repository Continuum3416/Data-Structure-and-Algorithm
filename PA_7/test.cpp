#include <iostream>

using namespace std;

bool isEven(int);
bool isOdd(int);

int main()
{   
    // stack overflow
    if(isEven(4))
        cout << "even" << endl;
    else
        cout << "odd" << endl;

    return 0;
}


bool isEven(int n){
    return !isOdd(n);
}

bool isOdd(int n){
    return !isEven(n);
}

// g++ test.cpp -o test.exe; ./test.exe