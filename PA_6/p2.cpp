/*  Program: PA6 exercise 2
    Author:  Delong Tang
    Class:   CSCI 240
    Date:    10/12/24 
    Description: Using SortedPriorityQueue class from the exercise 1 sorted the two files in 
                descending order, then test following test case
    I certify that the code below is my own work.
    Exception(s): N/A
*/
#include <iostream>
#include <functional>
#include <list>
#include<fstream>
#include<ctime>

using namespace std;

template <typename Entry, typename Compare=less<Entry>>
class SortedPriorityQueue {
  protected:
    list<Entry> data;                                     // our underlying collection
    Compare less_than;                                 // less_than(a,b) defines "a < b" relationship

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

    void printfirstfive(){
        list<int>::iterator it = data.begin();
        for (int i = 0; i < 5 && it != data.end(); ++i, ++it) {
            std::cout << *it << " ";
        }
    }

    void printlastfive(){
        list<int>::iterator it = data.end();
        --it;
        int inver_array[5];
        for (int i = 0; i < 5 ; ++i) {
           inver_array[i] = *it;
            --it;
        }

        for(int j = 4; j >=0; j--){
            cout << inver_array[j] <<" ";
        }
        cout << endl;
    }

};


int main(int argc, char const *argv[])
{
    cout << "Author: [Your Name]" << endl;
    //Test case 1
    //Sorted in descending order
    SortedPriorityQueue<int, greater<int>> queue;

    clock_t start = clock();
    ifstream inputfile("small1k.txt");
    int value;
    while(inputfile >> value){
        queue.insert(value);
    }

    cout << "For smallk.txt file: " << endl;
    cout << "First 5 values of the list: ";
    queue.printfirstfive();
    cout << endl;

    cout << "Last 5 values of the list: ";
    queue.printlastfive();

    clock_t end = clock();
    double time1 = double(end - start) * 1000 / CLOCKS_PER_SEC;
    cout << "Running time: " << time1 << " ms" << endl;

    cout << endl << endl;


    //Test case2 
    SortedPriorityQueue<int, greater<int>> queue2;
    clock_t start2 = clock();
    ifstream inputfile2("large100k.txt");
    int value2;
    while(inputfile2 >> value2){
        queue2.insert(value2);
    }
    cout << "For large100k.txt file: " <<endl;
    cout << "First 5 values of the list: ";
    queue2.printfirstfive();
    cout << endl;

    cout << "Last 5 values of the list: ";
    queue2.printlastfive();
    clock_t end2 = clock();

    double time2 = double(end2 - start2) * 1000 / CLOCKS_PER_SEC;
    cout << "Running time: " << time2 << " ms" << endl;

    // g++ p2.cpp -o p2.exe; ./p2.exe

    return 0;
}
