#pragma once
#include <algorithm>     // provides max
#include <stdexcept>     // provides out_of_range exception

namespace dsac::array {

/// A dynamically sized array (as a simplified version of std::vector)
/// @tparam T the element type    
template <typename T>
class Vector {
  private:
    /// capacity of the array
    int cap{0};

    /// number of actual entries
    int sz{0};

    /// pointer to array of elements
    T* data{nullptr};

  public:
    /// Constructs an empty vector
    Vector() {}

    /// Returns the current capacity of the underlying array
    /// @return the size of the underlying array
    int capacity() const { return cap; }

    /// Returns the number of elements stored
    /// @return the number of elements stored
    int size() const { return sz; }

    /// Tests whether the vector is empty.
    /// @return true if the vector is empty, false otherwise
    bool empty() const { return sz == 0; }

    /// Returns const reference to the element at index i; behavior is undefined if i is out of bounds
    /// @param i index of desired element
    /// @return element at index i
    const T& operator[](int i) const { return data[i]; }

    /// Returns reference to the element at index i; behavior is undefined if i is out of bounds
    /// @param i index of desired element
    /// @return element at index i
    T& operator[](int i) { return data[i]; }

    /// Returns const reference to the element at index i; raises out_of_range exception with invalid index
    /// @param i index of desired element
    /// @return element at index i
    /// @throw out_of_range exception if index is invalid for current vector
    const T& at(int i) const {
        if (i < 0 || i >= sz) throw std::out_of_range("Invalid index");
        return data[i];
    }

    /// Returns reference to the element at index i; raises out_of_range exception with invalid index
    /// @param i index of desired element
    /// @return element at index i
    /// @throw out_of_range exception if index is invalid for current vector
    T& at(int i) {
        if (i < 0 || i >= sz) throw std::out_of_range("Invalid index");
        return data[i];
    }

    /// Returns a const reference to the first element; behavior is undefined if vector is empty
    /// @return reference to first element
    const T& front() const { return data[0]; }

    /// Returns a live reference to the first element; behavior is undefined if vector is empty
    /// @return reference to first element
    T& front() { return data[0]; }

    /// Returns a const reference to the last element; behavior is undefined if vector is empty
    /// @return reference to last element
    const T& back() const { return data[sz - 1]; }

    /// Returns a live reference to the last element; behavior is undefined if vector is empty
    /// @return reference to last element
    T& back() { return data[sz - 1]; }

    /// Inserts an element at end of the vector
    /// @param elem   the new element
    void push_back(const T& elem) {
        if (sz == cap) reserve(std::max(1, 2 * cap));  // double array size
        data[sz++] = elem;
    }

    /// Removes an element from the end of the vector
    void pop_back() { sz--; }

    /// Inserts an element at index i; behavior is undefined if i is out of bounds
    /// @param i      index at which new element should be placed
    /// @param elem   the new element
    void insert(int i, const T& elem) {
        if (sz == cap) reserve(std::max(1, 2 * cap));  // double array size
        for (int k = sz - 1; k >= i; k--)              // shift subsequent elements upward
            data[k + 1] = std::move(data[k]);
        data[i] = elem;
        sz++;                                          // there is one more element
    }

    /// Removes element at index i; behavior is undefined if i is out of bounds
    /// @param i index of element to be removed
    void erase(int i) {
        for (int k = i + 1; k < sz; k++)               // shift subsequent elements down
            data[k - 1] = std::move(data[k]);
        sz--;                                          // there is one less element
    }

    /// Requests that the vector capacity be at least as large as the indicated capacity
    /// The function has no effect if the current capacity is already larger than the parameter.
    /// @param cap  the minimum capacity after the operation
    void reserve(int minimum) {
        if (cap < minimum) {
            T* temp{new T[minimum]};
            for (int k = 0; k < sz; k++)
                temp[k] = std::move(data[k]);
            delete[] data;                             // delete old array (if any)
            data = temp;                               // use new array 
            cap = minimum;                             // new capacity
        }
    }

