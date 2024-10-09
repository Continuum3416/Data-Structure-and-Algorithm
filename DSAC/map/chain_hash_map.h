#pragma once

#include "abstract_hash_map.h"
#include "unordered_list_map.h"

#include <functional>               // defines std::hash
#include <utility>                  // defines std::pair, std::make_pair
#include <vector>

namespace dsac::map {

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ChainHashMap : public AbstractHashMap<Key, Value, Hash> {
  protected:
    typedef AbstractHashMap<Key, Value, Hash> Base;
  public:
    using typename Base::Entry;                                  // make nested Entry public
  protected:
    using typename Base::abstract_iter_rep, Base::get_rep, Base::table_sz, Base::sz;
    
    typedef UnorderedListMap<Key,Value>  Bucket;                 // each bucket will be a simple map
    typedef typename Bucket::const_iterator BCI;                 // bucket const_iterator
    
    std::vector<Bucket> table;
    
    void create_table() {
        table.clear();
        table.resize(table_sz);                                  // fills with empty buckets
    }

    class iter_rep : public abstract_iter_rep {                  // specialize abstract version
      public:
        const std::vector<Bucket>* tbl{nullptr};                 // need table to advance
        int bkt_num{0};                                          // which bucket in table?
        BCI bkt_iter;                                            // which location within that bucket?
        iter_rep(const std::vector<Bucket>* t, int b, BCI it) : tbl{t}, bkt_num{b}, bkt_iter{it} {}
        
        const Entry& entry() const { return *bkt_iter; }
        abstract_iter_rep* clone() const { return new iter_rep(*this); }
        
        void advance() {
            ++bkt_iter;                                          // try advancing within current bucket
            while (bkt_iter == (*tbl)[bkt_num].end()) {
                ++bkt_num;                                       // advance one bucket
                if (bkt_num == tbl->size()) break;               // no buckets left
                bkt_iter = (*tbl)[bkt_num].begin();              // start at beginning of bucket
            }
        }
        
        bool equals(const abstract_iter_rep* other) const {
            const iter_rep* p = dynamic_cast<const iter_rep*>(other);  // cast abstract argument to our iter_rep
            if (p == nullptr) return false;    // failed cast
            return tbl == p->tbl && bkt_num == p->bkt_num && bkt_iter == p->bkt_iter;
        }            
    }; // end class iter_rep

  public:
    using AbstractMap<Key,Value>::erase;                               // makes the key-based version accessible
    using typename AbstractMap<Key,Value>::const_iterator;

    /// Creates an empty map
    ChainHashMap() { create_table(); }                                 // initializes table of buckets
    
    const_iterator begin() const {
        iter_rep* p = new iter_rep(&table, 0, table[0].begin());
        if (table[0].empty()) p->advance();                            // advance to first actual entry (or end)
        return const_iterator(p);
    }

    const_iterator end() const {
        return const_iterator(new iter_rep(&table, table.size(), table[table.size() - 1].end()));
    }

  protected:
    const_iterator bucket_find(int h, const Key& k) const {            // searches for k in bucket h
        BCI here{table[h].find(k)};
        if (here != table[h].end())                                    // found it!
            return const_iterator(new iter_rep(&table, h, here));
        else
            return end();
    }

    const_iterator bucket_put(int h, const Key& k, const Value& v)  {  // calls put(k,v) on bucket h
        int old_size{table[h].size()};
        BCI result{table[h].put(k,v)};
        sz += (table[h].size() - old_size);                            // one more if new key
        return const_iterator(new iter_rep(&table, h, result));
    }
    
    const_iterator bucket_erase(int h, const_iterator loc) {           // calls erase(loc) on bucket h
        const_iterator next{loc};
        ++next;                                                        // precompute next location
        table[h].erase(dynamic_cast<iter_rep*>(get_rep(loc))->bkt_iter);
        sz--;
        return next;
    }
};

} // namespace dsac::map
