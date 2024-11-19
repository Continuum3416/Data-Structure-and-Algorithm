#pragma once

#include <algorithm>       // provides std::max, std::reverse
#include <string>
#include <vector>

namespace dsac::text {

/// Returns table such that L[j][k] is length of LCS for X[0..j-1] and Y[0..k-1].
std::vector<std::vector<int>> lcs(std::string& X, std::string& Y) {
    int n(X.size());
    int m(Y.size());
    std::vector<std::vector<int>> L(n + 1, std::vector<int>(m + 1));    // (n+1) x (m+1) table
    for (int j = 0; j < n; j++)
        for (int k = 0; k < m; k++)
            if (X[j] == Y[k])                // align this match
                L[j + 1][k + 1] = L[j][k] + 1;
            else                             // choose to ignore one character
                L[j + 1][k + 1] = std::max(L[j][k + 1], L[j + 1][k]);
    return L;
}

/// Returns the longest common substring of X and Y, given LCS table L
std::string reconstruct_lcs(std::string& X, std::string& Y, const std::vector<std::vector<int>>& L) {
    std::string solution;
    int j(X.size());
    int k(Y.size());
    while (L[j][k] > 0)                      // common characters remain
        if (X[j - 1] == Y[k - 1]) {
            solution += X[j - 1];
            j--;
            k--;
        } else if (L[j - 1][k] >= L[j][k - 1])
            j--;
        else
            k--;
    // return left-to-right version
    std::reverse(solution.begin(), solution.end());
    return solution;
}
    
} // namespace dsac::text



