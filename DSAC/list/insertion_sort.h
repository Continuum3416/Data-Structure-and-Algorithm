#pragma once

#include <iostream>

namespace dsac::list {

template <typename List>
void insertion_sort(List& data) {
    if (data.size() > 1) {                   // otherwise, it is already sorted
        auto boundary{--data.end()};         // position of last element
        while (boundary != data.begin()) {
            auto newest{boundary};
            --newest;                        // position just before the boundary
            auto walk{boundary};             // will look for next entry >= newest (or else end)
            while (walk != data.end() && *walk < *newest)
                ++walk;
            if (walk == boundary) {          // newest is already in correct place
                --boundary;                  // so newest becomes the boundary
            } else {
                data.insert(walk, *newest);  // re-insert newest element before walk
                data.erase(newest);          // and then remove it from original location
            }
        }
    }
}
    

}  // namespace dsac::list
