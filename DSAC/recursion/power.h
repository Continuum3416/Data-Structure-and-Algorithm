#pragma once

namespace dsac::recursion {

/// Computes the value of x raised to the nth power, for nonnegative integer n.
double power_slow(double x, int n) {
    if (n == 0)
        return 1;
    else
        return x * power_slow(x, n - 1);
}

/// Computes the value of x raised to the nth power, for nonnegative integer n.
double power(double x, int n) {
    if (n == 0)
        return 1;
    else {
        double partial{power(x, n / 2)};         // rely on truncated division of n / 2
        double result{partial * partial};
        if (n % 2 == 1)                          // if n is odd, include extra factor of x
            result *= x;
        return result;
    }
}

}  // namespace dsac::recursion
