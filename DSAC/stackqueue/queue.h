#pragma once
#include <vector>

namespace dsac::stackqueue {

/// A simplified version of the STL queue class
template <typename T, typename Container=std::deque<T>>
class queue {

  private:
    Container data;

  public:
    /// return the number of elements currently in the queue
    int size() const { return data.size(); }
    
    /// return whether the queue is currently empty
    bool empty() const { return data.empty(); }

    /// return const reference to the first element of the queue
    const T& front() const { return data.front(); }

    /// return live (non-const) reference to the first element of the queue
    T& front() { return data.front(); }

    /// return const reference to the last element of the queue
    const T& back() const { return data.back(); }

    /// return live (non-const) reference to the last element of the queue
    T& back() { return data.back(); }

    /// add an element to the back of the queue
    void push(const T& elem) { data.push_back(elem); }

    /// remove the first element from the queue
    void pop() { data.pop_front(); }
};

}  // namespace dsac::stackqueue
