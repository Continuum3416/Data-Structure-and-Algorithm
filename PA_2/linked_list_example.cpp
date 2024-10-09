#include <iostream>
#include <initializer_list>

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

    // Helper function to get a pointer to the node at a specific index
    Node* getNode(int index) const {
        // pointer current
        Node* current = head;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;    // Move to the next node
        }
        return current;
    }

public:
    // default constructor
    SinglyLinkedList() {} 

    // Constructor that accepts std::initializer_list
    SinglyLinkedList(std::initializer_list<T> elements) {
        for (const T& element : elements) {
            push_back(element);  // Add each element to the list
        }
    }

    // Overload the subscript operator for non-const access
    T& operator[](int index) {
        Node* node = getNode(index);
        if (node != nullptr)
            return node->element; // access the element variable in the struct Node
        else
            throw std::out_of_range("Index out of range");
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

    void print_list() const {
        Node* current = head;                           // Start from the head
        while (current != nullptr) {                    // Traverse until the end (nullptr)
            std::cout << current->element << " ";       // Print the current element
            current = current->next;                    // Move to the next node
        }
        std::cout << std::endl;                         // End with a new line
    }

    void remove_at(int pos) {
        // Check if the position is valid
        if (pos < 0 || pos >= size) {
            throw std::out_of_range("Index out of range");
        }

        // Case 1: Removing from the beginning
        if (pos == 0) {
            pop_front(); // Reuse the pop_front method for simplicity
            return;
        }

        // Case 2: Removing from the middle or end
        Node* prev = getNode(pos - 1); // Get the previous node
        Node* to_delete = prev->next;  // The node to be deleted
        prev->next = to_delete->next;  // Skip over the node to be deleted

        if (to_delete == tail) {       // If deleting the tail node
            tail = prev;               // Update the tail pointer
        }

        delete to_delete;              // Free memory
        size--;                        // Decrease the size
    }

    ~SinglyLinkedList() {               // Destructor
        while (!isEmpty()) {
            pop_front(); 
        }
    }
};

int main(){
    SinglyLinkedList<int> list = {1, 2, 3};

    // insert front
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.print_list(); 

    // list.push_front(7);
    // list.push_front(8);
    // list[0] = 2;            // assign the first node to 2
    // cout << list[2] << endl;

    // list.print_list(); 

    // list.remove_at(2);
    // list.print_list();

    // Run: g++ linked_list_example.cpp -o linked_list_example.exe; ./linked_list_example.exe
    return 0;
}