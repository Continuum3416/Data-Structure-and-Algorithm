#pragma once

#include <stdexcept>  // provides std::invalid_argument

namespace dsac::recursion {

/// Computes the factorial of the given (nonnegative) integer)
long factorial(int n) {
    if (n < 0)
        throw std::invalid_argument("n must be nonnegative");
    else if (n == 0)
        return 1;                                 // base case
    else
        return n * factorial(n-1);                // recursive case
}

}  // namespace dsac::recursion
