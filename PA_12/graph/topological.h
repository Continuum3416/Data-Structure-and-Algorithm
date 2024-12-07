#pragma once

#include "graph.h"

namespace dsac::graph {

/// Returns a list of vertices of graph g in topological order
/// If no order is possible, the result will have less than n vertices
template <typename V, typename E>    
VertexList<V,E> topological_sort(const Graph<V,E>& g) {
    VertexList<V,E> topo;                 // list of vertices placed in topological order
    VertexList<V,E> ready;                // list of vertices that have no remaining ocnstraints
    VertexIntMap<V,E> incount;            // keep track of in-degree for each vertex
    for (auto u : g.vertices()) {
        incount[u] = g.degree(u, false);  // second argument requests incoming degree
        if (incount[u] == 0)              // if u has no incoming edges,
            ready.push_back(u);           // it is free of constraints
    }
    while (!ready.empty()) {
        auto u = ready.front();           // vertex u is free of constraints
        ready.pop_front();
        topo.push_back(u);                // add u to the topological order
        for (auto v : g.neighbors(u)) {   // consider each outgoing neighbor of u
            incount[v]--;                 // v has one less constraint without u
            if (incount[v] == 0)
                ready.push_back(v);
        }
    }
    return topo;
}
    
} // namespace dsac::graph
