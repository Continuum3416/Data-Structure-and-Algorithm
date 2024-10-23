#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <string>

using namespace std;

template <typename Key, typename Value>
class AbstractMap {
  public:
    //-------- nested Entry class ---------
    class Entry {
        friend AbstractMap;
      private:
        Key k;
        Value v;

      public:
        Entry(const Key& k = Key(), const Value& v = Value()) : k(k), v(v) {}
        const Key& key() const { return k; }       // read-only access
        const Value& value() const { return v; }   // read-only access
        Value& value() { return v; }               // allow change to value
    };  // end of Entry class

  protected:
    //---------- custom iterator representation ----------
    class abstract_iter_rep {
      public:
        virtual const Entry& entry() const = 0;
        virtual void advance() = 0;
        virtual bool equals(const abstract_iter_rep* other) const = 0;
        virtual abstract_iter_rep* clone() const = 0;
        virtual ~abstract_iter_rep() {}
    }; //------ end of abstract_iter_rep ----------

  public:
    //---------- const_iterator ----------
    class const_iterator {
        friend AbstractMap;

      private:
        abstract_iter_rep* rep{nullptr};      // a pointer to an underlying iterator representation
        
      public:
        const Entry& operator*() const { return rep->entry(); }
        const Entry* operator->() const { return &rep->entry(); }
        const_iterator& operator++() { rep->advance(); return *this; }
        const_iterator operator++(int) { const_iterator temp{*this}; rep->advance(); return temp; }
        bool operator==(const const_iterator& other) const { return rep->equals(other.rep); }
        bool operator!=(const const_iterator& other) const { return !rep->equals(other.rep); }
        
        const_iterator(abstract_iter_rep* r = nullptr) : rep{r} {}
        const_iterator(const const_iterator& other) : rep{other.rep->clone()} {}
        ~const_iterator() { delete rep; }
        const_iterator& operator=(const const_iterator& other) {
            if (this != &other and rep != nullptr) {
                delete rep;
                rep = other.rep->clone();
            }
            return *this;
        }
    }; //------ end of const_iterator ----------
    
  protected:
    // necessary utilities for our inheritance
    abstract_iter_rep* get_rep(const_iterator iter) const { return iter.rep; }
    void update_value(const Entry& e, const Value& v) { const_cast<Entry&>(e).v = v; }

  public:
    //---------- pure virtual functions -----------
    virtual int size() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator find(const Key& k) const = 0;
    virtual const_iterator put(const Key& k, const Value& v) = 0;
    virtual const_iterator erase(const_iterator loc) = 0;

    //---------- concrete functions -----------
    bool empty() const { return size() == 0; }     // Returns true if the map is empty, false otherwise
    bool contains(const Key& k) const { return find(k) != end(); }  // Returns true if map contains key
    
    // Returns the value associated with key k,  or throws out_of_range exception if k not found
    const Value& at(const Key& k) const {
        const_iterator it{find(k)};
        if (it == end())
            throw std::out_of_range("key not found");
        return it->value();
    }

    // Erases entry with given key (if one exists); returns true if entry was removed
    bool erase(const Key& k) {
        const_iterator it{find(k)};
        if (it == end())
            return false;
        erase(it);
        return true;
    }    

    virtual ~AbstractMap() {}                     // expected when declaring other virtual functions
};

template <typename Key, typename Value> class UnorderedListMap : public AbstractMap<Key,Value> {
  private:
    typedef AbstractMap<Key,Value> Base;                           // shorthand for templated base type
  public:
    using typename Base::Entry, typename Base::const_iterator, Base::erase;
  private:
    using typename Base::abstract_iter_rep, Base::get_rep;
    typedef std::list<Entry> EntryList;                            // shorthand for a list of entries
    typedef typename EntryList::const_iterator LCI;                // shorthand for list's const_iterator                                                  

    EntryList storage;                                             // map entries are stored in a list

  protected:
    // position within our map is described by an iterator in the underlying list
    class iter_rep : public abstract_iter_rep {                    // specialize abstract version
      public:
        LCI list_iter{nullptr};                                    // data member
        iter_rep(LCI it) : list_iter(it) {}                        // constructor
        
        const Entry& entry() const { return *list_iter; }
        void advance() { ++list_iter; }
        abstract_iter_rep* clone() const { return new iter_rep(list_iter); }
        bool equals(const abstract_iter_rep* other) const {
            const iter_rep* p = dynamic_cast<const iter_rep*>(other);  // cast abstract argument
            return p != nullptr && list_iter == p->list_iter;
        }
    };  //----- end of class iter_rep -----
    
  public:
    UnorderedListMap() {}                                          // Creates an empty map
    
    int size() const { return storage.size(); }                    // Returns number of map entries

    // Returns iterator to first entry
    const_iterator begin() const { return const_iterator(new iter_rep(storage.begin())); }

    // Returns iterator representing the end
    const_iterator end() const { return const_iterator(new iter_rep(storage.end())); }

    // Returns a iterator to the entry with a given key, or end() if no such entry exists
    const_iterator find(const Key& k) const {
        LCI walk{storage.begin()};
        while (walk != storage.end() && walk->key() != k)
            ++walk;
        return const_iterator(new iter_rep(walk));
    }

    // Associates given key with given value; if key already exists previous value is overwritten
    const_iterator put(const Key& k, const Value& v) {
        const_iterator loc{find(k)};
        if (loc != end()) {
            this->update_value(*loc,v);                            // overwrite existing value
            return loc;
        } else {                                                   // key is new
            storage.push_back(Entry(k,v));
            return const_iterator(new iter_rep(--storage.end()));  // newest entry is last on the list
        }
    }

    // Removes entry referenced by given iterator, and returns iterator to next entry in iteration order
    const_iterator erase(const_iterator loc) {
        LCI list_iter = dynamic_cast<iter_rep*>(get_rep(loc))->list_iter;
        return const_iterator(new iter_rep(storage.erase(list_iter)));
    }
};

#endif