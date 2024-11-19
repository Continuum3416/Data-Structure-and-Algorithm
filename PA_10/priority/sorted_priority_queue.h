#pragma once
#include <functional>    // defines std::less
#include <list>

namespace dsac::priority {

template <typename Entry, typename Compare=std::less<Entry>>
class SortedPriorityQueue {
  protected:
    typename std::list<Entry> data;                       // our underlying collection
    Compare less_than;                                    // less_than(a,b) defines "a < b" relationship

  public:
    SortedPriorityQueue() {}                              // default is an empty priority queue

    /// Returns the current size of the priority queue
    int size() const { return data.size(); }
    
    /// Returns true if the priority queue is empty
    bool empty() const { return data.empty(); }

    /// Inserts a new entry into the priority queue
    void insert(const Entry& e) {
        typename std::list<Entry>::iterator walk{data.begin()};
        while (walk != data.end() && less_than(*walk, e)) // while walk's entry is less than new entry
            ++walk;                                       // advance walk
        data.insert(walk, e);                             // new element goes before walk
    }
    
    /// Returns a constant reference to the minimum entry
    const Entry& min() const {
        return data.front();
    }

    /// Removes the minimum entry
    void remove_min() {
        data.pop_front();
    }
};

} // namespace dsac::priority
