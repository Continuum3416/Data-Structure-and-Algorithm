/// Definition for a templated ArrayQueue class with fixed capacity

#pragma once
#include <memory>        // defines unique_ptr
#include <stdexcept>     // defines overflow_error

namespace dsac::stackqueue {

/// Implementation of a queue interface using an array with bounded capacity
/// @param T the element type
template <typename T>
class ArrayQueue {

private:
    /// default capacity of a queue
    enum { CAPACITY = 1000 };

    /// actual capacity of the underlying array
    int capacity;
    
    /// index of the front of the queue
    int f{0};

    /// current number of elements in the queue
    int sz{0};

    /// pointer to the underlying array
    std::unique_ptr<T[]> data;
    
public:
    /// Construct a new queue with given capacity (default 1000)
    ArrayQueue(int cap = CAPACITY) : capacity(cap), data(std::make_unique<T[]>(cap)) { }

    /// return number of elements currently in the queue
    int size() const { return sz; }
    
    /// return whether the queue is currently empty
    bool empty() const { return sz == 0; }

    /// return const reference to the first element of the queue
    const T& front() const { return data[f]; }

    /// return live (non-const) reference to the first element of the queue
    T& front() { return data[f]; }

    /// return const reference to the last element of the queue
    const T& back() const { return data[(f + sz - 1) % capacity]; }

    /// return live (non-const) reference to the last element of the queue
    T& back() { return data[(f + sz - 1) % capacity]; }

    /// add element to the end of the queue
    /// @param elem the new element
    /// @throw overflow_error if queue is already at full capacity
    void push(const T& elem) {
        if (size() == capacity)
            throw std::overflow_error("Queue overflow");
        int avail{(f + sz) % capacity};                  // compute next available index
        data[avail] = elem;
        sz++;
    }

    /// remove the first element from the queue
    void pop() {
        f = (f + 1) % capacity;                          // advance the front one step (circularly)
        sz--;
    }
};

}  // namespace dsac::stackqueue
