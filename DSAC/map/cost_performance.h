#pragma once
#include <list>
#include <stdexcept>
#include <utility>
#include "ordered_table_map.h"

namespace dsac::map {

template <typename OrderedMap = OrderedTableMap<int,int>>
class CostPerformanceDatabase {
  public:
    typedef typename OrderedMap::const_iterator const_iterator;
    
  private:
    OrderedMap database;           // initially empty
    
  public:
    const_iterator begin() const { return database.begin(); }
    const_iterator end() const { return database.end(); }
    
    // Returns iterator to (cost,performance) entry with largest cost not exceeding c, or end() if no such entry
    const_iterator best(int c) const {
        const_iterator here{database.upper_bound(c)};                     // least key strictly greater than c
        if (here == begin())                                              // there are no keys less than or equal to c
            return end();
        return --here;                                                    // otherwise this has greatest key less than or equal to c
    }

    void add(int c, int p) {
        const_iterator existing{best(c)};                                 // existing costs no more than c
        if (existing != end() and existing->value() >= p)                 // if its performance is as good,
            return;                                                       // (c,p) is dominated, so ignore it
        const_iterator newest = database.put(c,p);                        // else, add (c,p) to database
        // and now remove any old entries that are dominated by the new one
        const_iterator old{newest};
        ++old;                                                            // old is more expensive than c
        while (old != end() && old->value() <= p)                         // if not better performance
            old = database.erase(old);                                    // remove the old entry
    }
};

} // namespace dsac::map
