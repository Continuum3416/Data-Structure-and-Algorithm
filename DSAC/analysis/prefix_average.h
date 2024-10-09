#pragma once

#include <vector>

namespace dsac::analysis {

/// Computes prefix average such that for each j,
/// result a[j] equals the average of x[0], ..., x[j].
/// @param x     a vector of doubles
/// @return a vector of prefix averages
std::vector<double> prefix_averages1(const std::vector<double>& x) {
    int n(x.size());
    std::vector<double> a(n);         // filled with n zeros by default
    for (int j = 0; j < n; j++) {
        double total{0.0};            // begin computing x[0] + ... + x[j]
        for (int i = 0; i <= j; i++)
            total += x[i];
        a[j] = total / (j+1);         // record the average
    }
    return a;
}

/// Computes prefix average such that for each j,
/// result a[j] equals the average of x[0], ..., x[j].
/// @param x     a vector of doubles
/// @return a vector of prefix averages
std::vector<double> prefix_averages2(const std::vector<double>& x) {
    int n(x.size());
    std::vector<double> a(n);         // filled with n zeros by default
    double total{0.0};                // compute prefix sum as x[0] + x[1] + ...
    for (int j = 0; j < n; j++) {
        total += x[j];                // update prefix sum to include x[j]
        a[j] = total / (j+1);         // computer average based on current sum
    }
    return a;
}

}  // namespace dsac::analysis
