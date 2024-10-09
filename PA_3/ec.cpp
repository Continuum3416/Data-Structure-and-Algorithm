#include <iostream>
#include <list>
#include <string>

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

    bool isAtBeginning(){
        return cursor -> prev == header;
    }

    bool isAtEnd(){
        return cursor == trailer;
    }

    void move_left(){
        if(!isAtBeginning()){
            cursor = cursor->prev;
        }
    }

    void move_right() {
        if (!isAtEnd()) {
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
    string input;
    int option = 1;
    cout << "Enter a starting string: "; std::getline(std::cin, input);
    TextEditor editor(input);

    cout << "Editing document . . ." << endl;
    cout << "\t Editing Menu" << endl;

    cout << " 1. Left\n 2. Right\n 3. Insert character\n 4. Remove character\n 5. Move to beginning\n 6. Move to the end\n 7. Display text\n 8. Quit\n";
    
    bool continue_ = true;
    cout << "Your string: " << input << endl;
    while(continue_){
        cout << "Enter an option: "; cin >> option;
        switch(option){
            case 1: 
                cout << ((editor.isAtBeginning())? "Cursor is at the beginning (ignore)." : "Moved cursor left.") << endl;
                editor.move_left(); break;
            case 2: 
                cout << ((editor.isAtEnd()) ? "Cursor is at the end (ignore)." : "Moved cursor right.") << endl;
                editor.move_right(); break;
            case 3: 
                char c;
                cout << "Enter a character: "; cin >> c;
                editor.insert(c); 
                break;
            case 4:
                cout << "Removed a character" << endl;
                editor.remove();
                break;
            case 5:
                cout << "Moved cursor to beginning" << endl;
                editor.first();
                break;
            case 6:
                cout << "Moved cursor to end" << endl;
                editor.last();
                break;
            case 7:
                cout << "Length: " << editor.size() << endl;
                break;
            case 8:
                cout << "Thanks for using my editor program." << endl;
                continue_ = false;
                break;
            default:
                cout << "Unknown option" << endl;
                break;
        }
        cout << "String: "; editor.display(); cout << endl;

    }
    
    // hHello Word
    // 7 2 1 3 5 1 2 4 7 6 7 8
    // Run: g++ ec.cpp -o ec.exe; ./ec.exe
    return 0;
}