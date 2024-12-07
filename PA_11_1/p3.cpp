#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <limits>
#include "graph/adjacency_list_graph.h"
#include "priority/heap_adaptable_priority_queue.h"


using namespace std;
using namespace dsac::graph;
using namespace dsac::priority;

template <typename V, typename E> void Dijkstra(const AdjacencyListGraph<V,E>& g, 
    typename AdjacencyListGraph<V,E>::Vertex src, 
    typename AdjacencyListGraph<V,E>::Vertex dest) {

    typedef HeapAdaptablePriorityQueue<std::pair<int, typename AdjacencyListGraph<V,E>::Vertex>> AdaptablePQ;
    typedef VertexMap_ALG<V,E, typename AdaptablePQ::Locator> VertexLocatorMap;
    
    VertexIntMap_ALG<V,E> D;                                // D[v] is upper bound from s to v
    VertexIntMap_ALG<V,E> cloud;                            // map reachable v to its D[v] value
    AdaptablePQ pq;                                          // PQ entry is {D[v],v}
    VertexLocatorMap pqlocator;                              // map from vertex to its pq locator
    VertexVertexMap_ALG<V,E> predecessors;                  // to store predecessors
    
    // Initialize distances and priority queue
    for (auto v : g.vertices()) {
        D[v] = (v == src ? 0 : std::numeric_limits<int>::max());
        pqlocator[v] = pq.insert({D[v], v});
    }

    // Dijkstra's algorithm
    while (!pq.empty()) {
        auto entry = pq.min();
        pq.remove_min();
        auto u = entry.second;                          // vertex removed from PQ
        cloud[u] = entry.first;                         // save final distance to u
        pqlocator.erase(u);                             // u is no longer in pq
        for (auto e : g.incident_edges(u)) {
            auto v = g.opposite(e,u);
            if (cloud.count(v) == 0) {                  // v not yet finalized
                // Perform relaxation step on edge (u,v)
                if (D[u] + e.weight() < D[v]) {         // better path to v?
                    D[v] = D[u] + e.weight();           // update the distance
                    pq.update(pqlocator[v], {D[v],v});  // update pq entry
                    predecessors[v] = u; 
                }
            }
        }
    }
    
    // Print the shortest path from src to dest
    vector<typename AdjacencyListGraph<V,E>::Vertex> path;
    typename AdjacencyListGraph<V,E>::Vertex current = dest;
    int total_cost = 0;  // To track the total cost
    
    // Reconstruct the path from destination to source
    while (current != src) {
        path.push_back(current);
        auto pred = predecessors.at(current);  // Move to the predecessor
        // Find the edge between current and pred to get the weight
        for (auto e : g.incident_edges(pred)) {
            if (g.opposite(e, pred) == current) {
                total_cost += e.weight();  // Add edge weight to total cost
                break;
            }
        }
        current = pred;
    }
    
    path.push_back(src);  // Add the source vertex
    
    // Reverse path because we reconstructed it backwards
    reverse(path.begin(), path.end());
    
    // Output the result
    cout << "Shortest path from " << *src << " to " << *dest << ": ";
    // for (const auto& v : path) {
    //     cout << *v << " -> ";
    // }
    for (size_t i = 0; i < path.size(); ++i) {
        cout << *path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << "\n";
    
    // Output the total cost
    cout << "Total cost: " << total_cost << endl;
}








int main() {
    AdjacencyListGraph<string, int> Graph(true);


    // Add vertices
    auto A = Graph.insert_vertex("A");
    auto B = Graph.insert_vertex("B");
    auto C = Graph.insert_vertex("C");
    auto D = Graph.insert_vertex("D");
    auto E = Graph.insert_vertex("E");



    // Add undirected edges
    Graph.insert_edge(B, A, 3);
    Graph.insert_edge(B, C, 4);
    Graph.insert_edge(A, D, 5);
    Graph.insert_edge(A, E, 10);
    Graph.insert_edge(C, D, 2);
    Graph.insert_edge(D, E, 3);
    Graph.insert_edge(E, C, 6);



    // Find shortest path from B to E
    Dijkstra(Graph, B, E);
    

    // Run: g++ p3.cpp -o p3.exe; ./p3.exe
    return 0;
}
