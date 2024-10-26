#pragma once

#include <stdexcept>
#include<vector>
#include <list>
#include <stdexcept>
#include <functional>               // defines std::hash
#include <utility>                  // defines std::pair, std::make_pair
#include <vector>

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
        Value& value() { return v; }               // allow value to be changed
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
        abstract_iter_rep* rep{ nullptr };

    public:
        const Entry& operator*() const { return rep->entry(); }
        const Entry* operator->() const { return &rep->entry(); }
        const_iterator& operator++() { rep->advance(); return *this; }
        const_iterator operator++(int) { const_iterator temp{ *this }; rep->advance(); return temp; }
        bool operator==(const const_iterator& other) const { return rep->equals(other.rep); }
        bool operator!=(const const_iterator& other) const { return !rep->equals(other.rep); }

        const_iterator(abstract_iter_rep* r = nullptr) : rep{ r } {}
        const_iterator(const const_iterator& other) : rep{ other.rep->clone() } {}
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
    abstract_iter_rep* get_rep(const_iterator iter) const { return iter.rep; }
    void update_value(const Entry& e, const Value& v) {
        const_cast<Entry&>(e).v = v;
    }

public:
    //---------- concrete functions -----------

    /// Returns true if the map is empty, false otherwise
    bool empty() const { return size() == 0; }

    /// Returns true if the map contains an entry with the given key
    bool contains(const Key& k) const {
        return find(k) != end();
    }

    /// Returns a reference to the value associated with given key,
    /// or throws out_of_range exception if key not found
    const Value& at(const Key& k) const {
        const_iterator it{ find(k) };
        if (it == end())
            throw std::out_of_range("key not found");
        return it->value();
    }

    /// Erases entry with given key (if one exists)
    /// Returns true if an entry was removed, false otherwise
    bool erase(const Key& k) {
        const_iterator it{ find(k) };
        if (it == end())
            return false;
        erase(it);
        return true;
    }

    virtual ~AbstractMap() {}

    //---------- pure virtual functions -----------
    virtual int size() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator find(const Key& k) const = 0;
    virtual const_iterator put(const Key& k, const Value& v) = 0;
    virtual const_iterator erase(const_iterator loc) = 0;
};



template <typename Key, typename Value, typename Hash>
class AbstractHashMap : public AbstractMap<Key, Value> {
protected:
    typedef AbstractMap<Key, Value> Base;

public:
    using typename Base::Entry, typename Base::const_iterator, Base::begin, Base::end;

protected:
    Hash hash;                                           // hash function
    int sz{ 0 };                                           // total number of entries
    int table_sz{ 17 };                                    // current number of buckets

    // compute compressed hash function on key k with simple division method
    int get_hash(const Key& k) const { return hash(k) % table_sz; }

public:
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

protected:
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
        int h{ get_hash(loc->key()) };
        return bucket_erase(h, loc);
    }

    /// Associates given key with given value. If key already exists previous value is overwritten.
    /// Returns an iterator to the entry associated with the key
    const_iterator put(const Key& k, const Value& v) {
        const_iterator result{ bucket_put(get_hash(k), k, v) };
        if (sz > table_sz / 2)                             // keep load factor <= 0.5
            resize(2 * table_sz - 1);                      // will be pow(2,j) + 1 for some j
        return result;
    }
};








template <typename Key, typename Value>
class UnorderedListMap : public AbstractMap<Key, Value> {
private:
    typedef AbstractMap<Key, Value> Base;                     // shorthand for the base class
public:
    using typename Base::Entry, typename Base::const_iterator, Base::erase;
private:
    using typename Base::abstract_iter_rep, Base::get_rep;
    typedef std::list<Entry> EntryList;                      // shorthand for list of entries
    typedef typename EntryList::const_iterator LCI;          // shorthand for list's const_iterator

    EntryList storage;                                       // map entries are stored in a list

protected:
    // position	within our map is described by an iterator in the underlying list
    class iter_rep : public Base::abstract_iter_rep {              // specialize abstract version
    public:
        LCI list_iter{ nullptr };
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
        LCI walk{ storage.begin() };
        while (walk != storage.end() && walk->key() != k)
            ++walk;
        return const_iterator(new iter_rep(walk));
    }

    /// Associates given key with given value. If key already exists previous value is overwritten.
    /// Returns an iterator to the entry associated with the key
    const_iterator put(const Key& k, const Value& v) {
        const_iterator loc{ find(k) };
        if (loc != end()) {
            this->update_value(*loc, v);                           // overwrite existing value
            return loc;
        }
        else {                                                  // key is new
            storage.push_back(Entry(k, v));
            return const_iterator(new iter_rep(--storage.end())); // newest entry is last on the list
        }
    }

    /// Removes the entry indicated by the given iterator, and returns iterator to next entry in iteration order
    const_iterator erase(const_iterator loc) {
        LCI list_iter = dynamic_cast<iter_rep*>(Base::get_rep(loc))->list_iter;
        return const_iterator(new iter_rep(storage.erase(list_iter)));
    }
};


template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ChainHashMap : public AbstractHashMap<Key, Value, Hash> {
protected:
    typedef AbstractHashMap<Key, Value, Hash> Base;
public:
    using typename Base::Entry;                                  // make nested Entry public
protected:
    using typename Base::abstract_iter_rep, Base::get_rep, Base::table_sz, Base::sz;

    typedef UnorderedListMap<Key, Value>  Bucket;                 // each bucket will be a simple map
    typedef typename Bucket::const_iterator BCI;                 // bucket const_iterator

    std::vector<Bucket> table;


    void create_table() {
        table.clear();
        table.resize(Base::table_sz);                                  // fills with empty buckets
    }

    class iter_rep : public Base::abstract_iter_rep {                  // specialize abstract version
    public:
        const std::vector<Bucket>* tbl{ nullptr };                 // need table to advance
        int bkt_num{ 0 };                                          // which bucket in table?
        BCI bkt_iter;                                            // which location within that bucket?
        iter_rep(const std::vector<Bucket>* t, int b, BCI it) : tbl{ t }, bkt_num{ b }, bkt_iter{ it } {}

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
    using AbstractMap<Key, Value>::erase;                               // makes the key-based version accessible
    using typename AbstractMap<Key, Value>::const_iterator;

    /// Creates an empty map
    ChainHashMap() { create_table(); }                                 // initializes table of buckets

    ChainHashMap(int initial_size) {
        Base::table_sz = initial_size; // Set the table size
        create_table(); // Create the initial table
    }

    bool has_key(const Key& k) const {
        return this->find(k) != this->end();
    }




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
        BCI here{ table[h].find(k) };
        if (here != table[h].end())                                    // found it!
            return const_iterator(new iter_rep(&table, h, here));
        else
            return end();
    }

    const_iterator bucket_put(int h, const Key& k, const Value& v) {  // calls put(k,v) on bucket h
        int old_size{ table[h].size() };
        BCI result{ table[h].put(k,v) };
        Base::sz += (table[h].size() - old_size);                            // one more if new key
        return const_iterator(new iter_rep(&table, h, result));
    }

    const_iterator bucket_erase(int h, const_iterator loc) {           // calls erase(loc) on bucket h
        const_iterator next{ loc };
        ++next;                                                        // precompute next location
        table[h].erase(dynamic_cast<iter_rep*>(Base::get_rep(loc))->bkt_iter);
        Base::sz--;
        return next;
    }
};

