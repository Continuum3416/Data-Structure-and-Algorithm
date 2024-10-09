#pragma once

#include <algorithm>       // provides std::min
#include <string>
#include <unordered_map>

namespace dsac::text {

/// Returns the lowest index at which substring pattern begins in text (or else -1)
int find_brute(const std::string& text, const std::string& pattern) {
    int n(text.size());
    int m(pattern.size());
    for (int i = 0; i <= n - m; i++) {                   // try every starting index within text
        int k{0};                                        // k is index into pattern
        while (k < m && text[i+k] == pattern[k])         // kth character of pattern matches
            k++;
        if (k == m)                                      // if we reach the end of the pattern,
            return i;                                    // substring text[i..i+m-1] is a match
    }
    return -1;                                           // search failed
}

/// Returns the lowest index at which substring pattern begins in text (or else -1).
int find_boyer_moore(const std::string& text, const std::string& pattern) {
    int n(text.size());
    int m(pattern.size());
    if (m == 0) return 0;                                // trivial search for empty string
    std::unordered_map<char,int> last;                   // the 'last' map
    for (int i = 0; i < n; i++)
        last[text[i]] = -1;                              // set -1 as default for all text characters
    for (int k = 0; k < m; k++)
        last[pattern[k]] = k;                            // rightmost occurrence in pattern is last
    // start with the end of the pattern aligned at index m-1 of the text
    int i{m - 1};                                        // an index into the text
    int k{m - 1};                                        // an index into the pattern
    while (i < n) {
        if (text[i] == pattern[k]) {                     // a matching character
            if (k == 0) return i;                        // entire pattern has been found
            i--;                                         // otherwise, examine previous
            k--;                                         // characters of text/pattern
        } else {
            i += m - std::min(k, 1 + last[text[i]]);     // case analysis for jump step
            k = m - 1;                                   // restart at end of pattern
        }
    }
    return -1;                                           // pattern was never found
}

/// Returns the failure table for Knuth, Morris Pratt algorithm
std::vector<int> compute_kmp_fail(const std::string& pattern) {
    int m(pattern.size());
    std::vector<int> fail(m,0);                          // by default, all overlaps are zero
    int j{1};
    int k{0};
    while (j < m) {                                      // compute fail[i] during this pass, if nonzero
        if (pattern[j] == pattern[k]) {                  // k + 1 characters match thus far
            fail[j] = k + 1;
            j++;
            k++;
        } else if (k > 0)                                // k follows a matching prefix
            k = fail[k - 1];
        else                                             // no match found starting at j
            j++;
    }
    return fail;
}
    
/// Returns the lowest index at which substring pattern begins in text (or else -1).
int find_kmp(const std::string& text, const std::string& pattern) {
    int n(text.size());
    int m(pattern.size());
    if (m == 0) return 0;                                // trivial search for empty string
    std::vector<int> fail{compute_kmp_fail(pattern)};    // computed by separate utility function
    int i{0};                                            // index into text
    int k{0};                                            // index into pattern
    while (i < n) {
        if (text[i] == pattern[k]) {                     // pattern[0..k] matched thus far
            if (k == m - 1) return i - m + 1;            // match is complete
            i++;                                         // otherwise, try to extend match
            k++;
        } else if (k > 0)
            k = fail[k - 1];                             // reuse suffix of P[0..k-1]
        else
            i++;
    }
    return -1;                                           // reached end without match
}

} // namespace dsac::text



