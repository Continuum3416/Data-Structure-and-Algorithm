#pragma once

#include "graph.h"
#include "priority/heap_adaptable_priority_queue.h"

#include <limits>            // std::numeric_limits<int>::max
#include <utility>           // std::pair

namespace dsac::graph {

/// Computes shortest-path distances from src to reachable vertices of g.
///    
/// Graph can be undirected or directed but must have nonnegative edge weights
template <typename V, typename E>    
VertexIntMap<V,E> shortest_path_distances(const Graph<V,E>& g, typename Graph<V,E>::Vertex src) {
    typedef dsac::priority::HeapAdaptablePriorityQueue<std::pair<int,typename Graph<V,E>::Vertex>> AdaptablePQ;
    typedef VertexMap<V,E,typename AdaptablePQ::Locator> VertexLocatorMap;
    
    VertexIntMap<V,E> D;                                // D[v] is upper bound from s to v
    VertexIntMap<V,E> cloud;                            // map reachable v to its D[v] value
    AdaptablePQ pq;                                     // PQ entry is {D[v],v}
    VertexLocatorMap pqlocator;                         // map from vertex to its pq locator

    // for each vertex v of the graph, add an entry to the priority queue, with
    // the source having distance 0 and all others having infinite distance
    for (auto v : g.vertices()) {
        D[v] = (v == src ? 0 : std::numeric_limits<int>::max());
        pqlocator[v] = pq.insert({D[v], v});
    }

    while (!pq.empty()) {
        auto entry = pq.min();
        pq.remove_min();
        auto u = entry.second;                          // vertex removed from PQ
        cloud[u] = entry.first;                         // save final distance to u
        pqlocator.erase(u);                             // u is no longer in pq
        for (auto e : g.incident_edges(u)) {
            auto v = g.opposite(e,u);
            if (cloud.count(v) == 0) {                  // v not yet finalized
                // perform relaxation step on edge (u,v)
                if (D[u] + e.weight() < D[v]) {         // better path to v?
                    D[v] = D[u] + e.weight();           // update the distance
                    pq.update(pqlocator[v], {D[v],v});  // update pq entry
                }
            }
        }
    }
    return cloud;                                       // only includes reachable vertices
}

/// reconstructs shortest-path tree rooted at vertex src, given computed distance map D
/// Each vertex is mapped to its parent vertex in the tree (with src mapped to itself)    
template <typename V, typename E>    
VertexVertexMap<V,E> shortest_path_tree(const Graph<V,E>& g, typename Graph<V,E>::Vertex src,
                                        const VertexIntMap<V,E>& D) {
    VertexVertexMap<V,E> tree;
    tree[src] = src;
    for (auto entry : D) {
        auto v = entry.first;
        if (v != src)
            for (auto e : g.incident_edges(v, false)) {   // consider INCOMING edges
                auto u = g.opposite(e,v);
                if (D.at(v) == D.at(u) + e.weight())
                    tree[v] = u;                          // v is reached by (u,v)
            }
    }
    return tree;
}


    
} // namespace dsac::graph
