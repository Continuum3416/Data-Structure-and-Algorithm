#pragma once
#include <functional>    // defines std::less
#include <vector>

namespace dsac::priority {

template <typename Entry, typename Compare=std::less<Entry>>
class HeapPriorityQueue {
  protected:
    typename std::vector<Entry> data;                      // our underlying collection
    Compare less_than;                                     // less_than(a,b) defines "a < b" relationship

    int parent(int j) { return (j-1) / 2; }                // truncating division
    int left(int j) { return 2 * j + 1; }
    int right(int j) { return 2 * j + 2; }
    bool has_left(int j) { return left(j) < data.size(); }
    bool has_right(int j) { return right(j) < data.size(); }
    
    /// Moves the entry at index j higher, if necessary, to restore the heap property
    void upheap(int j) {
        while (j > 0) {                                    // continue to root (or break statement)
            int p{parent(j)};
            if (less_than(data[j], data[p])) {             // if j's entry is less than its parent
                using std::swap;
                swap(data[j], data[p]);
                j = p;                                     // continue from new location after the swap
            } else
                break;
        }
    }
    
    /// Moves the entry at index j lower, if necessary, to restore the heap property
    void downheap(int j) {
        while (has_left(j)) {                              // continue to bottom (or break statement)
            int small_child{left(j)};                      // although right may be smaller
            if (has_right(j)) {
                if (less_than(data[right(j)], data[left(j)]))
                    small_child = right(j);
            }
            
            if (less_than(data[small_child], data[j])) {   // if small child's entry is less than j's
                using std::swap;
                swap(data[j], data[small_child]);
                j = small_child;                           // continue from new location after the swap
            } else
                break;
        }
    }

    void heapify() {
        int start{parent(data.size()-1)};                  // start at PARENT of last entry
        for (int j = start; j >= 0; j--)                   // loop until processing the root
            downheap(j);
    }
        
  public:
    /// Creates an empty priority queue
    HeapPriorityQueue() {}

    /// Creates a priority queue populated with the given entries
    HeapPriorityQueue(const std::vector<Entry>& contents) : data(contents) { heapify(); }
    
    /// Returns the current size of the priority queue
    int size() const { return data.size(); }
    
    /// Returns true if the priority queue is empty
    bool empty() const { return data.empty(); }

    /// Returns a constant reference to the minimum entry
    const Entry& min() const {
        return data.front();
    }

    /// Inserts a new entry into the priority queue
    void insert(const Entry& e) {
        data.push_back(e);                                 // add to the end of the vector
        upheap(data.size() - 1);                           // upheap newly added entry
    }
    
    /// Removes the minimum entry
    void remove_min() {
        using std::swap;
        swap(data[0], data[data.size() - 1]);              // put last entry at the root
        data.pop_back();                                   // and remove the displaced minimum
        downheap(0);                                       // fix heap property for new root
    }
};

} // namespace dsac::priority