    //------------------------------------------------
    // rule-of-five behaviors
    //------------------------------------------------

    /// Copy constructor
    Vector(const Vector& other) { clone(other); }

    /// Copy assignment
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            clone(other);
        }
        return *this;
    }

    /// Move constructor
    Vector(Vector&& other) { transfer(other); }

    /// Move assignment
    Vector& operator=(Vector&& other) {
        if (this != &other) {
            delete[] data;
            transfer(other);
        }
        return *this;
    }

    /// Destructor
    ~Vector() { delete[] data; }
    
  private:
    void clone(const Vector& other) {
        cap = other.cap;
        sz = other.sz;
        data = new T[cap];
        for (int k = 0; k < sz; k++) {
            data[k] = other.data[k];
        }
    }

    void transfer(Vector& other) {
        cap = other.cap;
        sz = other.sz;
        data = other.data;
        other.cap = other.sz = 0;       // reset other to empty state
        other.data = nullptr;
    }

  public:

    //-------------------------------------------------------
    // Support for iterator as a bidirectional access iterator
    //-------------------------------------------------------
    /// A bidirectional iterator
    class iterator {
        friend class Vector;       // needed by Vector's insert(it,elem) and erase(it)
        
      private:
        Vector* vec;
        int ind;                   // index within the vector
        
      public:
        iterator(Vector* v = nullptr, int i = -1) : vec{v}, ind{i} {}
        T& operator*() const { return (*vec)[ind]; }
        T* operator->() const { return &(*vec)[ind]; }
        iterator& operator++() { ++ind; return *this; }
        iterator operator++(int) { iterator old(*this); ++ind; return old; }
        iterator& operator--() { --ind; return *this; }
        iterator operator--(int) { iterator old(*this); --ind; return old; }
        bool operator==(iterator rhs) const { return vec == rhs.vec && ind == rhs.ind; }
        bool operator!=(iterator rhs) const { return !(*this == rhs); }
    };

    //-------------------------------------------------------
    // Support for const_iterator as a bidirectional access iterator
    //-------------------------------------------------------
    /// A bidirectional const_iterator
    class const_iterator {
      private:
        const Vector* vec;
        int ind;                   // index within the vector
        
      public:
        const_iterator(const Vector* v = nullptr, int i = -1) : vec{v}, ind{i} {}
        const T& operator*() const { return (*vec)[ind]; }
        const T* operator->() const { return &(*vec)[ind]; }
        const_iterator& operator++() { ++ind; return *this; }
        const_iterator operator++(int) { const_iterator old(*this); ++ind; return old; }
        const_iterator& operator--() { --ind; return *this; }
        const_iterator operator--(int) { const_iterator old(*this); --ind; return old; }
        bool operator==(const_iterator rhs) const { return vec == rhs.vec && ind == rhs.ind; }
        bool operator!=(const_iterator rhs) const { return !(*this == rhs); }
    };

    iterator begin() { return iterator(this, 0); }
    iterator end() { return iterator(this, sz); }
    const_iterator begin() const { return const_iterator(this, 0); }
    const_iterator end() const { return const_iterator(this, sz); }

    /// Inserts an element immediately before the given iterator position
    /// @param it     iterator defining the insertion position
    /// @param elem   the new element
    /// @return iterator of newly inserted element
    iterator insert(iterator it, const T& elem) {
        insert(it.ind, elem);                            // call our index-based version
        return it;                                       // new element was placed at the given index
    }

    /// Removes the element at the given iterator position
    /// @param it     iterator defining the position of element to be removed
    /// @return iterator just beyond the removed element
    iterator erase(iterator it) {
        erase(it.ind);                                   // call our index-based version
        return it;                                       // element after removed has been shifted
    }
    
}; // Vector class

}  // namespace dsac::array
