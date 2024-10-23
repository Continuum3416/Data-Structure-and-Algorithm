/*  Program: PA6 exercise 1
    Author:  Delong Tang    
    Class:   CSCI 240  
    Date:    10/12/24  
    Description: Using the SortedPriorityQueue class from textbook and test following test case
    I certify that the code below is my own work.
    Exception(s): N/A
*/
#include <iostream>
#include <functional>
#include <list>

using namespace std;

template <typename Entry, typename Compare=less<Entry>>
class SortedPriorityQueue {
  protected:
    list<Entry> data;                            // our underlying collection
    Compare less_than;                                    // less_than(a,b) defines "a < b" relationship

  public:
    SortedPriorityQueue() {}                              // default is an empty priority queue

    int size() const { return data.size(); }              // returns number of entries
    bool empty() const { return data.empty(); }           // returns true if there are no entries
    const Entry& min() const { return data.front(); }     // returns constant reference to minimum entry
    void remove_min() { data.pop_front(); }               // removes the minimum entry

    // Inserts a new entry into the priority queue
    void insert(const Entry& e) {
        typename list<Entry>::iterator walk{data.begin()};
        while (walk != data.end() && less_than(*walk, e)) // while walk's entry is less than new entry
            ++walk;                                       // advance walk
        data.insert(walk, e);                             // new element goes before walk
    }
};

int main(int argc, char const *argv[])
{
    cout << "Author: [Your Name]" << endl;
    /* code */

    //default ascending sorted list
    SortedPriorityQueue<int, less<int>> queue; 
    //Case1:
    queue.insert(5);
    queue.insert(4);
    queue.insert(7);
    queue.insert(1);
    cout << "Min value of the queue list: ";
    cout << queue.min() << endl;

    //Case2:
    queue.remove_min();
    queue.insert(3);
    queue.insert(6);
    cout << "Min value of the queue list: ";
    cout << queue.min() << endl;
    //Case3:
    queue.remove_min();
    cout << "Min value of the queue list: ";
    cout << queue.min() << endl;
    //Case4:
    queue.remove_min();
    queue.insert(8);
    cout << "Min value of the queue list: ";
    cout << queue.min() << endl;
    //Case5:
    queue.remove_min();
    queue.insert(2);
    cout << "Min value of the queue list: ";
    cout << queue.min() << endl;

    //Case6:
    queue.remove_min();
    cout << "Min value of the queue list: ";
    cout << queue.min() << endl;
    queue.remove_min();

    // g++ p1.cpp -o p1.exe; ./p1.exe

    return 0;
}
