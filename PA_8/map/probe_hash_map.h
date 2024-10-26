#pragma once

#include "abstract_hash_map.h"

#include <algorithm>                // defines std::fill
#include <functional>               // defines std::hash
#include <utility>                  // defines std::pair, std::make_pair
#include <vector>

namespace dsac::map {

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ProbeHashMap : public AbstractHashMap<Key, Value, Hash> {
  protected:
    typedef AbstractHashMap<Key, Value, Hash> Base;
  public:
    using typename Base::Entry;                                  // make nested Entry public
  protected:
    using typename Base::abstract_iter_rep;
    using Base::get_rep, Base::table_sz, Base::sz;

    std::vector<Entry> table;
    std::vector<bool> open;           // open[j] is true if cell j has not yet been used for the map
    std::vector<bool> defunct;        // defunct[j] is true if cell j was previously used/deleted
    
    void create_table() {
        table.resize(table_sz);
        open.resize(table_sz);
        fill(open.begin(), open.end(), true);
        defunct.resize(table_sz);
        fill(defunct.begin(), defunct.end(), false);
    }

    class iter_rep : public abstract_iter_rep {    // specialize abstract version
      public:
        const ProbeHashMap* map{nullptr};
        int loc;                                   // which cell?  (table.size() is end)
        iter_rep(const ProbeHashMap* m, int j) : map{m}, loc{j} {}
        
        const Entry& entry() const { return map->table[loc]; }
        
        abstract_iter_rep* clone() const { return new iter_rep(*this); }
        
        void advance() {
            do {
                ++loc;
            } while (loc < map->table.size() && (map->open[loc] || map->defunct[loc]));
        }
        
        bool equals(const abstract_iter_rep* other) const {
            const iter_rep* p = dynamic_cast<const iter_rep*>(other);
            if (p == nullptr) return false;    // failed cast
            return map == p->map && loc == p->loc;
        }            
    }; // end class iter_rep
    friend iter_rep;             // allow iter_rep access to map's table/open/defunct vectors

  public:
    using AbstractMap<Key,Value>::erase;                         // makes the Key-based version accessible
    using typename AbstractMap<Key,Value>::const_iterator;

    /// Creates an empty map
    ProbeHashMap() { create_table(); }                           // initializes tables
    
    const_iterator begin() const {
        iter_rep* p = new iter_rep(this, -1);                    // artificial -1 location before advance
        p->advance();                                            // advance to first actual entry (or end)
        return const_iterator(p);
    }

    const_iterator end() const {
        return const_iterator(new iter_rep(this, table.size()));
    }
    
  protected:
    // Searches for an entry with key k (which is known to have hash value h),
    // returning the index at which it was found, or returning -(a+1)
    // where a is the index of the first available slot (possibly DEFUNCT)
    // that can be used to store a new entry.
    int find_slot(int h, const Key& k) const {
        int avail{-1};                         // no slot available (thus far)
        int j{h};                              // index while scanning table
        do {
            if (open[j] || defunct[j]) {
                if (avail == -1) avail = j;    // this is the first available slot!
                if (open[j]) break;            // if empty, search fails immediately
            } else if (table[j].key() == k)
                return j;                      // successful match
            j = (j + 1) % table.size();        // keep looking (cyclically)
        } while (j != h);                      // stop if we return to the start
        return -(avail+1);                     // search has failed
    }

    // search for entry with key k in "bucket h"
    const_iterator bucket_find(int h, const Key& k) const {
        int j{find_slot(h, k)};
        if (j < 0)                                               // no match found
            return end();
        return const_iterator(new iter_rep(this, j)); // this key has an existing entry
    }
    
    // add/update Entry(k,v) within "bucket h"
    const_iterator bucket_put(int h, const Key& k, const Value& v)  {
        int j{find_slot(h, k)};
        if (j < 0) {                                             // no match found
            j = -(j+1);                                          // available slot
            sz++;
            table[j] = Entry(k, v);
            open[j] = false;
        } else {                                                 // replace existing value
            this->update_value(table[j], v);
        }
        return const_iterator(new iter_rep(this, j));
    }
    
    // remove existing entry from "bucket h"
    const_iterator bucket_erase(int h, const_iterator loc) {
        (void)h;                                                  // meaningless command to suppress compiler warning
        const_iterator next{loc};
        ++next;                                                   // precompute next location
        int j{dynamic_cast<iter_rep*>(get_rep(loc))->loc};
        defunct[j] = true;
        sz--;
        return next;
    }
};

} // namespace dsac::map
