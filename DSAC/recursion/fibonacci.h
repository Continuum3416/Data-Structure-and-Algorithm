#pragma once

#include <utility>  // std::pair

namespace dsac::recursion {

/// Returns the nth Fibonacci number (inefficiently).
long fibonacci_bad(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci_bad(n - 2) + fibonacci_bad(n - 1);
}

/// Returns the pair of Fibonacci numbers, F(n) and F(n-1).
std::pair<long,long> fibonacci_good(int n) {
    if (n <= 1) {
        return std::make_pair(n, 0);
    } else {
        auto temp{fibonacci_good(n - 1)};                             // returns { F(n-1), F(n-2) }
        return std::make_pair(temp.first + temp.second, temp.first);  // we want { F(n), F(n-1) }
    }
}

/// Don't call this (infinite) version.
long fibonacci(int n) {
    return fibonacci(n);              // After all F(n) does equal F(n)
}
    
    
}  // namespace dsac::recursion
