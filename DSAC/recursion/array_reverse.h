#pragma once

#include <utility>     //  std::swap

namespace dsac::recursion {

/// Reverses the contents of subarray data[low] through data[high] inclusive.
/// @param data  an array of integers
/// @param low   the index of the first element in the range to be reversed
/// @param high  the index of the last element in the range to be reversed
void reverse_array(int data[], int low, int high) {
    if (low < high) {                                // if at least two elements in subarray
        std::swap(data[low], data[high]);
        reverse_array(data, low + 1, high - 1);      // recur on the rest
    }
}

/// Reverses the contents of the given array.
/// @param data  an array of integers
/// @param n     length of the array
void reverse_iterative(int data[], int n) {
    int low{0};
    int high{n - 1};
    while (low < high) {
        std::swap(data[low], data[high]);
        low++;
        high--;
    }
}

}  // namespace dsac::recursion
