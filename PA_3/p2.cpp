#include <iostream>
#include <initializer_list>
#include <iterator>

using namespace std;

template <typename T> class SinglyLinkedList {
private:
    struct Node{
        T element;      // content of the node
        Node* next;     // a pointer variable that holds the address of the next node in the list

        Node(const T& element, Node* next = nullptr){
            this -> element = element;
            this -> next = next;
        }
    };
    int size = 0;
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    // default constructor
    SinglyLinkedList() {} 

    // Constructor that accepts std::initializer_list
    SinglyLinkedList(std::initializer_list<T> elements) {
        for (const T& element : elements) {
            push_back(element);  // Add each element to the list
        }
    }

    int listSize() const { return size;}
    bool isEmpty() const { return size == 0;}
    T& front() {return head -> element;}
    const T& front() const {return head -> element;}
    T& back() {return tail -> element;}
    const T& back() const {return tail -> element;}

    // insert element at the beginning
    void push_front(const T& element){
        head =  new Node(element, head);
        if(size == 0)
            tail = head;
        size++;
    }

    // insert element at the end
    void push_back(const T& element){
        Node* newest = new Node(element);
        if(size == 0)
            head =  newest;
        else
            tail -> next =  newest;
        tail =  newest;
        size++;
    }

    // Remove the first element of the list
    // Behavior: undefined if list is empty
    void pop_front() {
        Node* old = head;
        head = head -> next; // updates the head pointer to point to the next node in the list
        delete old;
        size--;
        if(size == 0)
            tail = nullptr;
    }

    void pop_back(){
        Node* current = head;
        while (current->next != tail) {
            current = current->next; // Move to the second-to-last node
        }
        // Delete the tail node
        delete tail;
        tail = current; // Update tail to the second-to-last node
        tail->next = nullptr; // Set the new tail's next to nullptr
        size--;
    }


    class iterator {
        friend class SinglyLinkedList; // needed for SinglyLinkedLists's insert_after and erase_after
        
      private:
        Node* node_ptr;  // pointer to a node

      public:
        iterator(Node* ptr = nullptr) : node_ptr(ptr) {}
        T& operator*() const { return node_ptr->element; }
        T* operator->() const { return &node_ptr->element; }
        iterator& operator++() { node_ptr = node_ptr->next; return *this; }        // pre-increment
        iterator operator++(int) { iterator temp(*this); ++(*this); return temp; } // post-increment
        bool operator==(iterator rhs) const { return node_ptr == rhs.node_ptr; }
        bool operator!=(iterator rhs) const { return node_ptr != rhs.node_ptr; }
        iterator& operator+=(int inc) {
            // Move the iterator forward by 'inc' positions
            for (int i = 0; i < inc; ++i) {
                if (node_ptr != nullptr)
                    node_ptr = node_ptr->next;
                else
                    break;  // If node_ptr is nullptr, stop advancing (end of list)
            }
            return *this;  // Return *this to allow chaining
        }
    };

    // const version of iterator
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

    // ---------- Iterator-based functions ----------

    iterator begin() { return iterator(head); }
    const_iterator begin() const { return const_iterator(head); }
    iterator end() { return iterator(nullptr); }
    const_iterator end() const { return const_iterator(nullptr); }

    // Inserts new element just after the given position
    iterator insert_after(iterator it, const T& elem) {
        it.node_ptr->next = new Node(elem, it.node_ptr->next);
        if (tail == it.node_ptr)             // special case, as newest node becomes tail
            tail = it.node_ptr->next;
        size++;
        return iterator(it.node_ptr->next);
    }

    // Inserts new element just before the given position
    iterator insert_before(iterator it, const T& elem) {
        if (it == begin()) {
            push_front(elem);
            return begin();   // Return iterator to the new head (first element)
        }

        // Traverse the list to find the node before 'it'
        Node* prev = head;
        while (prev->next != it.node_ptr) {
            prev = prev->next;
        }

        // Insert the new node between 'prev' and 'it.node_ptr'
        prev->next = new Node(elem, it.node_ptr);
        size++;

        return iterator(prev->next); 
    }

    // Removes the element just after the given position
    iterator erase_after(iterator it) {
        Node* dead = it.node_ptr->next;
        if (tail == dead)                    // special case, as old tail is being removed
            tail = it.node_ptr;
        it.node_ptr->next = dead->next;
        delete dead;
        size--;
        return iterator(it.node_ptr->next);  // return iterator to what newly follows the original iterator
    }

    // Removes the element just before the given position
    iterator erase_before(iterator it) {
        if(it == begin()){
            std::cout << "No element to delete before this node" << std::endl;
            return it;
        }
        
        if(it == begin() + 1){
            pop_front();
            return it;
        }

        Node* prev = head;
        while(prev->next != it.node_ptr){
            prev = prev->next;
        }

        Node* node_to_delete = prev -> next;
        prev -> next = node_to_delete -> next;
        delete node_to_delete;
        size--;

        return it;
    }

};

template <typename S> 
void print(SinglyLinkedList<S>& list){
    typename SinglyLinkedList<S>::iterator it;
    for (it = list.begin(); it != list.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main () {
    SinglyLinkedList<string> list;

    cout << "Add some elements: " << endl;
    list.push_front("Two");
    list.push_back("Three");
    list.push_front("One");
    list.push_back("Four");
    cout << list.listSize() << " elements inserted" << endl;
    print(list);

    // access nested class notation
    SinglyLinkedList<string>::iterator it = list.begin(); // 0
    it += 2;

    cout << "\nInsert before interator " << &it << ": " << endl; 
    list.insert_before(it, "Don");
    print(list);

    cout << "\nRemove front and back: " << endl;
    list.pop_front();
    list.pop_back();
    print(list);

    // Run: g++ p2.cpp -o p2.exe; ./p2.exe
    return 0;
}