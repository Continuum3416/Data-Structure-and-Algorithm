#pragma once

namespace dsac::recursion {

/// Returns the sum of the first n integers of the given array.
/// @param data  array of integers
/// @param n     how many integers from the beginning of the array to sum
/// @return the sum of the first n integers of data
int linear_sum(int data[], int n) {
    if (n == 0)
        return 0;
    else
        return linear_sum(data, n - 1) + data[n - 1];
}

/// Returns the sum of subarray data[low] through data[high] inclusive.
/// @param data  array of integers
/// @param low   the index of the first integer in the range
/// @param high   the index of the second integer in the range
/// @return the sum of the integers from data[low] through data[high] inclusive
int binary_sum(int data[], int low, int high) {
    if (low > high)                               // zero elements in subarray
        return 0;
    else if (low == high)                         // one element in subarray
        return data[low];
    else {
        int mid = (low + high) / 2;
        return binary_sum(data, low, mid) + binary_sum(data, mid + 1, high);
    }
}

}  // namespace dsac::recursion
