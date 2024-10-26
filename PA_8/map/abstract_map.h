#pragma once

#include <stdexcept>

namespace dsac::map {

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
        abstract_iter_rep* rep{nullptr};
        
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
        const_iterator it{find(k)};
        if (it == end())
            throw std::out_of_range("key not found");
        return it->value();
    }

    /// Erases entry with given key (if one exists)
    /// Returns true if an entry was removed, false otherwise
    bool erase(const Key& k) {
        const_iterator it{find(k)};
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

} // namespace dsac::map
