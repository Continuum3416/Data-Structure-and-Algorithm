#pragma once
#include <functional>    // defines std::less
#include <list>

namespace dsac::priority {

template <typename Entry, typename Compare=std::less<Entry>>
class UnsortedPriorityQueue {
  protected:
    typename std::list<Entry> data;                   // our underlying collection
    Compare less_than;                                // less_than(a,b) defines "a < b" relationship

  public:
    UnsortedPriorityQueue() {}                        // default is an empty priority queue

    /// Returns the current size of the priority queue
    int size() const { return data.size(); }
    
    /// Returns true if the priority queue is empty
    bool empty() const { return data.empty(); }

    /// Inserts a new entry into the priority queue
    void insert(const Entry& e) { data.push_back(e); }
    
    /// Returns a constant reference to the minimum entry
    const Entry& min() const { return *find_min(); }  // returns the found element

    /// Removes the minimum entry
    void remove_min() { data.erase(find_min()); }     // removes the found element
    
  private:
    typedef typename std::list<Entry>::const_iterator const_iterator;  // convenient shorthand
    
    // utility to locate the minimum entry
    const_iterator find_min() const {
        const_iterator small{data.begin()};
        const_iterator walk{++data.begin()};
        while (walk != data.end()) {
            if (less_than(*walk, *small))             // walk's entry is "less than" small's entry
                small = walk;
            ++walk;
        }
        return small;
    }
    
};

} // namespace dsac::priority
