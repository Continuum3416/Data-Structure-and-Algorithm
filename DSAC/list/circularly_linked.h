#pragma once

#include <utility>     // provides std::swap

namespace dsac::list {

/// circularly linked list
template <typename T>
class CircularlyLinkedList {
  private:
    //---------------- nested Node class ----------------
    class Node {
      public:
        T elem;                           // stored element
        Node* next;                       // pointer to next node

        Node(const T& element, Node* nxt = nullptr) : elem{element}, next{nxt} {}
    };  //------------ end of nested Node class ------------

    // CircularlyLinkedList instance variables
    int sz{0};                            // number of actual entries in list
    Node* tail{nullptr};                  // the node storing last element of the list

  public:
    /// Constructs an empty list
    CircularlyLinkedList() {}

    // ---------- access functions ----------

    /// Returns the number of elements stored
    /// @return the number of elements stored
    int size() const { return sz; }

    /// Tests whether the list is empty.
    /// @return true if the list is empty, false otherwise
    bool empty() const { return sz == 0; }

    /// Returns live reference to the first element of the list; behavior undefined if list is empty
    /// @return reference to first element of the list
    T& front() { return tail->next->elem; }

    /// Returns const reference to the first element of the list; behavior undefined if list is empty
    /// @return reference to first element of the list
    const T& front() const { return tail->next->elem; }

    /// Returns live reference to the last element of the list; behavior undefined if list is empty
    /// @return reference to last element of the list
    T& back() { return tail->elem; }

    /// Returns const reference to the last element of the list; behavior undefined if list is empty
    /// @return reference to last element of the list
    const T& back() const { return tail->elem; }

    // ---------- update functions ----------

    /// Inserts element at the beginning of the list
    /// @param elem   the new element
    void push_front(const T& elem) {
        if (sz == 0) {
            tail = new Node(elem);
            tail->next = tail;                        // link to itself circularly
        } else {
            tail->next = new Node(elem, tail->next);  // splice new node after the tail
        }
        sz++;
    }

    /// Inserts element at the end of the list
    /// @param elem   the new element
    void push_back(const T& elem) {
        push_front(elem);                             // start by inserting at front of list
        tail = tail->next;                            // then rotate newest node to be tail
    }

    /// Removes the first element of the list
    void pop_front() {
        Node* head = tail->next;
        if (head == tail)
            tail = nullptr;                           // must be the only node left
        else
            tail->next = head->next;
        delete head;
        sz--;
    }

    /// Rotates the first element to the back of the list
    void rotate() {
        if (tail != nullptr)                          // if empty, do nothing
            tail = tail->next;                        // otherwise, the old head becomes the new tail
    }
    
    //------------------------------------------------
    // rule-of-five behaviors
    //------------------------------------------------

  private:
    // presumes valid empty list when called
    void clone(const CircularlyLinkedList& other) {
        Node* walk = other.tail;
        for (int i = 0; i < other.size(); i++) {
            push_back(walk->next->elem);
            walk = walk->next;
        }
    }

  public:
    /// non-member function to swap two lists
    friend void swap(CircularlyLinkedList& a, CircularlyLinkedList& b) {
        std::swap(a.sz, b.sz);
        std::swap(a.tail, b.tail);
    }

    /// Resets the list to empty
    void clear() {
        while (sz > 0) pop_front();
    }

    /// Copy constructor
    CircularlyLinkedList(const CircularlyLinkedList& other) { clone(other); }

    /// Copy assignment
    CircularlyLinkedList& operator=(const CircularlyLinkedList& other) {
        if (this != &other) {     // do nothing for self-assignment
            clear();
            clone(other);
        }
        return *this;
    }

    /// Move constructor
    CircularlyLinkedList(CircularlyLinkedList&& other) { swap(*this, other); }

    /// Move assignment
    CircularlyLinkedList& operator=(CircularlyLinkedList&& other) {
        if (this != &other) swap(*this, other);   // do nothing for self-assignment
        return *this;
    }

    /// default destructor
    ~CircularlyLinkedList() { clear(); }

};

}  // namespace dsac::list
