#pragma once

#include <vector>

namespace dsac::analysis {

/// Returns the first index j such that data[j] == val, or -1 if no such element
/// @param data   a vector of integers
/// @param val    the target value
/// @return       first index j such that data[j] == val, or -1 if no such element
int find_first(const std::vector<int>& data, int val) {
    int n(data.size());
    int j{0};
    while (j < n) {
        if (data[j] == val)
            return j;                     // a match was found at index j
        j++;                              // otherwise continue to next index
        // val is not equal to any of the first j elements of data
    }
    return -1;                            // if we reach this, no match was found
}

}  // namespace dsac::analysis
