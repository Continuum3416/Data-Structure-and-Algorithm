#pragma once

#include <utility>     // provides std::swap

namespace dsac::list {

/// singly linked list, akin to std::forward_list
template <typename T>
class SinglyLinkedList {
  private:
    //---------------- nested Node class ----------------
    class Node {
      public:
        T elem;                           // stored element
        Node* next;                       // pointer to next node

        Node(const T& element, Node* nxt = nullptr) : elem{element}, next{nxt} {}
    };  //------------ end of nested Node class ------------

    // SingleLinkedList instance variables
    int sz{0};                            // number of entries in the list
    Node* head{nullptr};                  // raw pointer to first node of list
    Node* tail{nullptr};                  // raw pointer to last node of list

  public:
    /// Constructs an empty list
    SinglyLinkedList() {}

    // ---------- access functions ----------

    /// Returns the number of elements stored
    /// @return the number of elements stored
    int size() const { return sz; }

    /// Tests whether the list is empty.
    /// @return true if the list is empty, false otherwise
    bool empty() const { return sz == 0; }

    /// Returns live reference to the first element of the list; behavior undefined if list is empty
    /// @return reference to first element of the list
    T& front() { return head->elem; }

    /// Returns const reference to the first element of the list; behavior undefined if list is empty
    /// @return reference to first element of the list
    const T& front() const { return head->elem; }

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
        head = new Node(elem, head);   // new head uses old head (possibly null) as next
        if (sz == 0) tail = head;      // special case: newest node is also the tail
        sz++;
    }

    /// Removes the first element of the list; behavior undefined if list is empty
    void pop_front() {
        Node* old{head};
        head = head->next;
        delete old;
        sz--;
        if (sz == 0) tail = nullptr;   // special case as list is now empty
    }

    /// Inserts element at the end of the list
    /// @param elem   the new element
    void push_back(const T& elem) {
        Node* newest{new Node(elem)};
        if (sz == 0)
            head = newest;             // newest node becomes head
        else
            tail->next = newest;       // new node follows old tail
        tail = newest;                 // in either case, newest node becomes the tail
        sz++;
    }

    //-------------------------------------------------------
    // A basic forward iterator
    //-------------------------------------------------------
    class iterator {
        friend class SinglyLinkedList; // needed for SinglyLinkedLists's insert_after and erase_after

    private:
        Node* node_ptr;  // pointer to a node

      public:
        iterator(Node* ptr = nullptr) : node_ptr(ptr) {}
        T& operator*() const { return node_ptr->elem; }
        T* operator->() const { return &node_ptr->elem; }
        iterator& operator++() { node_ptr = node_ptr->next; return *this; }
        iterator operator++(int) { iterator temp(*this); ++(*this); return temp; }
        bool operator==(iterator rhs) const { return node_ptr == rhs.node_ptr; }
        bool operator!=(iterator rhs) const { return node_ptr != rhs.node_ptr; }
    };

    //-------------------------------------------------------
    // const version of iterator
    //-------------------------------------------------------
    class const_iterator {
      private:
        Node* node_ptr;  // pointer to a node

      public:
        const_iterator(Node* ptr = nullptr) : node_ptr(ptr) {}
        const T& operator*() const { return node_ptr->elem; }
        const T* operator->() const { return &node_ptr->elem; }
        const_iterator& operator++() { node_ptr = node_ptr->next; return *this; }
        const_iterator operator++(int) { const_iterator temp(*this); ++(*this); return temp; }
        bool operator==(const_iterator rhs) const { return node_ptr == rhs.node_ptr; }
        bool operator!=(const_iterator rhs) const { return node_ptr != rhs.node_ptr; }
    };

    // ---------- iterator-based functions ----------

    /// Returns iterator for the front of the list
    iterator begin() { return iterator(head); }

    /// Returns const_iterator for the front of the list
    const_iterator begin() const { return const_iterator(head); }

    /// Returns iterator for the end of the list
    iterator end() {
        return iterator(nullptr);  // fictional position after the last element
    }

    /// Returns const_iterator for the end of the list
    const_iterator end() const {
        return const_iterator(nullptr);  // fictional position after the last element
    }

    /// Inserts new element just after the given position
    /// @param it     iterator defining position
    /// @param elem   element to insert
    /// @return       iterator of newly inserted element
    iterator insert_after(iterator it, const T& elem) {
        it.node_ptr->next = new Node(elem, it.node_ptr->next);
        if (tail == it.node_ptr)  // special case, as newest node becomes tail
            tail = it.node_ptr->next;
        sz++;
        return iterator(it.node_ptr->next);
    }

    /// Removes the element just after the given position
    /// @param it     iterator defining position
    /// @return       iterator of position just beyond the removed element
    iterator erase_after(iterator it) {
        Node* dead = it.node_ptr->next;
        if (tail == dead)  // special case, as old tail is being removed
            tail = it.node_ptr;
        it.node_ptr->next = dead->next;
        delete dead;
        sz--;
        return iterator(it.node_ptr->next);  // return iterator to what newly follows the original iterator
    }

    //------------------------------------------------
    // rule-of-five behaviors
    //------------------------------------------------

  private:
    // presumes valid empty list when called
    void clone(const SinglyLinkedList& other) {
        for (T e : other) push_back(e);        // add each element of other to this list
    }

  public:

    /// non-member function to swap two lists
    friend void swap(SinglyLinkedList& a, SinglyLinkedList& b) {
        std::swap(a.sz, b.sz);
        std::swap(a.head, b.head);
        std::swap(a.tail, b.tail);
    }

    /// resets the list to empty
    void clear() { while (sz > 0) pop_front(); }

    /// copy constructor
    SinglyLinkedList(const SinglyLinkedList& other) { clone(other); }

    /// copy assignment
    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {                     // do nothing for a self-assignment
            clear();
            clone(other);
        }
        return *this;
    }

    /// move constructor
    SinglyLinkedList(SinglyLinkedList&& other) { swap(*this, other); }

    /// move assignment
    SinglyLinkedList& operator=(SinglyLinkedList&& other) {
        if (this != &other) swap(*this, other);   // do nothing for a self-assignment
        return *this;
    }

    /// destructor
    ~SinglyLinkedList() { clear(); }

};

}  // namespace dsac::list
