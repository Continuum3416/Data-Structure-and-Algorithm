#pragma once
#include <string>

namespace dsac::design {

/// A counter that maintains a single integer value
class Counter {
  private:
    int value{0};       // a simple integer instance variable

  public:
    /// Constructs a new Counter with value zero.
    Counter();

    /// Constructs a new Counter with given initial value.
    /// @param initial the initial value
    Counter(int initial);

    /// Returns the current counter value.
    /// @return the current counter value
    int get_value() const;

    /// Increments the counter value by one.
    void increment();

    /// Increments the counter value by the specified delta.
    /// @param delta the amount of the increment
    void increment(int delta);

    /// Resets the counter value to zero.
    void reset();
    
}; // Counter class

}  // namespace dsac::design
