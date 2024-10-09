#pragma once

#include <utility>     // provides std::swap

namespace dsac::list {

/// doubly linked list, akin to std::list
template <typename T>
class DoublyLinkedList {
  private:
    //---------------- nested Node class ----------------
    class Node {
      public:
        T elem;                           // stored element
        Node* prev{nullptr};              // pointer to previous node
        Node* next{nullptr};              // pointer to next node

        Node() {}
        Node(const T& element, Node* prv, Node* nxt) : elem{element}, prev{prv}, next{nxt} {}
    };  //------------ end of nested Node class ------------

    // DoublyLinkedList instance variables
    int sz{0};                            // number of actual user entries in list
    Node* header;                         // sentinel node at beginning of list
    Node* trailer;                        // sentinel node at end of list

    // utility to configure an empty list
    void create_sentinels() {
        header = new Node();
        trailer = new Node();
        header->next = trailer;
        trailer->prev = header;
    }

  public:
    /// Constructs an empty list
    DoublyLinkedList() { create_sentinels(); }

    // ---------- access functions ----------

    /// Returns the number of elements stored
    /// @return the number of elements stored
    int size() const { return sz; }

    /// Tests whether the list is empty.
    /// @return true if the list is empty, false otherwise
    bool empty() const { return sz == 0; }

    /// Returns live reference to the first element of the list; behavior undefined if list is empty
    /// @return reference to first element of the list
    T& front() { return header->next->elem; }

    /// Returns const reference to the first element of the list; behavior undefined if list is empty
    /// @return reference to first element of the list
    const T& front() const { return header->next->elem; }

    /// Returns live reference to the last element of the list; behavior undefined if list is empty
    /// @return reference to last element of the list
    T& back() { return trailer->prev->elem; }

    /// Returns const reference to the last element of the list; behavior undefined if list is empty
    /// @return reference to last element of the list
    const T& back() const { return trailer->prev->elem; }

  private:
    // ---------- private update functions ----------

    /// Inserts new element immediately before the given node and returns pointer to the new node
    /// @param successor   node just before the location where the new node is inserted
    /// @return pointer to the newly created node
    Node* insert_before(T elem, Node* successor) {
        Node* predecessor = successor->prev;
        Node* newest = new Node(elem, predecessor, successor);
        predecessor->next = newest;
        successor->prev = newest;
        sz++;
        return newest;
    }

    /// Removes the given node from the list
    /// @param node    the node to be removed (must not be a sentinel)
    void erase(Node* node) {
        Node* predecessor = node->prev;
        Node* successor = node->next;
        predecessor->next = successor;              // relink neighbors of removed node
        successor->prev = predecessor;
        delete node;
        sz--;
    }

  public:
    // ---------- public update functions ----------

    /// Inserts element at the beginning of the list
    /// @param elem   the new element
    void push_front(const T& elem) {
        insert_before(elem, header->next);    // place between header and header->next
    }

    /// Inserts element at the end of the list
    /// @param elem   the new element
    void push_back(const T& elem) {
        insert_before(elem, trailer);         // place between trailer->prev and trailer
    }

    /// Removes the first element of the list
    void pop_front() { erase(header->next); }

    /// Removes the last element of the list
    void pop_back() { erase(trailer->prev); }

    //-------------------------------------------------------
    // A bidirectional iterator
    //-------------------------------------------------------
    class iterator {
        friend class DoublyLinkedList;  // needed for DoublyLinkedList's insert and erase

      private:
        Node* node_ptr;  // pointer to a node

      public:
        iterator(Node* ptr = nullptr) : node_ptr(ptr) {}
        T& operator*() const { return node_ptr->elem; }
        T* operator->() const { return &node_ptr->elem; }
        iterator& operator++() { node_ptr = node_ptr->next; return *this; }
        iterator operator++(int) { iterator temp(*this); ++(*this); return temp; }
        iterator& operator--() { node_ptr = node_ptr->prev; return *this; }
        iterator operator--(int) { iterator temp(*this); ++(*this); return temp; }
        bool operator==(const iterator& other) const { return node_ptr == other.node_ptr; }
        bool operator!=(const iterator& other) const { return node_ptr != other.node_ptr; }
    };

