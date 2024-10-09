#include <iostream>
#include <vector>

using namespace std;

vector<int> twoSumIterationFast(vector<int> A, int target){
    int left = 0;
    int right = A.size() - 1;

    while(left < right){
        if(A[left] + A[right] == target)
            return {A[left], A[right]};
        else if (A[left] + A[right] < target)
            left++;
        else    
            right--;
    }
    return {};
}

vector<int> twoSumRecursionFast(vector<int> A, int target, int left, int right){
    // base case
    if(left > right)
        return {};
    else if(A[left] + A[right] == target)
        return {A[left], A[right]};
    else if(A[left] + A[right] < target)
        return twoSumRecursionFast(A, target, left + 1, right); // or ++left
    else
        return twoSumRecursionFast(A, target, left, right - 1); // or --right
}

template <typename S>
ostream& operator << (ostream& os, const vector<S>& vector){
    if(vector.empty())
        os << "No element found";
    else{
        for(auto element: vector){
            os << element << " ";
        }
    }
    return os;
}

int main(){
    // assuming arr is sorted
    vector<int> arr = {3, 9, 12, 15, 16, 23};
    int target = 16;
    vector<int> output_1 = twoSumIterationFast(arr, target);
    cout << "Iterative: " << output_1 << endl;

    vector<int> output_2 = twoSumRecursionFast(arr, target, 0, arr.size()-1);
    cout << "Recursion: " << output_2 << endl;

    // Run: g++ p2.cpp -o p2.exe; ./p2.exe
    return 0;
}