/*  Program:    
    Author: Don Le
    Class: CSCI 240
    Date: December 11 2024
    Description: Problem 1
    I certify that the code below is my own work.
    Exception(s): N/A
*/
#include<iostream>
#include<unordered_set>

using namespace std;

template<typename T> class MyDList{
private:
    struct MyDNode{
        T data;
        MyDNode *prev = nullptr;
        MyDNode *next = nullptr;

        MyDNode(){}

        MyDNode(const T& data, MyDNode* prev, MyDNode* next){
            this->data = data;
            this->prev = prev;
            this->next = next;
        }
    };

    int size = 0;
    MyDNode* head = nullptr;
    MyDNode* trailer = nullptr;
    unordered_set<T> unique_set;

    void insertBefore(MyDNode* nextNode, const T& data) {
        MyDNode* previousNode = nextNode->prev;
        MyDNode* newNode = new MyDNode(data, previousNode, nextNode);
        previousNode->next = newNode;
        nextNode->prev = newNode;
        size++;

        unique_set.insert(data);
    }

    void Delete(MyDNode* deleteNode){
        MyDNode* previousNode = deleteNode->prev;
        MyDNode* nextNode = deleteNode->next;
        unique_set.erase(deleteNode->data);
        delete deleteNode;
        previousNode->next = nextNode;
        nextNode->prev = previousNode;
        size--;
    }

public:
    MyDList(){
        head = new MyDNode();
        trailer = new MyDNode();
        head->next = trailer;
        trailer->prev = head;
    }

    int Size(){return size;}
    bool empty(){return (size == 0);}

    // insert before trailer
    void insertRear(const T& data){
        insertBefore(trailer, data);
    }

    // insert before head->next
    void insertFront(const T& data){
        insertBefore(head->next, data);
    }

    void removeFront(){
        if(empty()){
            cout << "List is empty, nothing to remove" << endl;
            return;
        } 
        Delete(head->next);
    }

    void removeRear(){
        if(empty()){
            cout << "List is empty, nothing to remove" << endl;
            return;
        } 
        Delete(trailer->prev);
    }

    void print(){
        MyDNode* current = head->next;
        while(current != trailer){
            cout << current -> data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void removeElem(const T& removeNode){
        MyDNode* current = head->next;

        while (current != trailer && current->data != removeNode) {
            current = current->next;
        }
        if(current == trailer)
            cout << "No element called " << removeNode << " found" << endl;
        else
            deleteBefore(current);
    }

    // Revised instruction:
    void insertElem(const T& elem1, const T& elem2) {
        if (empty()) {
            cout << "List is empty. Inserting at the rear." << endl;
            insertBefore(trailer, elem1);
            return;
        }

        MyDNode* current = head->next;

        while (current != trailer && current->data != elem2) {
            current = current->next;
        }

        // If the element exists, insert before it
        if (current != trailer) {
            cout << elem2 << " found, inserting " << elem1 <<" before " << elem2 << endl;
            insertBefore(current, elem1);
        } 
        else {
            // If element not found, insert at the rear
            cout << "Element not found, inserting " << elem1 << " at the rear" << endl;
            insertBefore(trailer, elem1);
        }
    }


};

void testDrive(){

}

int main(){
    cout << "Author: Don Le" << endl;
    cout << "Test drive with a few integers: " << endl;
    MyDList<int> integerList;
    integerList.insertRear(4);
    integerList.insertRear(3);
    integerList.insertRear(2);
    integerList.insertRear(1);
    integerList.print();


    integerList.removeRear();
    integerList.removeElem(4);
    integerList.print();

    integerList.removeElem(4);

    // Runtime for each operations
    cout << "Running time for insertRear() is O(1)" << endl;
    cout << "Running time for removeRear() is O(1)" << endl;
    cout << "Running time for removeElem() is O(n)" << endl;
    cout << "Running time for empty() is O(1)" << endl;
    cout << "Running time for Size() is O(1)" << endl;
    cout << "Running time for print() is O(n)" << endl;


    cout << "\nString List:" << endl;

    MyDList<string> list;
    cout << "Insert Jane John Kim: " << endl;
    // insert “Jane” to the rear
    list.insertRear("Jane");
    // insert “John” to the rear
    list.insertRear("John");
    // insert “Kim” to the rear
    list.insertRear("Kim");
    // print the list, should be Jane John Kim
    list.print();

    // remove “Tom”
    // remove “John”
    list.removeElem("Tom");
    list.removeElem("John");


    // insert “Bob” before “Kim”
    // remove rear
    // insert “Jo” before “Jon”
    // print the list, should be Jane Bob Jo
    list.insertElem("Bob", "Kim");
    list.removeRear();
    list.insertElem("Jo", "Jon");
    list.print();
    
    // print the size of the list, should be 3
    cout << "Size of the string list: " << list.Size() << endl;


    // Create a MyDList object that holds a list of integers
    cout << "\nInteger List: " << endl;
    MyDList<int> intList;

    // remove rear
    intList.removeRear();

    // insert 5 before 7
    intList.insertElem(5, 7);
    intList.print();

    if(intList.empty()) cout << "List is empty" << endl;
    else cout << "List is not empty" << endl;

    cout << "Running time for removeRear() is O(1)" << endl;
    cout << "Running time for insertElem() is O(n)" << endl;

    // Run: g++ p1.cpp -o p1.exe; ./p1.exe
    return 0;
}