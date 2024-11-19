#pragma once
#include <functional>    // defines std::less
#include <list>
#include "unsorted_priority_queue.h"

namespace dsac::priority {

template <typename Entry, typename Compare=std::less<Entry>>
class UnsortedAdaptablePriorityQueue {
    
  private:
    typedef typename std::list<Entry>::iterator iterator;
    
    class AdaptablePQ : public UnsortedPriorityQueue<Entry, Compare> {
      public:
        /// Removes the entry at give location
        void remove(iterator loc) { this->data.erase(loc); }

        /// Replaces the entry at given location with a new entry
        void update(iterator loc, const Entry& e) { *loc = e; }

        /// Return iterator to the last entry of the list
        iterator last_inserted() { return --(this->data.end()); }
    };

    // The UnsortedAdaptablePriorityQueue will use an instance of our AdaptablePQ to store entries.
    AdaptablePQ apq;
    
  public:
    class Locator {
      private:
        friend class UnsortedAdaptablePriorityQueue;
        iterator location;
        Locator(iterator loc) : location{loc} {}
      public:
        Locator() {}
    };

    /// Returns the size of the priority queue
    int size() const { return apq.size(); }

    /// Returns true if the priority queue is empty
    bool empty() const { return apq.empty(); }
    
    /// Returns a reference to the minimum element
    const Entry& min() { return apq.min(); }
    
    /// Removes the minimum entry
    void remove_min() { apq.remove_min(); }
    
    /// Inserts an entry and returns a Locator for that entry
    Locator insert(const Entry& e) {
        apq.insert(e);
        return Locator{apq.last_inserted()};   // return the tracked location
    }

    /// Removes the tracked entry
    void remove(Locator t) { apq.remove(t.location); }

    /// Replaces the tracked entry with a new entry
    void update(Locator t, const Entry& e) { apq.update(t.location, e); }
};

} // namespace dsac::priority
