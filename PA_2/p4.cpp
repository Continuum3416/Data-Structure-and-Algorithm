#include <iostream>
#include <string>

using namespace std;

struct Node {
    string value;
    Node* next;
    int size = 0;

    Node(){size++;}
    ~Node(){size--;}
};


void insertFront(Node* &, Node* &, string);
void insertRear(Node* &, Node* &, string);
void removeElem(Node* &, string);
void printAll(Node* &);
void removeFront(Node* &head, Node* tail);


int main(){
    Node* head = nullptr;
    Node* tail = nullptr;
    insertFront(head, tail, "Jo");
    insertRear(head, tail, "Jane");
    insertFront(head, tail, "John");
    insertRear(head, tail, "Kim");
    

    cout << "Inserting some elements: " << endl; 
    printAll(head);

    cout << "Delete the first element: " << endl;
    removeFront(head, tail);
    printAll(head);

    cout << "Remove Jane: "; 
    removeElem(head, "Jane");
    printAll(head);

    cout << "Remove Bob: "; 
    removeElem(head, "Bob");
    printAll(head);
    
    // Run: g++ p4.cpp -o p4.exe; ./p4.exe
    return 0;
}

// insert at the front
void insertFront(Node* &head, Node* &tail, string element){ // change to Node& head; string element if need to pass head
    Node* new_node = new Node();
    new_node -> value = element;
    new_node -> next = head;        // next is now the current head, link new node to old head
    head = new_node;

    // if list is empty, set tail to new node
    if(tail == nullptr)
        tail = new_node;
    
    return;
}

// insert at the end
void insertRear(Node* &head, Node* &tail, string element){
    Node* new_node = new Node();
    new_node -> value = element;
    new_node -> next = nullptr;

    if(tail != nullptr)
        tail -> next = new_node;
    tail = new_node;

    if(head == nullptr)
        head = new_node;
    return;
}

void removeFront(Node* &head, Node* tail){
    if (head == nullptr) { // Empty list
        return;
    }
    if (head == tail) { // Only one element in the list
        delete head;
        head = tail = nullptr;
        return;
    }
    Node* current_node = head;
    head = head->next;
    delete current_node;

}

void removeRear(Node* head, Node* tail){
    if (head == nullptr) { // Empty list
        return;
    }
    
    if (head == tail) { // Only one element in the list
        delete head;
        head = tail = nullptr;
        return;
    }
    Node* second_to_last = head;
    while (second_to_last->next != tail) {
        second_to_last = second_to_last->next;
    }

    delete tail;
    tail = second_to_last;
    tail->next = nullptr;
}

void removeElem(Node* &head, string element){
    if(head == nullptr){
        cout << "Nothing to remove" << endl;
        return;
    } 

    // if element is in the first node
    if(head -> value == element){
        Node* temp = head;  // Store the old head
        head = head->next;  // Move head to the next node
        delete temp;        // Delete the old head
        return;
    }

    Node* current = head;
    // transverse from left to right 
    // find the node before the target node
    // current->next is a pointer to the node that comes immediately after current
    // current->next->value:
    // This accesses the value (or element, depending on your naming) of the node that follows current.
    Node* next_node = current->next;
    while(current -> next != nullptr && next_node->value != element){
        current = current->next;
    }

    if(current->next == nullptr){
        cout << "No such element called " << element << endl;
    }
    else {
        cout << "Removed " << element << " successfully" << endl;
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    return;
}

void printAll(Node* &head){
    Node* current = head;
    static int count = 1;
    cout << ((count == 1)? "List: " : "Updated List: ");
    cout << "head -> ";
    while(current != nullptr){
        cout << current -> value << " --> ";
        current = current -> next;
    }
    cout << "null pointer" << endl << endl; 
    count++;
    return;
}