#pragma once
#include <functional>    // defines std::less
#include <stdexcept>
#include <vector>
#include "abstract_map.h"

namespace dsac::map {

template <typename Key, typename Value, typename Compare=std::less<Key>>
class OrderedTableMap : public AbstractMap<Key,Value> {
  protected:
    typedef AbstractMap<Key,Value> Base;                     // shorthand for the base class
  public:
    using typename Base::Entry, typename Base::const_iterator, Base::erase;
  protected:
    using typename Base::abstract_iter_rep, Base::get_rep;

    std::vector<Entry> table;                                // map entries are stored in a vector
    Compare less_than;                                       // less_than(a,b) defines "a < b" relationship

    int lower_bound_index(const Key& target) const {
        int low(0), high(table.size()-1);
        while (low <= high) {
            int mid{(low + high) / 2};
            if (less_than(table[mid].key(), target))         // lower bound must be right of mid
                low = mid + 1;
            else
                high = mid - 1;                              // lower bound is either mid or left of mid
        }
        return low;                                          // lower bound at low (which equals 1+high)
    }
    
    // a position within our map is described by an iterator in the underlying list
    class iter_rep : public abstract_iter_rep {              // specialize abstract version
      public:
        const std::vector<Entry>* vec;
        int index;
        iter_rep(const std::vector<Entry>* v, int i) : vec{v}, index{i} {}

        const Entry& entry() const { return (*vec)[index]; }
        void advance() { ++index; }
        abstract_iter_rep* clone() const { return new iter_rep(vec,index); }
        bool equals(const abstract_iter_rep* other) const {
            const iter_rep* p = dynamic_cast<const iter_rep*>(other);   // cast abstract argument to our iter_rep
            return p != nullptr && vec == p->vec && index == p->index;
        }
    };  //------- end of class iter_rep --------
    
  public:
    /// Creates an empty map
    OrderedTableMap() {}

    /// Returns the number of entries in the map
    int size() const { return table.size(); }

    /// Returns a const_iterator to first entry
    const_iterator begin() const { return const_iterator(new iter_rep(&table, 0)); }

    /// Returns a const_iterator representing the end
    const_iterator end() const { return const_iterator(new iter_rep(&table, table.size())); }

    /// Returns a const_iterator to the entry with a given key, or end() if no such entry exists
    const_iterator find(const Key& k) const {
        int j{lower_bound_index(k)};
        if (j < table.size() && !less_than(k, table[j].key()))            // exact match
            return const_iterator(new iter_rep(&table, j));               // at index j
        else
            return const_iterator(new iter_rep(&table, table.size()));    // unsuccessful search
    }

    /// Associates given key with given value. If key already exists previous value is overwritten.
    /// Returns a const_iterator to the entry associated with the key
    const_iterator put(const Key& k, const Value& v) {
        int j{lower_bound_index(k)};
        if (j < table.size() && !less_than(k, table[j].key()))            // exact match
            this->update_value(table[j],v);                               // overwrite existing value
        else
            table.insert(table.begin() + j, Entry(k,v));                  // insert at index j
        return const_iterator(new iter_rep(&table, j));                   // either way, entry is at index j
    }

    /// Removes the entry indicated by the given iterator, and returns const_iterator to next entry in iteration order
    const_iterator erase(const_iterator loc) {
        int j = dynamic_cast<iter_rep*>(get_rep(loc))->index;
        table.erase(table.begin() + j);
        return const_iterator(new iter_rep(&table, j));
    }

    /// Returns a const_iterator to the first entry with key greater than or equal to k, or end() if no such entry exists
    const_iterator lower_bound(const Key& k) const {
        int j{lower_bound_index(k)};
        return const_iterator(new iter_rep(&table, j));
    }
    
    /// Returns a const_iterator to the first entry with key strictly greater than k, or end() if no such entry exists
    const_iterator upper_bound(const Key& k) const {
        int j{lower_bound_index(k)};
        if (j < table.size() && !less_than(k, table[j].key()))         // exact match
            j++;                                                       // advance past the match
        return const_iterator(new iter_rep(&table, j));
    }
    
};

} // namespace dsac::map
