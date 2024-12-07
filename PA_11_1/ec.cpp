#include <iostream>
#include <list>
#include <string>
#include <utility> // for std::pair
#include <unordered_map>
#include <queue>
#include "graph/adjacency_list_graph.h"

using namespace std;
using namespace dsac::graph;

template <typename V, typename E>  
VertexList_ALG<V,E> topological_sort_ALG(const AdjacencyListGraph<V,E>& g) {
    VertexList_ALG<V,E> topo;                 // list of vertices placed in topological order
    VertexList_ALG<V,E> ready;                // list of vertices that have no remaining ocnstraints
    VertexIntMap_ALG<V,E> incount;            // keep track of in-degree for each vertex
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


int main() {
    AdjacencyListGraph<string, int> Graph(true);


    // Add vertices
    auto A = Graph.insert_vertex("A");
    auto B = Graph.insert_vertex("B");
    auto C = Graph.insert_vertex("C");
    auto D = Graph.insert_vertex("D");
    auto E = Graph.insert_vertex("E");
    auto F = Graph.insert_vertex("F");

    // Add edges
    Graph.insert_edge(B, A);
    Graph.insert_edge(A, D);
    Graph.insert_edge(B, C);
    Graph.insert_edge(C, D);
    Graph.insert_edge(A, F);
    Graph.insert_edge(D, E);


    auto sorted_vertices = topological_sort_ALG<string, int>(Graph);

    // Output the sorted vertices
    cout << "Topologically sorted order: ";
    for (auto vertex : sorted_vertices) {
        cout << *vertex << " ";
    }
    cout << endl;



    // Run: g++ ec.cpp -o ec.exe; ./ec.exe
    return 0;
}



