#include<iostream>
#include <initializer_list>

using namespace std;

template <typename T> class DoublyLinkedList {
private:
    //---------------- nested Node class ----------------
    struct Node {
        T elem;                                            // stored element
        Node* prev{nullptr};                               // pointer to previous node
        Node* next{nullptr};                               // pointer to next node

        Node() {}
        Node(const T& element, Node* prv, Node* nxt) : elem{element}, prev{prv}, next{nxt} {}
    };
      //------------ end of nested Node class ------------

    // DoublyLinkedList instance variables
    int sz{0};                                             // number of actual user entries in list
    Node* header;                                          // sentinel node at beginning of list
    Node* trailer;                                         // sentinel node at end of list

    // utility to configure an empty list
    void create_sentinels() {
        header = new Node();
        trailer = new Node();
        header->next = trailer;
        trailer->prev = header;
    }

    Node* getNode(int index) const {
        // pointer current
        Node* current = header;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;    // Move to the next node
        }
        return current;
    }

public:
    DoublyLinkedList() { create_sentinels(); }             // Constructs an empty list

    DoublyLinkedList(std::initializer_list<T> elements) {
        create_sentinels();
        for (const T& element : elements) {
            push_back(element);  // Add each element to the list
        }
    }

    // ---------- access functions ----------
    int size() const { return sz; }                        // Returns the number of elements stored
    bool empty() const { return sz == 0; }                 // Tests whether the list is empty.
    T& front() { return header->next->elem; }              // Live reference to the first element
    const T& front() const { return header->next->elem; }  // Const reference to the first element
    T& back() { return trailer->prev->elem; }              // Live reference to the last element
    const T& back() const { return trailer->prev->elem; }  // Const reference to the last element

private:
    // ---------- private update functions ----------

    // Inserts new element immediately before the given node and returns pointer to the new node
    Node* insert_before(T elem, Node* successor) {
        Node* predecessor = successor->prev;
        Node* newest = new Node(elem, predecessor, successor);
        predecessor->next = newest;
        successor->prev = newest;
        sz++;
        return newest;
    }

    // Removes the given node from the list
    void erase(Node* node) {
        Node* predecessor = node->prev;
        Node* successor = node->next;
        delete node;
        predecessor->next = successor;                     // relink neighbors of removed node
        successor->prev = predecessor;
        sz--;
    }

  public:
    // ---------- public update functions ----------

    // Inserts element at the beginning of the list (between header and header->next)
    void push_front(const T& elem) { insert_before(elem, header->next); }

    // Inserts element at the end of the list (between trailer->prev and trailer)
    void push_back(const T& elem) { insert_before(elem, trailer); }

    // Removes the first element of the list
    void pop_front() { erase(header->next); }

    // Removes the last element of the list
    void pop_back() { erase(trailer->prev); }

    T find_middle() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        Node* left = header->next;  // points to first node with data
        Node* right = header->next;

        while (right != trailer && right->next != trailer) {
            left = left->next;          // Move left one node
            right = right->next->next;  // Move right two nodes
        }

        if (right == trailer) {
            return left->prev->elem; // Return the previous node if right reached trailer
        }

        return left->elem; 
    }

    // Function to get a node by index for testing purposes
    Node* getNodeByIndex(int index) {
        Node* current = header;
        int count = 0;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }
        return current;
    }

    void deleteNode(const T& value) {
        // Start from the first real node (after header)
        Node* current = header->next;
        
        // Traverse the list to find the node with the matching value
        while (current != trailer) {
            if (current->elem == value) {
                // Node found, delete it
                erase(current);
                return;  // Exit after deletion
            }
            current = current->next;
        }
        // If the value is not found, simply return
    }

    void printList() {
        Node* temp = header->next;
        while (temp != nullptr && temp->next != nullptr) {
            std::cout << temp->elem<< " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

};  //----------- end of DoublyLinkedList class -----------


int main(){
    DoublyLinkedList<int> list1 = {1, 2, 3, 4, 5, 6};
    cout << list1.find_middle() << endl;

    DoublyLinkedList<int> list2 = {1, 2, 3, 4, 5, 6, 7};
    cout << list2.find_middle() << endl;

    list2.deleteNode(5);
    list2.printList();

    // g++ linked_list.cpp -o linked_list.exe; ./linked_list.exe
    return 0;
}