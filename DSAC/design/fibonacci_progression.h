#pragma once
#include <iostream>

namespace dsac::design {

/// A Fibonacci progression, in which each number is the sum of the previous two numbers
class FibonacciProgression : public Progression {
  protected:
    long prev;

    /// Replaces (prev,current) with (current,current+prev)
    virtual void advance() {
        long temp{prev};
        prev = current;
        current += temp;
    }
    
  public:
    /// Constructs a Fibonacci sequence using the given first and second values
    /// @param first the first value of the sequence (default: 0)
    /// @param start the second value of the sequence (default: 1)
    FibonacciProgression(long first = 0, long second = 1) : Progression{first}, prev{second - first} {}
    
}; // FibonacciProgression class

}  // namespace dsac::design
