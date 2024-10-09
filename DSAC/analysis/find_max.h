#pragma once

#include <vector>

namespace dsac::analysis {

/// Returns the maximum value of a nonempty vector of integers
/// @param data   a nonempty vector of integers
/// @return       the largest value
int find_max(const std::vector<int>& data) {
    int n(data.size());
    int current_max{data[0]};                // assume first entry is biggest (for now)
    for (int j = 1; j < n; j++) {            // consider all other entries
        if (data[j] > current_max)           // if data[j] is biggest thus far...
            current_max = data[j];           // record data[j] as the current max
    }
    return current_max;
}

}  // namespace dsac::analysis
