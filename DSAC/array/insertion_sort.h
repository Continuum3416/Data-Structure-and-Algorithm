#pragma once

namespace dsac::array {

/// Sorts an array of n elements.
/// Elements must be comparable with < operator    
/// @param data  an array of elements
/// @param n     the length of the array
template <typename T>    
void insertion_sort(T data[], int n) {
    for (int k = 1; k < n; k++) {               // begin with second character
        T cur{std::move(data[k])};              // might relocate cur=data[k]
        int j{k};                               // find correct index j for cur
        while (j > 0 && cur < data[j - 1]) {    // thus, data[j-1] must move after cur
            data[j] = std::move(data[j - 1]);   // slide data[j-1] rightward
            j--;                                // and consider previous j
        }
        data[j] = std::move(cur);               // this is the proper place for cur
    }
}

}  // namespace dsac::array
