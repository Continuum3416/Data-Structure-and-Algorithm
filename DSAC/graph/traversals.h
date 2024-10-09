#pragma once

#include "graph.h"

namespace dsac::graph {

/// Performs DFS of the undiscovered portion of Graph g starting at Vertex u
///    
/// discovered maps each vertex to the discovery vertex used to reach it in DFS
/// root of a search tree is canonically marked with itself as the discovery vertex    
template <typename V, typename E>    
void dfs(const Graph<V,E>& g, typename Graph<V,E>::Vertex u, VertexVertexMap<V,E>& discovered) {
    if (discovered.count(u) == 0)
        discovered[u] = u;                             // we conventionally mark a tree root as its own parent
    for (auto v : g.neighbors(u)) {                    // for every outgoing neighbor of u
        if (discovered.count(v) == 0) {                // v is undiscovered
            discovered[v] = u;                         // u is the parent of v in the tree
            dfs(g, v, discovered);                     // recursively explore from v
        }
    }
}

/// Performs DFS of an entire graph, returning the discovery map
template <typename V, typename E>    
VertexVertexMap<V,E> dfs_complete(const Graph<V,E>& g) {
    VertexVertexMap<V,E> discovered;
    for (auto u : g.vertices())
        if (discovered.count(u) == 0)
            dfs(g, u, discovered);                           // (re)start the DFS process at u
    return discovered;
}

/// Performs BFS of the undiscovered portion of Graph g starting at Vertex s
///    
/// discovered maps each vertex to the discovery vertex used to reach it in DFS
/// root of a search tree is canonically marked with itself as the discovery vertex    
template <typename V, typename E>    
void bfs(const Graph<V,E>& g, typename Graph<V,E>::Vertex s, VertexVertexMap<V,E>& discovered) {
    VertexList<V,E> level;
    level.push_back(s);                                 // first level includes only s
    while (!level.empty()) {
        VertexList<V,E> next_level;                     // prepare to gather newly discovered vertices
        for (auto u : level) {                          // for every u in the previous level
            for (auto v : g.neighbors(u)) {             // for every outgoing neighbor of u
                if (discovered.count(v) == 0) {         // v was previously undiscovered
                    discovered[v] = u;                  // mark v as discovered via u
                    next_level.push_back(v);            // v will be further considered in next pass
                }
            }
        }
        swap(level, next_level);                         // continue by exploring 'next' level
    }
}

/// Returns list of vertices on directed path from u to v (or empty list if v not reachable)
/// based upon the discovery map from a previous graph traversal    
template <typename V, typename E>    
VertexList<V,E> construct_path(const Graph<V,E>& g,
                               typename Graph<V,E>::Vertex u,
                               typename Graph<V,E>::Vertex v,
                               const VertexVertexMap<V,E>& discovered) {
    VertexList<V,E> path;
    if (discovered.count(v) == 1) {             // v was discovered during the search
        typename Graph<V,E>::Vertex walk = v;   // we reverse engineer the path used to reach v
        path.push_back(v);
        while (walk != u) {
            walk = discovered.at(walk);
            path.push_front(walk);
        }
    }
    return path;
}
 
} // namespace dsac::graph
