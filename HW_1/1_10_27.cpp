#include <iostream>
#include <cstdlib> 
#include <vector>
#include <algorithm>

using namespace std;

void shuffle(std::vector<int>& arr) {
    srand(time(0));
    for (int i = arr.size() - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        std::swap(arr[i], arr[j]);
    }
}

template <typename S>
ostream& operator << (ostream& os, const vector<S>& vector){
    for(auto element: vector){
        os << element << " ";
    }
    return os;
}

int main(){
    vector<int> A;
    for(int i = 1; i <= 52; i++){
        A.push_back(i);
    }
    cout <<  "Before shuffle: " <<A << endl;
    shuffle(A);
    cout <<  "\nAfter shuffle: " << A << endl;
    shuffle(A);
    cout <<  "\nShuffle again: " << A << endl;

    // Run: g++ 1_10_27.cpp -o 1_10_27.exe; ./1_10_27.exe   
    return 0;
}