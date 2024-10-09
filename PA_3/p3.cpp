#include <iostream>
#include <list>

using namespace std;

// template <typename T>
class TextEditor{
private:
    //---------------- nested Node class ----------------
    struct Node {
        char elem;                                            // stored element
        Node* prev{nullptr};                               // pointer to previous node
        Node* next{nullptr};                               // pointer to next node

        Node() {}
        Node(const char& element, Node* prv, Node* nxt) : elem{element}, prev{prv}, next{nxt} {}
    };  //------------ end of nested Node class ------------

    // DoublyLinkedList instance variables
    int sz{0};                                             // number of actual user entries in list
    Node* header;                                          // sentinel node at beginning of list
    Node* trailer;                                         // sentinel node at end of list
    Node* cursor;
    bool endCursor = true;

    // utility to configure an empty list
    void create_sentinels() {
        header = new Node();
        trailer = new Node();
        header->next = trailer;
        trailer->prev = header;
    }

public:
    TextEditor(const std::string& str = "") { 
        create_sentinels(); 
        for(char c: str){
            push_back(c);
        }
        cursor = (endCursor)? trailer : header -> next; // replace with header  -> next for cursor at beginning
    }             

    // ---------- access functions ----------
    int size() const { return sz; }                        // Returns the number of elements stored
    bool empty() const { return sz == 0; }                 // Tests whether the list is empty.
    char& front() { return header->next->elem; }              // Live reference to the first element
    const char& front() const { return header->next->elem; }  // Const reference to the first element
    char& back() { return trailer->prev->elem; }              // Live reference to the last element
    const char& back() const { return trailer->prev->elem; }  // Const reference to the last element

private:
    // ---------- private update functions ----------

    // Inserts new element immediately before the given node and returns pointer to the new node
    Node* insert_before(char elem, Node* successor) {
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
    void push_front(const char& elem) { insert_before(elem, header->next); }
    void push_back(const char& elem) { insert_before(elem, trailer); }
    void pop_front() { erase(header->next); }
    void pop_back() { erase(trailer->prev); }

    void display(){
        Node* current = header -> next;
        while(current != trailer) {
            if(current == cursor)
                cout << "|";
            cout << current->elem;
            current = current->next;
        }
        if(current == cursor)
            cout << "|";
        cout << endl;
    }

    void move_left(){
        if(cursor -> prev != header){
            cursor = cursor->prev;
        }
    }

    void move_right() {
        if (cursor != trailer) {
            cursor = cursor->next;
        }
    }

    void insert(char c){
        if(isalpha(c) || c == ' '){
            cursor = insert_before(c, cursor);
            move_right();
        }
        else
            cout << "Character inserted must be a letter" << endl;
    }

    void remove(){
        if(cursor -> prev != header){
            erase(cursor -> prev);
        }
    }

    // move cursor to first element
    void first(){
        cursor = header -> next;
    }

    // move cursor to end
    void last(){
        cursor = trailer;
    }
};



int main () {
    cout << "Initial string: \n";
    TextEditor editor("hHello Word");
    editor.display();

    cout << "\nMove cursor right (nothing happens): \n";
    editor.move_right();
    editor.display();

    cout << "\nMove cursor left: \n";
    editor.move_left();
    editor.display();

    cout << "\nInsert l: \n";
    editor.insert('l'); 
    editor.display(); 

    cout << "\nMove cursor to beginning: \n";
    editor.first();   // Move cursor to the beginning
    editor.display(); 

    cout << "\nMove cursor left (nothing happens): \n";
    editor.move_left();    
    editor.display(); 

    cout << "\nMove cursor right: \n";
    editor.move_right();   
    editor.display(); 

    cout << "\nRemove character before cursor: \n";
    editor.remove();  // Remove character just before cursor
    editor.display(); 

    cout << "\nMove cursor to the end: \n";
    editor.last();   
    editor.display(); 


    // Run: g++ p3.cpp -o p3.exe; ./p3.exe
    return 0;
}