#include <iostream>
#include <utility>
#include <initializer_list>

using namespace std;

// dynamically sized array; a simplified version of std::vector
template <typename T> class Vector {
  private:
    int cap{0};                            // capacity of the array
    int sz{0};                             // number of actual entries
    T* data{nullptr};                      // pointer to array of elements

  public:
    // Constructs an empty vector
    Vector() {}

    Vector(std::initializer_list<T> elements) {
        for (const T& element : elements) {
            push_back(element);  // Add each element to the list
        }
    }

    // Returns the current capacity of the underlying array
    int capacity() const { return cap; }

    // Returns the number of elements stored
    int size() const { return sz; }

    // Tests whether the vector is empty.
    bool empty() const { return sz == 0; }

    // Returns const reference to the element at index i; behavior is undefined if i is out of bounds
    const T& operator[](int i) const { return data[i]; }

    // Returns reference to the element at index i; behavior is undefined if i is out of bounds
    T& operator[](int i) { return data[i]; }

    // Returns const reference to the element at index i; raises out_of_range exception with invalid index
    const T& at(int i) const {
        if (i < 0 || i >= sz) throw out_of_range("Invalid index");
        return data[i];
    }

    // Returns reference to the element at index i; raises out_of_range exception with invalid index
    T& at(int i) {
        if (i < 0 || i >= sz) throw out_of_range("Invalid index");
        return data[i];
    }

    // Returns a const reference to the first element; behavior is undefined if vector is empty
    const T& front() const { return data[0]; }

    // Returns a live reference to the first element; behavior is undefined if vector is empty
    T& front() { return data[0]; }

    // Returns a const reference to the last element. behavior is undefined if vector is empty
    const T& back() const { return data[sz - 1]; }

    // Returns a live reference to the last element; behavior is undefined if vector is empty
    T& back() { return data[sz - 1]; }

    // Inserts an element at end of the vector
    void push_back(const T& elem) {
        if (sz == cap) reserve(max(1, 2 * cap));       // double array size
        data[sz++] = elem;
    }

    // Removes an element from the end of the vector
    void pop_back() { sz--; }

    // Inserts an element at index i; behavior is undefined if i is out of bounds
    void insert(int i, const T& elem) {
        if (sz == cap) reserve(max(1, 2 * cap));       // double array size
        for (int k = sz - 1; k >= i; k--)              // shift subsequent elements upward
            data[k + 1] = move(data[k]);
        data[i] = elem;
        sz++;                                          // there is one more element
    }

    // Removes element at index i; behavior is undefined if i is out of bounds
    void erase(int i) {
        for (int k = i + 1; k < sz; k++)               // shift subsequent elements down
            data[k - 1] = move(data[k]);
        sz--;                                          // there is one less element
    }

    // Requests that the vector capacity be at least as large as the indicated capacity
    void reserve(int minimum) {
        if (cap < minimum) {
            T* temp{new T[minimum]};
            for (int k = 0; k < sz; k++)
                temp[k] = move(data[k]);
            delete[] data;                             // delete old array (if any)
            data = move(temp);                         // begin using new array
            cap = minimum;                             // new capacity
        }
    }

    // support for iterators and rule-of-five in later sections

    void removeElement(const T& elem){
        int i = 0;
        while (i < sz && data[i] != elem) {
            i++;
        }
        
        // If the element is found
        if (i < sz) {
            // Shift subsequent elements to the left by one position
            for (int j = i + 1; j < sz; ++j) {
                data[j - 1] = move(data[j]);
            }
            sz--;
        }
        else
            std::cout << "No such element found" << std::endl;
        return;
    }

    void print(){
        for(int i = 0; i < sz; i++)
            cout << data[i] << " ";
        cout << endl;
        return;
    }
};


int main(){
    Vector <string> A = {"One", "Two"};
    A.insert(0, "Two");
    A.insert(1, "Three");
    A.insert(3, "Four");
    A.print();

    A.erase(0);
    A.removeElement("Two");
    A.removeElement("Four");
    A.insert(1, "Don");
    A.print();


    A.removeElement("four");
    
    // Run: g++ p1.cpp -o p1.exe; ./p1.exe
    return 0;
}