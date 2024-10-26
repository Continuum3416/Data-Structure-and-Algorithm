#pragma once

#include "abstract_map.h"

namespace dsac::map {

template <typename Key, typename Value, typename Hash>
class AbstractHashMap : public AbstractMap<Key,Value> {
  protected:
    typedef AbstractMap<Key,Value> Base;
    
  public:
    using typename Base::Entry, typename Base::const_iterator, Base::begin, Base::end;
    
  protected:
    Hash hash;                                           // hash function
    int sz{0};                                           // total number of entries
    int table_sz{17};                                    // current number of buckets

    // compute compressed hash function on key k with simple division method
    int get_hash(const Key& k) const { return hash(k) % table_sz; }

    // Change table size and rehash all entries
    void resize(int new_table_size) {
        std::vector<Entry> buffer;                       // temporary copy of all entries
        for (Entry e : *this)
            buffer.push_back(e);
        table_sz = new_table_size;
        create_table();                                  // based on updated capacity
        sz = 0;                                          // will be recomputed while reinserting entries
        for (Entry e : buffer)
            put(e.key(), e.value());                     // reinsert into this map
    }

    //---------- pure virtual functions -----------
    virtual void create_table() = 0;              // creates an empty table having length equal to num_buckets;
    virtual const_iterator bucket_find(int h, const Key& k) const = 0;          // searches for k in bucket h
    virtual const_iterator bucket_put(int h, const Key& k, const Value& v) = 0; // calls put(k,v) on bucket h
    virtual const_iterator bucket_erase(int h, const_iterator loc) = 0;         // calls erase(v) on bucket h
    
  public:
    /// Returns the number of entries in the map
    int size() const { return sz; }

    /// Returns a const_iterator to the entry with a given key, or end() if no such entry exists
    const_iterator find(const Key& k) const { return bucket_find(get_hash(k), k); }

    /// Removes the entry indicated by the given iterator, and returns iterator to next entry in iteration order
    const_iterator erase(const_iterator loc) {
        int h{get_hash(loc->key())};
        return bucket_erase(h, loc);
    }

    /// Associates given key with given value. If key already exists previous value is overwritten.
    /// Returns an iterator to the entry associated with the key
    const_iterator put(const Key& k, const Value& v) {
        const_iterator result{bucket_put(get_hash(k), k, v)};
        if (sz > table_sz / 2)                             // keep load factor <= 0.5
            resize(2 * table_sz - 1);                      // will be pow(2,j) + 1 for some j
        return result;
    }
};

} // namespace dsac::map