    //-------------------------------------------------------
    // const version of iterator
    //-------------------------------------------------------
    class const_iterator {
      private:
        const Node* node_ptr;  // pointer to a node

      public:
        const_iterator(const Node* ptr = nullptr) : node_ptr(ptr) {}
        const T& operator*() const { return node_ptr->elem; }
        const T* operator->() const { return &node_ptr->elem; }
        const_iterator& operator++() { node_ptr = node_ptr->next; return *this; }
        const_iterator operator++(int) { const_iterator temp(*this); ++(*this); return temp; }
        const_iterator& operator--() { node_ptr = node_ptr->prev; return *this; }
        const_iterator operator--(int) { const_iterator temp(*this); ++(*this); return temp; }
        bool operator==(const const_iterator& other) const { return node_ptr == other.node_ptr; }
        bool operator!=(const const_iterator& other) const { return node_ptr != other.node_ptr; }
    };

    // ---------- iterator-based functions ----------

    /// Returns iterator for the front of the list
    iterator begin() {
        return iterator(header->next);        // node AFTER the header stores the front element (if any)
    }

    /// Returns const_iterator for the front of the list
    const_iterator begin() const {
        return const_iterator(header->next);  // node AFTER the header stores the front element (if any)
    }

    /// Returns iterator for the end of the list
    iterator end() {
        return iterator(trailer);              // trailer serves as the end sentinel
    }

    /// Returns const_iterator for the end of the list
    const_iterator end() const {
        return const_iterator(trailer);        // trailer serves as the end sentinel
    }

    /// Inserts new element immediately before the given position and returns iterator to new element
    /// @param it     iterator defining position
    /// @param elem   element to insert
    /// @return       iterator of newly inserted element
    iterator insert(iterator it, const T& elem) {
        Node* node = it.node_ptr;
        return iterator(insert_before(elem, node));    // call the private node-based insert-before
    }

    /// Removes the element at the given position
    /// @param it     iterator defining position
    /// @return       iterator of position just beyond the removed element
    iterator erase(iterator it) {
        erase((it++).node_ptr);   // call the private node-based erase function
        return it;                // note the post-increment during previous command
    }

    //------------------------------------------------
    // rule-of-five behaviors
    //------------------------------------------------

  private:
    // presumes valid empty list when called
    void clone(const DoublyLinkedList& other) {
        for (T e : other)
            push_back(e);
    }

  public:
    /// non-member function to swap two lists
    friend void swap(DoublyLinkedList& a, DoublyLinkedList& b) {
        std::swap(a.sz, b.sz);
        std::swap(a.header, b.header);
        std::swap(a.trailer, b.trailer);
    }
    
    /// resets the list to empty
    void clear() {
        while (sz > 0) pop_front();
    }

    /// copy constructor
    DoublyLinkedList(const DoublyLinkedList& other) {
        create_sentinels();                           // establish as an empty list
        clone(other);                                 // then copy other
    }

    /// copy assignment
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {                         // do nothing for self-assignment
            clear();                                  // reset to an empty list
            clone(other);                             // then copy other
        }
        return *this;
    }

    /// move constructor
    DoublyLinkedList(DoublyLinkedList&& other) {
        create_sentinels();                          // establish as an empty list
        swap(*this, other);                          // then trade states with other
    }

    /// move assignment
    DoublyLinkedList& operator=(DoublyLinkedList&& other) {
        if (this != &other) { swap(*this, other); }  // do nothing for self-assignment
        return *this;
    }

    /// default destructor
    ~DoublyLinkedList() {
        clear();              // this leaves list with size zero, but sentinels exist
        delete header;
        delete trailer;
    }
};  //----------- end of DoublyLinkedList class -----------

}  // namespace dsac::list
