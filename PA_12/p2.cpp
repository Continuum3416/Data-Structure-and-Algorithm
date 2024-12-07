#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <limits> 
#include "graph/adjacency_list_graph.h"
#include "graph/partition.h"
#include "priority/heap_adaptable_priority_queue.h"

using namespace std;
using namespace dsac::graph;


template <typename V, typename E>    
EdgeList_ALG<V,E> mst_prim_jarnik(const AdjacencyListGraph<V,E>& g) {
    typedef dsac::priority::HeapAdaptablePriorityQueue<std::tuple<int,typename AdjacencyListGraph<V,E>::Vertex,typename AdjacencyListGraph<V,E>::Vertex>> AdaptablePQ;
    typedef VertexMap_ALG<V,E,typename AdaptablePQ::Locator> VertexLocatorMap;
    
    VertexIntMap_ALG<V,E> D;                                // D[v] is upper bound from s to v
    EdgeList_ALG<V,E> tree;                                 // list of edges in spanning tree
    AdaptablePQ pq;                                     // u's entry is {w(nbr,u),u,nbr} reaching u
    VertexLocatorMap pqlocator;                         // map from vertex to its pq locator

    // for each vertex v of the graph, add an entry to the priority queue, with
    // the source having distance 0 and all others having infinite distance
    typename AdjacencyListGraph<V,E>::Vertex dummy,src;
    src = g.vertices().front();
    for (auto u : g.vertices()) {
        D[u] = (u == src ? 0 : std::numeric_limits<int>::max());
        pqlocator[u] = pq.insert({D[u], u, dummy});
    }

    while (!pq.empty()) {
        int d;
        typename AdjacencyListGraph<V,E>::Vertex u,nbr;
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


template <typename V, typename E>
EdgeList_ALG<V,E> mst_kruskal(const AdjacencyListGraph<V,E>& g) {
    EdgeList_ALG<V,E> tree;

    // sort edges by non-decreasing weights
    std::vector<std::pair<int,typename AdjacencyListGraph<V,E>::Edge>> edges;
    for (auto e : g.edges())
        edges.push_back({e.weight(),e});
    std::sort(edges.begin(), edges.end());

    // create the Partition structure with each vertex in its own cluster
    typedef Partition<typename AdjacencyListGraph<V,E>::Vertex> Partition;
    Partition forest;
    VertexMap_ALG<V,E,typename Partition::Position> tokens;
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


void printTree(EdgeList_ALG<string, int> discovered, AdjacencyListGraph<string, int> Graph){
    // Print tree
    int total_cost = 0;
    for (auto it = discovered.begin(); it != discovered.end(); it++) {
        auto edge = *it;
        auto [source, destination] = Graph.endpoints(edge);
        total_cost += edge.weight() ;
        cout << "(" << *source << ", " << *destination << ", " << edge.weight() << ") ";
    }
    cout << "Total cost: " << total_cost <<endl;
}

int main() {
    AdjacencyListGraph<string, int> Graph(false);

    // Add vertices
    auto A = Graph.insert_vertex("A");
    auto B = Graph.insert_vertex("B");
    auto C = Graph.insert_vertex("C");
    auto D = Graph.insert_vertex("D");
    auto E = Graph.insert_vertex("E");



    // Add undirected edges
    Graph.insert_edge(A, B, 3);
    Graph.insert_edge(A, C, 4);
    Graph.insert_edge(A, D, 5);
    Graph.insert_edge(A, E, 5);
    Graph.insert_edge(B, C, 4);
    Graph.insert_edge(C, D, 2);
    Graph.insert_edge(D, E, 5);
    Graph.insert_edge(C, E, 3);

    std::cout << "Prim-Jarnik:\n";
    EdgeList_ALG<string, int> mst_prim_tree = mst_prim_jarnik(Graph);
    printTree(mst_prim_tree, Graph);



    std::cout << "Kruskal:\n";
    EdgeList_ALG<string, int> mst_kruskal_tree = mst_kruskal(Graph);
    printTree(mst_kruskal_tree, Graph);



    // Run: g++ p2.cpp -o p2.exe; ./p2.exe
    return 0;
}
