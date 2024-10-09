#include <iostream>
#include <string>

using namespace std;

struct Node {
    string value;
    Node* next;
};


void insertFront(string);
void insertRear(string);
void removeElem(string);
void printAll();

Node* head = nullptr; // pointer to the first node in the list


int numElems = 0;

int main(){
    insertFront("Jo");
    insertRear("Jane");
    insertFront("John");
    insertRear("Kim");
    cout << "Inserting some elements: " << endl; 
    cout << numElems << " elements inserted" << endl;
    printAll();

    cout << "Remove Jane: " << endl; 
    removeElem("Jane");
    cout << numElems << " elements left" << endl;
    printAll();

    cout << "Remove Bob: " << endl; 
    removeElem("Bob");
    cout << numElems << " elements left" << endl;
    printAll();
    
    // Run: g++ p4_sol_2.cpp -o p4_sol_2.exe; ./p4_sol_2.exe
    return 0;
}

// insert at the front
void insertFront(string element){   // change to Node& head; string element if need to pass head
    Node* new_node = new Node();    // create new node, then assign the new object's address to new_node
    new_node -> value = element;    // initialize value to new element
    new_node -> next = head;        // next is now the current head, link new node to old head
    head = new_node;
    numElems++;
    return;
}

// insert at the end
void insertRear(string element){
    Node* new_node = new Node();
    new_node -> value = element;
    new_node -> next = nullptr;

    if (head == nullptr) {
        // If the list is empty, the new node becomes the head
        head = new_node;
    } 
    else {
        // Traverse the list to find the last node
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        // Insert the new node at the end
        current->next = new_node;
    }
    numElems++;
}

void removeElem(string element){
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
    while(current -> next != nullptr && current->next->value != element){
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
        numElems--;
    }

    return;
}

void printAll(){
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