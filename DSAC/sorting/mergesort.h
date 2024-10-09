#pragma once

#include <algorithm>       // defines std::min
#include <list>
#include <vector>

namespace dsac::sorting {

/// Merges the contents of sorted vectors S1 and S2 into result S
template <typename T, typename Compare>
void merge(const std::vector<T>& S1, const std::vector<T>& S2, std::vector<T>& S, Compare comp) {
    S.resize(S1.size() + S2.size());
    int i{0}, j{0}, k{0};
    while (k < S.size()) {
        if (j == S2.size() || (i < S1.size() && comp(S1[i], S2[j])))
            S[k++] = S1[i++];                                // copy ith element of S1 to S
        else
            S[k++] = S2[j++];                                // copy jth element of S2 to S
    }
}

/// Sorts the contents of vector S using the given comparator to define the element ordering
template <typename T, typename Compare>
void merge_sort(std::vector<T>& S, Compare comp) {
    int n(S.size());
    if (n < 2) return;                                       // vector is trivially sorted
    int mid{n / 2};
    std::vector<T> S1(S.begin(), S.begin() + mid);           // copy of first half
    std::vector<T> S2(S.begin() + mid, S.end());             // copy of second half
    // conquer (with recursion)
    merge_sort(S1, comp);
    merge_sort(S2, comp);
    // merge results
    merge(S1, S2, S, comp);                                  // merge sorted halves back into original
}


// merges in[start..start+inc-1] and in[start+inc..start+2*inc-1] into out[start..start+2*inc-1]
// (truncated if increments extend beyond the end of the array)
template <typename T, typename Compare>
void merge(const std::vector<T>& in, std::vector<T>& out, Compare comp, int start, int inc) {
    int n(in.size());
    int x{start};                                            // index into run 1
    int y{start + inc};                                      // index into run 2
    int z{start};                                            // index into output
    int stop1 = std::min(start + inc, n);                    // boundary for run 1
    int stop2 = std::min(start + 2 * inc, n);                // boundary for run 2
    while (x < stop1 || y < stop2) {
        if (y >= stop2 || (x < stop1 && comp(in[x], in[y])))
            out[z++] = in[x++];                              // take next from run 1
        else
            out[z++] = in[y++];                              // take next from run 2
    }
}
    
template <typename T, typename Compare>
void merge_sort_bottom_up(std::vector<T>& S, Compare comp) {
    int n(S.size());
    std::vector<T> temp(n);                                  // make a new temporary vector
    for (int i = 1; i < n; i *= 2) {                         // consider runs of length 1, 2, 4, 8, ...
        for (int j = 0; j < n; j += 2*i)                     // merge pair of runs starting at j
            merge(S, temp, comp, j, i);                      // (last pass may involve partial runs)
        std::swap(S, temp);                                  // move results back to S (constant time swap)
    }
}

    
template <typename T, typename Compare>
void merge(const std::list<T>& S1, const std::list<T>& S2, std::list<T>& S, Compare comp) {
    S.clear();
    typename std::list<T>::const_iterator walk1 = S1.begin();
    typename std::list<T>::const_iterator walk2 = S2.begin();
    while (walk1 != S1.end() || walk2 != S2.end()) {
        if (walk2 == S2.end() || (walk1 != S1.end() && comp(*walk1, *walk2)))
            S.push_back(*(walk1++));                         // copy element from S1 to S
        else
            S.push_back(*(walk2++));                         // copy element from S2 to S
    }
}                                  

template <typename T, typename Compare>
void merge_sort(std::list<T>& S, Compare comp) {
    int n(S.size());
    if (n < 2) return;                                       // list is trivially sorted
    // divide
    typename std::list<T>::iterator walk = S.begin();
    std::list<T> S1,S2;
    while (S1.size() < n / 2)
        S1.push_back(*(walk++));                             // copy first n/2 elements to S1
    while (walk != S.end())
        S2.push_back(*(walk++));                             // copy remaining elements to S2
    // conquer (with recursion)
    merge_sort(S1, comp);
    merge_sort(S2, comp);
    merge(S1, S2, S, comp);                                  // merge sorted halves back into original
}

// versions that use std::less as default comparator
 
template <typename T>
void merge_sort(std::vector<T>& S) { merge_sort(S, std::less<T>()); }
    
template <typename T>
void merge_sort(std::list<T>& S) { merge_sort(S, std::less<T>()); }
    
template <typename T>
void merge_sort_bottom_up(std::vector<T>& S) { merge_sort(S, std::less<T>()); }


 
} // namespace dsac::sorting
    
