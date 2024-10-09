#pragma once
#include <list>
#include <utility>

namespace dsac::list {

/// Maintains a list of elements ordered according to access frequency.
template <typename T>
class FavoritesList {

  protected:
    // setup some convenient shorthands
    typedef typename std::list<std::pair<int,T>>::iterator iterator;
    typedef typename std::list<std::pair<int,T>>::const_iterator const_iterator;
    
    std::list<std::pair<int,T>> contents;                                  // initially empty

    iterator find(T elem) {
        iterator walk{contents.begin()};
        while (walk != contents.end() && walk->second != elem)
            ++walk;
        return walk;
    }

  public:
    /// Returns number of distinct elements in the list
    int size() const { return contents.size(); }

    /// Returns true if the list is non-empty
    bool empty() const { return contents.empty(); }

    /// Accessess element (possibly new), increasing its access count
    void access(T elem) {
        iterator p{find(elem)};                                            // try to locate existing element
        if (p == contents.end())
            contents.push_back({1,elem});                                  // add entry for new element to end
        else {
            int count{++(p->first)};                                       // increment count for existing element
            iterator walk{p};                                              // used to walk toward beginning of list
            iterator peek{walk};                                           // used to peek just before walk
            while (walk != contents.begin() && (--peek)->first < count)    // while element before walk has smaller count
                --walk;                                                    // move walk one spot earlier
            if (walk != p) {                      
                contents.insert(walk, *p);                                 // reinsert just before walk
                contents.erase(p);                                         // and remove original entry
            }
        }
    }

    /// Removes the given element from the list of favorites (if found)
    void remove(T elem) {
        iterator p{find(elem)};                                            // try to locate existing element
        if (p != contents.end())
            contents.erase(p);
    }

    /// Returns an ordered list of the k most frequently accessed elements
    std::list<T> get_favorites(int k) const {
        const_iterator walk{contents.begin()};
        std::list<T> result;
        while (walk != contents.end() and result.size() < k) {
            result.push_back(walk->second);                                // add original element to the results
            ++walk;
        }
        return result;
    }
  
};  //----------- end of FavoritesList class -----------
  
}  // namespace dsac::list
