#pragma once

#include "graph.h"
#include "partition.h"
#include "priority/heap_adaptable_priority_queue.h"

#include <algorithm>
#include <limits>            // std::numeric_limits<int>::max
#include <vector>
#include <utility>           // std::pair

namespace dsac::graph {

/// Computes a minimum spanning tree of graph g with the Prim-Jarnik algorithm
///
/// Graph should be connected and have nonnegative edge weights.
template <typename V, typename E>    
EdgeList<V,E> mst_prim_jarnik(const Graph<V,E>& g) {
    typedef dsac::priority::HeapAdaptablePriorityQueue<std::tuple<int,typename Graph<V,E>::Vertex,typename Graph<V,E>::Vertex>> AdaptablePQ;
    typedef VertexMap<V,E,typename AdaptablePQ::Locator> VertexLocatorMap;
    
    VertexIntMap<V,E> D;                                // D[v] is upper bound from s to v
    EdgeList<V,E> tree;                                 // list of edges in spanning tree
    AdaptablePQ pq;                                     // u's entry is {w(nbr,u),u,nbr} reaching u
    VertexLocatorMap pqlocator;                         // map from vertex to its pq locator

    // for each vertex v of the graph, add an entry to the priority queue, with
    // the source having distance 0 and all others having infinite distance
    typename Graph<V,E>::Vertex dummy,src;
    src = g.vertices().front();
    for (auto u : g.vertices()) {
        D[u] = (u == src ? 0 : std::numeric_limits<int>::max());
        pqlocator[u] = pq.insert({D[u], u, dummy});
    }

    while (!pq.empty()) {
        int d;
        typename Graph<V,E>::Vertex u,nbr;
        std::tie(d,u,nbr) = pq.min();                     // unpack tuple from pq
        pq.remove_min();
        pqlocator.erase(u);                               // u's entry is no longer in pq
        if (nbr != dummy)
            tree.push_back(g.get_edge(nbr,u));            // edge (nbr,u) added to tree
        for (auto e : g.incident_edges(u)) {
            auto v = g.opposite(e,u);
            if (pqlocator.count(v) > 0) {                 // v still in PQ
                if (e.weight() < D[v]) {                  // better edge to v?
                    D[v] = e.weight();                    // update the distance
                    pq.update(pqlocator[v], {D[v],v,u});  // update pq entry
                }
            }
        }
    }
    return tree;
}


/// Computes a minimum spanning tree of graph g with Kruskal's algorithm
///
/// Graph should be connected and have nonnegative edge weights.
template <typename V, typename E>
EdgeList<V,E> mst_kruskal(const Graph<V,E>& g) {
    EdgeList<V,E> tree;

    // sort edges by non-decreasing weights
    std::vector<std::pair<int,typename Graph<V,E>::Edge>> edges;
    for (auto e : g.edges())
        edges.push_back({e.weight(),e});
    std::sort(edges.begin(), edges.end());

    // create the Partition structure with each vertex in its own cluster
    typedef Partition<typename Graph<V,E>::Vertex> Partition;
    Partition forest;
    VertexMap<V,E,typename Partition::Position> tokens;
    for (auto v : g.vertices())
        tokens[v] = forest.make_cluster(v);
    
    for (auto e : edges) {
        auto p = g.endpoints(e.second);
        typename Partition::Position a = forest.find(tokens[p.first]);
        typename Partition::Position b = forest.find(tokens[p.second]);
        if (a != b) {
            tree.push_back(e.second);
            forest.combine(a,b);
            if (tree.size() == g.num_vertices() - 1) break;  // MST is complete
        }
    }

    return tree;
}

    
    
    
} // namespace dsac::graph
