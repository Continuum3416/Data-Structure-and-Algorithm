#pragma once
#include <vector>

namespace dsac::priority {


template <typename Entry, typename PriorityQueue>
void pq_sort(std::vector<Entry>& data) {
    PriorityQueue pq;
    // insert all entries into the priority queue
    for (int j=0; j < data.size(); j++)
        pq.insert(data[j]);
    // retrieve all entries from smallest to largest
    for (int j=0; j < data.size(); j++) {
        data[j] = pq.min();
        pq.remove_min();
    }
}

} // namespace dsac::priority
