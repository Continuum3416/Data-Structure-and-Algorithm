#pragma once

#include <algorithm>       // provides std::min
#include <string>
#include <unordered_map>


int comparisons = 0;

namespace dsac::text {

/// Returns the lowest index at which substring pattern begins in text (or else -1)
// Brute Force with comparison count
int find_brute(const std::string& text, const std::string& pattern, int& comparisons) {
    int n = text.size();
    int m = pattern.size();
    for (int i = 0; i <= n - m; i++) { // try every starting index within text
        int k = 0;                     // k is index into pattern
        while (k < m && text[i + k] == pattern[k]) { // kth character matches
            comparisons++;
            k++;
        }
        if (k == m) { // if we reach the end of the pattern
            return i; // substring text[i..i+m-1] is a match
        }
        comparisons++; // mismatch
    }
    return -1; // search failed
}

// Boyer-Moore with comparison count
int find_boyer_moore(const std::string& text, const std::string& pattern, int& comparisons) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) return 0; // trivial search for empty string
    std::unordered_map<char, int> last;
    for (int i = 0; i < n; i++) last[text[i]] = -1; // set default for text characters
    for (int k = 0; k < m; k++) last[pattern[k]] = k; // rightmost occurrence

    int i = m - 1; // index into text
    int k = m - 1; // index into pattern
    while (i < n) {
        comparisons++;
        if (text[i] == pattern[k]) { // a matching character
            if (k == 0) return i;    // entire pattern found
            i--;                     // check previous
            k--;
        } else {
            i += m - std::min(k, 1 + last[text[i]]);
            k = m - 1; // restart at pattern's end
        }
    }
    return -1; // pattern not found
}

// Compute failure function for KMP
std::vector<int> compute_kmp_fail(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> fail(m, 0); // by default, all overlaps are zero
    int j = 1;
    int k = 0;
    while (j < m) { // compute fail[j]
        if (pattern[j] == pattern[k]) {
            fail[j] = k + 1;
            j++;
            k++;
        } else if (k > 0) {
            k = fail[k - 1];
        } else {
            j++;
        }
    }
    return fail;
}

// KMP with comparison count
int find_kmp(const std::string& text, const std::string& pattern, int& comparisons) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) return 0; // trivial search for empty string
    std::vector<int> fail = compute_kmp_fail(pattern);
    int i = 0; // index into text
    int k = 0; // index into pattern
    while (i < n) {
        comparisons++;
        if (text[i] == pattern[k]) { // characters match
            if (k == m - 1) return i - m + 1; // complete match
            i++;
            k++;
        } else if (k > 0) {
            k = fail[k - 1]; // reuse previous suffix
        } else {
            i++;
        }
    }
    return -1; // no match
}



} // namespace dsac::text



