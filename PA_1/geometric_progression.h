#pragma once
#include <iostream>

namespace dsac::design {

/// A geometric progression, in which each number is the previous number plus times some fixed multiplier
class GeometricProgression : public Progression {
  protected:
    long base;

    /// Multiply the current value by the geometric base
    virtual void advance() {
        current *= base;
    }
    
  public:
    /// Constructs a geometric progression with given base and start 
    /// @param base the base of the geometric progression (default: 2)
    /// @param start the first value of the geometric progression (default: 1)
    GeometricProgression(long b = 2, long start = 1) : Progression{start}, base{b} {}
    
}; // GeometricProgression class

}  // namespace dsac::design
