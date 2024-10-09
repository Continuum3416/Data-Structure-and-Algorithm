#pragma once
#include "favorites_list.h"
#include <algorithm>


namespace dsac::list {

/// Maintains a list of elements ordered using move-to-front heuristic
template <typename T>
class FavoritesListMTF : public FavoritesList<T> {
    using FavoritesList<T>::contents, FavoritesList<T>::find;
    using typename FavoritesList<T>::iterator;
    
  public:
    /// Accessess element (possibly new), increasing its access count
    void access(T elem) {
        iterator p{find(elem)};                                // try to locate existing element
        if (p == contents.end())
            contents.push_front({1,elem});                     // insert new entry at front
        else {
            p->first++;                                        // increment count of existing element
            if (p != contents.begin()) {
                contents.push_front(*p);                       // reinsert at front of list
                contents.erase(p);                             // and remove the original entry
            }
        }
    }

    /// Returns an ordered list of the k most frequently accessed elements
    std::list<T> get_favorites(int k) const {
        std::list<T> results;
        std::list<std::pair<int,T>> temp{contents};            // copy of the official list
        for (int j = 0; j < k; j++) {
            iterator big;
            big = std::max_element(temp.begin(), temp.end());  // from <algorithm>
            results.push_back(big->second);
            temp.erase(big);
        }
        return results;
    }
};  //----------- end of FavoritesListMTF class -----------

}  // namespace dsac::list
