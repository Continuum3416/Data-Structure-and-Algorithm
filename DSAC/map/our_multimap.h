#pragma once

#include <list>
#include <map>

namespace dsac::map {

template <typename Key, typename Value>
class OurMultimap {
  private:
    typedef std::pair<const Key,Value> Entry;
    typedef std::list<Entry> Secondary;
    typedef std::map<Key, Secondary> Primary;
    typedef typename Primary::iterator PI;
    typedef typename Primary::const_iterator PCI;

    Primary primary;    // initially empty
    int sz{0};
    
  public:
    int size() const { return sz; }
    bool empty() const { return sz == 0; }

    int count(const Key& k) const {
        PCI pi = primary.find(k);
        if (pi == primary.end())
            return 0;
        else
            return pi->second.size();
    }

    void insert(const Entry& e) {
        PI pi = primary.find(e.first);
        if (pi == primary.end())
            pi = primary.insert({e.first,Secondary()}).first;    // make new empty list for key
        pi->second.push_front(e);
        sz++;
    }        

    int erase(const Key& k) {
        PI pi = primary.find(k);
        if (pi == primary.end())
            return 0;
        else {
            int removed = pi->second.size();
            sz -= removed;
            primary.erase(pi);
            return removed;
        }
    }
};
    
} // namespace dsac::map
