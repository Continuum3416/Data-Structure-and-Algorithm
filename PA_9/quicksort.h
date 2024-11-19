#pragma once

#include <algorithm>       // defines std::min
#include <list>
#include <vector>

namespace dsac::sorting {

struct SortStats {
    int comparisons = 0;
    int dataMoves = 0;
};

template <typename T, typename Compare>
void quick_sort_in_place(std::vector<T>& S, Compare comp, int a, int b, SortStats& stats) {
    if (a >= b) return;                        // subarray is trivially sorted
    T pivot{S[b]};
    int left{a};
    int right{b - 1};
    while (left <= right) {
        // scan until reaching value equal or larger than pivot (or right marker)
        while (left <= right && comp(S[left], pivot)) {
            stats.comparisons++;
            left++;
        }
        // scan until reaching value equal or smaller than pivot (or left marker)
        while (left <= right && comp(pivot, S[right])) {
            stats.comparisons++;
            right--;
        }
        if (left <= right) {                   // indices did not strictly cross
            // swap values and shrink range
            std::swap(S[left], S[right]);
            stats.dataMoves++;
            left++;
            right--;
        }
    }
    // put pivot into its final place (currently marked by left index)
    std::swap(S[left], S[b]);
    stats.dataMoves++;

    // make recursive calls
    quick_sort_in_place(S, comp, a, left - 1, stats);
    quick_sort_in_place(S, comp, left + 1, b, stats);
}

// version without extraneous arguments
template <typename T, typename Compare>
void quick_sort_in_place(std::vector<T>& S, Compare comp, SortStats& stats) {
    quick_sort_in_place(S, comp, 0, S.size() - 1, stats);
}

// versions that use std::less as default comparator
template <typename T>
void quick_sort(std::vector<T>& S) { quick_sort(S, std::less<T>()); }
    
template <typename T>
void quick_sort_in_place(std::vector<T>& S) { 
    SortStats stats;
    quick_sort_in_place(S, std::less<T>(), stats);
    // Optionally print out stats after sorting
    std::cout << "Comparisons: " << stats.comparisons << std::endl;
    std::cout << "Data Moves: " << stats.dataMoves << std::endl;
}

} // namespace dsac::sorting
