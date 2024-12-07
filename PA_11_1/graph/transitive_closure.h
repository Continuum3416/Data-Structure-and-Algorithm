#pragma once

#include "graph.h"

namespace dsac::graph {

/// Returns a new graph that is the transitive closure of g
template <typename V, typename E>    
Graph<V,E> floyd_warshall(const Graph<V,E>& g) {
    Graph<V,E> closure{g};                        // start with a fresh copy of the graph
    for (auto k : closure.vertices())
        for (auto i : closure.vertices())
            // only continue with i if edge (i,k) exists in closure
            if (closure.has_edge(i,k))
                for (auto j : closure.vertices())
                    // if (k,j) also exists, then add (i,j)
                    if (i != j && closure.has_edge(k,j) && !closure.has_edge(i,j))
                        closure.insert_edge(i,j);
    return closure;
}
    
} // namespace dsac::graph
