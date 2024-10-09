#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

template <typename T> class MyLinkedDeque {
  private:
    class Node {
      public:
        T elem;                                            // stored element
        Node* prev{nullptr};                               // pointer to previous node
        Node* next{nullptr};                               // pointer to next node

        Node() {}
        Node(const T& element, Node* prv, Node* nxt) : elem{element}, prev{prv}, next{nxt} {}
    };

    int sz{0};                                             // number of actual user entries in list
    Node* header;                                          // sentinel node at beginning of list
    Node* trailer;                                         // sentinel node at end of list

    void create_sentinels() {
        header = new Node();
        trailer = new Node();
        header->next = trailer;
        trailer->prev = header;
    }

        Node* insert_before(T elem, Node* successor) {
        Node* predecessor = successor->prev;
        Node* newest = new Node(elem, predecessor, successor);
        predecessor->next = newest;
        successor->prev = newest;
        sz++;
        return newest;
    }

    void erase(Node* node) {
        Node* predecessor = node->prev;
        Node* successor = node->next;
        delete node;
        predecessor->next = successor;
        successor->prev = predecessor;
        sz--;
    }

  public:
    MyLinkedDeque() { create_sentinels(); }
    int size() const { return sz; }
    bool empty() const { return sz == 0; }
    T& front() { return header->next->elem; }
    T& back() { return trailer->prev->elem; }

    void insert_front(const T& elem) { insert_before(elem, header->next); }
    void insert_rear(const T& elem) { insert_before(elem, trailer); }
    void remove_front() { erase(header->next); }
    void remove_rear() { erase(trailer->prev); }

    void printDueue(){
        Node* top = header->next;
        while(top != trailer){
            cout << top->elem << " ";
            top = top->next;
        }
        cout << endl;
        return;
    }

};

int main(){
    MyLinkedDeque<string> Deque;
    cout << "Adding some elements: " << endl;
    Deque.insert_front("John");
    Deque.insert_front("Jane");
    Deque.insert_rear("Jo");

    cout << "Output: ";
    Deque.printDueue();

    cout << "Removing some elements: " << endl;
    Deque.remove_rear();
    Deque.remove_front();

    cout << "Output: ";
    Deque.printDueue();

    cout << "Size of this deque is " << Deque.size() << endl;
    cout << "The front element is " << Deque.front() << endl;

    // Run: g++ ec2.cpp -o ec2.exe; ./ec2.exe
    return 0;
}