#pragma once
#include <functional>    // defines std::less
#include <memory>        // defines std::shared_ptr
#include <vector>
#include "heap_priority_queue.h"

namespace dsac::priority {

template <typename Entry, typename Compare=std::less<Entry>>
class HeapAdaptablePriorityQueue {
  private:

    // Wrapper class for the original entry, to include an integer location for tracking
    class TrackedEntry {
      public:
        Entry entry;
        std::shared_ptr<int> location{nullptr};
        TrackedEntry(const Entry& e=Entry(), int loc=-1) : entry{e}, location{std::make_shared<int>(loc)} { }

        friend void swap(TrackedEntry& a, TrackedEntry& b) {
            // in addition to swapping the two data members, the actual location values must be swapped!
            using std::swap;
            swap(a.entry, b.entry);          // swap original entries
            swap(a.location,b.location);     // swap the smart pointers
            swap(*a.location,*b.location);   // swap the location values!!!
        }
    };

    // Wrapper to compare TrackedEntry instances (based on their Entry members)
    class TrackedCompare : public Compare {
      public:
        bool operator()(const TrackedEntry& a, const TrackedEntry& b) {
            return Compare::operator()(a.entry, b.entry);
        }
    };
    
    // Specialization of the original heap class using our TrackedEntry and new functions
    typedef HeapPriorityQueue<TrackedEntry, TrackedCompare> PQ;
    class AdaptablePQ : public PQ {
        using PQ::data, PQ::upheap, PQ::downheap, PQ::parent, PQ::less_than;  // inherited
      
      public:
        /// Restores the heap property by moving the entry at index j upward/downward
        void bubble(int j) {
            if (j > 0 && less_than(data[j], data[parent(j)]))
                upheap(j);
            else
                downheap(j);                          // although it might not need to move
        }

        /// Removes the entry at index j
        void remove(int j) {
            if (j == data.size() - 1)                 // entry is at last position
                data.pop_back();                      // just remove it
            else {
                using std::swap;
                swap(data[j], data[data.size() - 1]); // move entry to last position
                data.pop_back();                      // then remove it
                bubble(j);                            // and fix entry displaced by the swap
            }
        }

        /// Replaces the entry at index j with a new entry
        void update(int j, const Entry& e) {
            data[j].entry = e;
            bubble(j);                                // with new key, may need to move entry
        }
    };

    // The HeapAdaptablePriorityQueue will use an instance of our adapted PQ to store entries.
    AdaptablePQ apq;
    
  public:

    typedef const int* Locator;       // will refer to the shared location of a TrackedEntry

    /// Returns the size of the priority queue
    int size() const { return apq.size(); }

    /// Returns true if the priority queue is empty
    bool empty() const { return apq.empty(); }
    
    /// Returns a reference to the minimum element
    const Entry& min() { return apq.min().entry; }
    
    /// Removes the minimum entry
    void remove_min() { apq.remove_min(); }
    
    /// Inserts an entry and returns a Locator for that entry
    Locator insert(const Entry& e) {
        TrackedEntry wrapper(e, apq.size());     // initial location is at the end of the vector
        apq.insert(wrapper);                     // entry might be moved elsewhere during insertion
        return wrapper.location.get();           // return the tracked location
    }

    /// Removes the tracked entry
    void remove(Locator loc) { apq.remove(*loc); }

    /// Replaces the tracked entry with a new entry
    void update(Locator loc, const Entry& e) { apq.update(*loc, e); }
};

} // namespace dsac::priority
