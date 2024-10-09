#pragma once

namespace dsac::recursion {

/// Returns true if there are no duplicate values from data[low] through data[high].
/// @param data   array of integers
/// @param low    lowest index of interest
/// @param high   highest index of interest    
bool is_unique3(int data[], int low, int high) {
    if (low >= high) return true;                              // at most one item
    else if (!is_unique3(data, low, high - 1)) return false;   // duplicate in first n-1
    else if (!is_unique3(data, low + 1, high)) return false;   // duplicate in last n-1
    else return (data[low] != data[high]);                     // do first and last differ?
}

}  // namespace dsac::recursion
