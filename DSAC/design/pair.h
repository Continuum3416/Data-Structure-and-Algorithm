#pragma once

namespace dsac::design {

/// A composite pair (akin to std::pair)
/// @tparam A the type of the first element of a pair
/// @tparam B the type of the second element of a pair
template <typename A, typename B>
class pair {
  public:
    A first;
    B second;

    /// Constructs a default pair (with default element values)
    pair() {}

    /// Constructs a pair with the given element values
    /// @param a the value of the first element of the pair
    /// @param b the value of the second element of the pair
    pair(const A& a, const B& b) : first(a), second(b) {}

    /// Tests whether two pairs are element-by-element equivalent
    /// @param other the right-hand side operand
    /// @return true if the pairs are equivalent, false otherwise
    bool operator==(const pair& other) const {
        return first == other.first && second == other.second;
    }

    /// Tests whether two pairs are not element-by-element equivalent
    /// @param other the right-hand side operand
    /// @return true if the pairs are not equivalent, false otherwise
    bool operator!=(const pair& other) const {
        return !operator==(other);              // the opposite of ==
    }

    /// Performs lexicographical comparison of two pairs
    /// @param other the right-hand side operand
    /// @return true if the left-hand pair is strictly less than the right-hand pair, false otherwise
    bool operator<(const pair& other) const {
        return (first < other.first ||
                (first == other.first && second < other.second));
    }
};

}  // namespace dsac::design
