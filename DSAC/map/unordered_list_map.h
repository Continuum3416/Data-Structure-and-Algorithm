#pragma once
#include <list>
#include <stdexcept>
#include "abstract_map.h"

namespace dsac::map {

template <typename Key, typename Value>
class UnorderedListMap : public AbstractMap<Key,Value> {
  private:
    typedef AbstractMap<Key,Value> Base;                     // shorthand for the base class
  public:
    using typename Base::Entry, typename Base::const_iterator, Base::erase;
  private:
    using typename Base::abstract_iter_rep, Base::get_rep;
    typedef std::list<Entry> EntryList;                      // shorthand for list of entries
    typedef typename EntryList::const_iterator LCI;          // shorthand for list's const_iterator

    EntryList storage;                                       // map entries are stored in a list

  protected:
    // position	within our map is described by an iterator in the underlying list
    class iter_rep : public abstract_iter_rep {              // specialize abstract version
      public:
        LCI list_iter{nullptr};
        iter_rep(LCI it) : list_iter(it) {}
        
        const Entry& entry() const { return *list_iter; }
        void advance() { ++list_iter; }
        abstract_iter_rep* clone() const { return new iter_rep(list_iter); }
        bool equals(const abstract_iter_rep* other) const {
            const iter_rep* p = dynamic_cast<const iter_rep*>(other);   // cast abstract argument to our iter_rep
            return p != nullptr && list_iter == p->list_iter;
        }
    };  //------- end of class iter_rep --------
    
  public:
    /// Creates an empty map
    UnorderedListMap() {}

    /// Returns the number of entries in the map
    int size() const { return storage.size(); }

    /// Returns iterator to first entry
    const_iterator begin() const { return const_iterator(new iter_rep(storage.begin())); }

    /// Returns iterator representing the end
    const_iterator end() const { return const_iterator(new iter_rep(storage.end())); }

    /// Returns a iterator to the entry with a given key, or end() if no such entry exists
    const_iterator find(const Key& k) const {
        LCI walk{storage.begin()};
        while (walk != storage.end() && walk->key() != k)
            ++walk;
        return const_iterator(new iter_rep(walk));
    }

    /// Associates given key with given value. If key already exists previous value is overwritten.
    /// Returns an iterator to the entry associated with the key
    const_iterator put(const Key& k, const Value& v) {
        const_iterator loc{find(k)};
        if (loc != end()) {
            this->update_value(*loc,v);                           // overwrite existing value
            return loc;
        } else {                                                  // key is new
            storage.push_back(Entry(k,v));
            return const_iterator(new iter_rep(--storage.end())); // newest entry is last on the list
        }
    }

    /// Removes the entry indicated by the given iterator, and returns iterator to next entry in iteration order
    const_iterator erase(const_iterator loc) {
        LCI list_iter = dynamic_cast<iter_rep*>(get_rep(loc))->list_iter;
        return const_iterator(new iter_rep(storage.erase(list_iter)));
    }
};

} // namespace dsac::map
