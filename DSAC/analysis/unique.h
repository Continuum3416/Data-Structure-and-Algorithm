#pragma once

#include <algorithm>       // std::sort
#include <vector>          // std::vector

namespace dsac::analysis {

/// Returns true if there are no duplicate elements in the vector
/// @param data     a vector of integers
/// @return true if all values are unique
bool is_unique1(const std::vector<int>& data) {
    int n(data.size());
    for (int j = 0; j < n - 1; j++)
        for (int k = j + 1; k < n; k++)
            if (data[j] == data[k]) return false;   // found duplicate pair
    return true;                                    // if we reach this, elements are unique
}

/// Returns true if there are no duplicate elements in the vector
/// @param data     a vector of integers
/// @return true if all values are unique
bool is_unique2(const std::vector<int>& data) {
    int n(data.size());
    std::vector<int> temp{data};
    std::sort(temp.begin(), temp.end());            // std::sort from <algorithm>
    for (int j = 0; j < n - 1; j++)
        if (temp[j] == temp[j + 1])                 // check neighboring entries
            return false;                           // found duplicate pair
    return true;                                    // if we reach this, sets are disjoint
}

}  // namespace dsac::analysis
