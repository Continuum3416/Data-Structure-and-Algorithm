/*  Program:    
    Author: Don Le
    Class: CSCI 240
    Date: December 11 2024
    Description: Problem 3
    I certify that the code below is my own work.
    Exception(s): N/A
*/

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <limits>
#include "graph/graph.h"
#include "priority/heap_adaptable_priority_queue.h"


using namespace std;
using namespace dsac::graph;
using namespace dsac::priority;

template <typename V, typename E> void path(const Graph<V,E>& g, 
    typename Graph<V,E>::Vertex src, 
    typename Graph<V,E>::Vertex dest) {

    typedef HeapAdaptablePriorityQueue<std::pair<int, typename Graph<V,E>::Vertex>> AdaptablePQ;
    typedef VertexMap<V,E, typename AdaptablePQ::Locator> VertexLocatorMap;
    
    VertexIntMap<V,E> D;                                 // D[v] is upper bound from s to v
    VertexIntMap<V,E> cloud;                             // map reachable v to its D[v] value
    VertexLocatorMap pqlocator;                              // map from vertex to its pq locator
    VertexVertexMap<V,E> predecessors;                  // to store predecessors
    AdaptablePQ pq;                                          // PQ entry is {D[v],v}
    
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
    
    // Check if there is no path to dest
    if (D[dest] == std::numeric_limits<int>::max()) {
        cout << "Path from " <<*src << " to " << *dest << ": ";
        cout << "no \n";
        return;  // Exit the function if no path is found
    }

    // Print the shortest path from src to dest
    vector<typename Graph<V,E>::Vertex> path;
    typename Graph<V,E>::Vertex current = dest;
    int total_cost = 0;  // To track the total cost
    
    // Reconstruct the path from destination to source
    while (current != src) {
        path.push_back(current);
        auto pred = predecessors.at(current);
        for (auto e : g.incident_edges(pred)) {
            if (g.opposite(e, pred) == current) {
                total_cost += e.weight();
                break;
            }
        }
        current = pred;
    }
    
    path.push_back(src);  // Add the source vertex
    
    // Reverse path because we reconstructed it backwards
    reverse(path.begin(), path.end());
    
    // Output the result
    cout << "Path from " <<*src << " to " << *dest << ": ";
    cout << "yes (";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << *path[i];
        if (i < path.size() - 1) {
            cout << " ";
        }
    }
    cout << ")\n";
    

}




int main(){
    cout << "Author: Don Le" << endl;
    cout << "I certify that I did my own work with no outside help. " << endl;
    Graph<int, int> myGraph(true);
    int n = 4;

    // Add vertices
    vector<typename Graph<int, int>::Vertex> V;
    V.reserve(n);
    for(int i = 0; i <= n; i++){
        V[i] = myGraph.insert_vertex(i);
    }
    

    // Add directed edges
    myGraph.insert_edge(V[0], V[2]);
    myGraph.insert_edge(V[2], V[4]);
    myGraph.insert_edge(V[4], V[3]);
    myGraph.insert_edge(V[3], V[4]);
    myGraph.insert_edge(V[3], V[2]);
    myGraph.insert_edge(V[1], V[3]);
    

    cout << "Output for 0 to 4 and 4 to 0:" << endl;
    path(myGraph, V[0], V[4]);

    path(myGraph, V[4], V[0]);

    // dump(myGraph, cout);

    
    
    cout << "\nOutput for all vertices:" << endl;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <=n; j++){
            if(i != j) path(myGraph, V[i], V[j]);
        }
    }

    // Add directed edges from 3 to 0 and 3 to 1
    myGraph.insert_edge(V[3], V[0]);
    myGraph.insert_edge(V[3], V[1]);
    cout << "\nOutput after adding 3 to 0 and 3 to 1:" << endl;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <=n; j++){
            if(i != j) path(myGraph, V[i], V[j]);
        }
    }


    // Run: g++ p3.cpp -o p3.exe; ./p3.exe
    return 0;
}