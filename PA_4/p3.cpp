#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

template<typename T> class MyLinkedQueue{
private:
    //---------------- nested Node class ----------------
    struct Node {
        T elem;                                            // stored element
        Node* prev{nullptr};
        Node* next{nullptr};

        Node() {}
        Node(const T& element, Node* prv, Node* nxt) : elem{element}, prev{prv}, next{nxt} {}
    }; 

    // DoublyLinkedList instance variables
    int sz{0};
    Node* header;
    Node* trailer;

    // utility to configure an empty list
    void create_sentinels() {
        header = new Node();
        trailer = new Node();
        header->next = trailer;
        trailer->prev = header;
    }

public:
    MyLinkedQueue() { create_sentinels(); }

    int size() const { return sz; }                        // Returns the number of elements stored
    bool empty() const { return sz == 0; }                 // Tests whether the list is empty.
    T& front() { return header->next->elem; }              // Live reference to the first element
    T& back() { return trailer->prev->elem; }              // Live reference to the last element

private:
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
        predecessor->next = successor;
        successor->prev = predecessor;
        sz--;
    }

public:
    // ---------- public update functions ----------

    void enqueue(const T& elem) { insert_before(elem, trailer); }

    // remove first element
    T dequeue() {
        T current = header->next->elem;
        erase(header->next); 
        return current;
    }

    void printQueue(){
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
    srand(time(0));

    vector<int> test = {2, 1, 2, 1, 1};

    MyLinkedQueue<pair<int, int>> queue;  // Pair of <jobNum, processingUnits>

    for (int i = 1; i <= 5; ++i) {
        int processingUnits = rand() % 6 + 1; // rand() % 6 + 1
        queue.enqueue({i, processingUnits});
        cout << "Enqueue job " << i << " with " << processingUnits<< " units\n";
    }

    int cycle = 1;

    while (!queue.empty()) {
        pair<int, int> currentJob = queue.dequeue();
        int jobNum = currentJob.first;              // pair[0]
        int processingUnits = currentJob.second;    // pair[1]
        
        cout << cycle << " Processing job " << jobNum << endl;
        processingUnits--;  // Serve 1 unit of the job

        if (processingUnits > 0) {
            queue.enqueue({jobNum, processingUnits});  // Re-enqueue the job if units remain
        } 
        else {
            cout << "Done with job " << jobNum << endl;
        }

        cycle++;
    }

    cout << "Done with all jobs\n";
    // Run: g++ p3.cpp -o p3.exe; ./p3.exe
    return 0;
}