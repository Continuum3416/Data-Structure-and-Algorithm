#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include "graph/adjacency_list_graph.h"

using namespace std;
using namespace dsac::graph;



template <typename V, typename E>    
void dfs_ALG(const AdjacencyListGraph<V,E>& g, typename AdjacencyListGraph<V,E>::Vertex u, VertexVertexMap_ALG<V,E>& discovered) {
    if (discovered.count(u) == 0){
        discovered[u] = u;                             // we conventionally mark a tree root as its own parent
        cout << "Visited vertex " <<*u << endl;
    }
        
    for (auto v : g.neighbors(u)) {                    // for every outgoing neighbor of u
        if (discovered.count(v) == 0) {                // v is undiscovered
            cout << "Discovery edge from " << *u << " to " << *v << endl;
            cout << "Visited vertex " <<*v << endl;
            discovered[v] = u;                         // u is the parent of v in the tree
            dfs_ALG(g, v, discovered);                     // recursively explore from v
        }
    }
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
    Graph.insert_edge(C, B);
    Graph.insert_edge(C, A);
    Graph.insert_edge(C, D);
    Graph.insert_edge(B, A);
    Graph.insert_edge(A, D);
    Graph.insert_edge(D, E);


    // Perform DFS starting from vertex C
    std::cout << "Output:\n";
    VertexVertexMap_ALG<string, int> discovered;
    dfs_ALG(Graph, C, discovered);

    // Print tree
    
    // for (const auto& [vertex, parent] : discovered) {
    //     //cout << *vertex << " discovered by " << *parent << "\n";
    //     cout << "Visited vertex: " << *vertex<< '\n';
    //     cout << "Discovery edge from " << *vertex << " to " << *parent << endl;
    // }


    // Run: g++ p2.cpp -o p2.exe; ./p2.exe
    return 0;
}
