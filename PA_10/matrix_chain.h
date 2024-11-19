#pragma once
#include <iostream>
#include <algorithm>       // provides std::min
#include <limits>          // std::numeric_limits<int>::max()
#include <vector>

namespace dsac::text {

std::vector<std::vector<int>> matrix_chain(const std::vector<int>& d) {
    int n = d.size() - 1;                                         // number of matrices
    std::vector<std::vector<int>> N(n, std::vector<int>(n, 0));   // n-by-n matrix; initially zeros
    for (int b = 1; b < n; b++)                                   // number of products in subchain
        for (int i = 0; i < n - b; i++) {                         // start of subchain
            int j{i + b};                                         // end of subchain
            N[i][j] = std::numeric_limits<int>::max();            // used as 'infinity'
            for (int k = i; k < j; k++)
                N[i][j] = std::min(N[i][j], N[i][k] + N[k+1][j] + d[i]*d[k+1]*d[j+1]);
        }

    // Print the result table
    std::cout << "Resulting table of minimum operations:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << N[i][j] << "\t";
        }
        std::cout << std::endl;
    }


    return N;
}
    
} // namespace dsac::text



