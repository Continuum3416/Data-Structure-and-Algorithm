#pragma once

#include <vector>

namespace dsac::analysis {

/// Returns true if there is no element common to all three groups
/// @param groupA   a vector of integers
/// @param groupB   a vector of integers
/// @param groupC   a vector of integers
/// @return true if there does not exist a value common to all three groups
bool is_disjoint1(const std::vector<int>& groupA, const std::vector<int>& groupB, const std::vector<int>& groupC) {
    for (int a : groupA)
        for (int b : groupB)
            for (int c : groupC)
                if ((a == b) && (b == c))
                    return false;              // we found a common value
    return true;                               // if we reach this, sets are disjoint
}

/// Returns true if there is no element common to all three groups
/// @param groupA   a vector of integers
/// @param groupB   a vector of integers
/// @param groupC   a vector of integers
/// @return true if there does not exist a value common to all three groups
bool is_disjoint2(const std::vector<int>& groupA, const std::vector<int>& groupB, const std::vector<int>& groupC) {
    for (int a : groupA)
        for (int b : groupB)
            if (a == b)                        // match between A and B; look for it in C
                for (int c : groupC)
                    if (a == c)                // three-way match
                        return false;
    return true;                               // if we reach this, sets are disjoint
}

}  // namespace dsac::analysis
