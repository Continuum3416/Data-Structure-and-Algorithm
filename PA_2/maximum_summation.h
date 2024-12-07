#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

//using namespace std;

typedef int (*Function_Vector) (const std::vector<int>& A);


// output the largest sum found in a sub-array
// there should be sum_{i = 0}^{size} binom(size, i) = 2^n sub-arrays
// and there should be 1 + 2 + ... + n = n(n + 1)/2 consecutive sub-arrays
int maximumSummation1(const std::vector<int>& A) {
    if (A.size() == 0) return 0;

    int maxSoFar = A[0];
    int maxEndingHere = A[0];

    for (int i = 1; i < A.size(); i++) {
        maxEndingHere = std::max(A[i], maxEndingHere + A[i]);   // O(1)
        maxSoFar = std::max(maxSoFar, maxEndingHere);           // O(1)
    }

    return maxSoFar;
}

int maximumSummation2(const std::vector<int>& A){
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

int maximumSummation3(const std::vector<int>& A){
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