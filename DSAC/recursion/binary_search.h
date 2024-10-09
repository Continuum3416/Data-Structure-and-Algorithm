#pragma once

namespace dsac::recursion {

/// Returns true if the target value is found in the indicated portion of the data array.
/// This search only considers the array portion from data[low] to data[high] inclusive.
///
/// @param data   sorted array of integers
/// @param target the query value
/// @param low    the index of the left end of the search range
/// @param high   the index of the right end of the search range
/// @return true  if the target is found, false otherwise
bool binary_search(int data[], int target, int low, int high) {
    if (low > high)
        return false;                                             // interval empty; no match
    else {
        int mid{(low + high) / 2};
        if (target == data[mid])
            return true;                                          // found a match
        else if (target < data[mid])
            return binary_search(data, target, low, mid - 1);     // recur left of the middle
        else
            return binary_search(data, target, mid + 1, high);    // recur right of the middle
    }
}

/// Returns true if the target value is found in the array of length n.
///
/// @param data   sorted array of integers
/// @param n      length of data
/// @param target the query value
/// @return true  if the target is found, false otherwise
bool binary_search(int data[], int n, int target) {
    return binary_search(data, target, 0, n - 1);                    // start the recursion
}

/// Returns true if the target value is found in the array of length n.
///
/// @param data   sorted array of integers
/// @param n      length of data
/// @param target the query value
/// @return true  if the target is found, false otherwise
bool binary_search_iterative(int data[], int n, int target) {
    int low{0};
    int high{n - 1};
    while (low <= high) {
        int mid{(low + high) / 2};
        if (target == data[mid])          // found a match
            return true;
        else if (target < data[mid])
            high = mid - 1;               // only consider values left of mid
        else
            low = mid + 1;                // only consider values right of mid
    }
    return false;                         // loop ended without success
}

}  // namespace dsac::recursion
