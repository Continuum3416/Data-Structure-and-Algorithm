#pragma once
#include <iostream>

namespace dsac::design {

/// An arithmetic progression, in which each number is the previous number plus some fixed increment
class ArithmeticProgression : public Progression {
  protected:
    long increment;

    /// Adds the arithmetic increment to the current value
    virtual void advance() {
        current += increment;
    }
    
  public:
    /// Constructs an arithmetic progression with given start value (default: 0) and given stepsize (default: 1)
    /// @param stepsize the increment value for the arithmetic progression
    /// @param start the first value of the arithmetic progression
    ArithmeticProgression(long stepsize = 1, long start = 0) : Progression{start}, increment{stepsize} {}
    
}; // ArithmeticProgression class

}  // namespace dsac::design
