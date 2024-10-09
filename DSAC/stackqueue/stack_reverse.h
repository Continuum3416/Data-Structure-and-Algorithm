#pragma once
#include <stack>

namespace dsac::stackqueue {

/// Reverses the contents of the given array.
/// @param data  an array of elements
/// @param n     length of the array
template <typename T>    
void reverse(T data[], int n) {
    std::stack<T> buffer;
    for (int j = 0; j < n; j++)
        buffer.push(data[j]);
    for (int j = 0; j < n; j++) {
        data[j] = buffer.top();
        buffer.pop();
    }
}

}  // namespace dsac::stackqueue
