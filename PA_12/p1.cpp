#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <limits>
#include <map>
#include <set>
#include <sstream>
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
    cout << "Cheapest flight from " << *src << " to " << *dest << ": ";
    // for (size_t i = 0; i < path.size(); ++i) {
    //     cout << *path[i];
    //     if (i < path.size() - 1) {
    //         cout << " -> " << *path[i].weight;
    //     }
    // }
    for (size_t i = 0; i < path.size(); ++i) {
        cout << *path[i]; // Print the current vertex
        if (i < path.size() - 1) {
            // Find the edge between path[i] and path[i+1]
            for (auto e : g.incident_edges(path[i])) {
                if (g.opposite(e, path[i]) == path[i + 1]) {
                    cout << " -[" << e.weight() << "]-> "; // Print the edge weight
                    break; // Stop once the edge is found
                }
            }
        }
    }
    cout << "\n";
    
    // Output the total cost
    cout << "Total cost: $" << total_cost << endl;
}







bool isNumeric(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

// Store strings uniquely: Use a set to automatically handle uniqueness.
// Extract words: Tokenize each line to get the strings separately.
// Output unique strings: Iterate over the std::set to display the results.
set<string> readCities(const string& filename) {
    ifstream file(filename);
    set<string> uniqueStrings;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string word;

        while (iss >> word) {
            if (!isNumeric(word)){
                uniqueStrings.insert(word);
            }
        }
    }

    return uniqueStrings;
}


void insertEdges(const string& filename, 
                 AdjacencyListGraph<string, int>& Graph, 
                 const vector<AdjacencyListGraph<string, int>::Vertex>& cities) {
    ifstream file(filename);


    map<string, AdjacencyListGraph<string, int>::Vertex> vertexMap;
    for (const auto& city : cities) {
        vertexMap[*city] = city;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string source, destination;
        int weight;

        iss >> source >> destination >> weight;

        // Add edge to the graph
        // weight = 0;
        Graph.insert_edge(vertexMap[source], vertexMap[destination], weight);
    }
}


int main() {
    string filename = "PA12Flights-1.txt";
    AdjacencyListGraph<string, int> Graph(true);

    // vector<string> cities;

    set<string> extract_cities = readCities(filename);
    vector<AdjacencyListGraph<string, int>::Vertex> city(extract_cities.size());



    cout << "List of cities: ";
    auto setIt = extract_cities.begin();
    for (size_t i = 0; i < city.size(); ++i) {
        city[i] = Graph.insert_vertex(*setIt);
        ++setIt;
        cout << "[" << i << ", " <<*city[i] << "] ";
    }
    cout << '\n';

    // Insert edges into the graph
    insertEdges(filename, Graph, city);

    // cout << "\nGraph: " << endl;
    // dump(Graph, cout);



    // JFK is city[2], LAX is city[3]
    Dijkstra(Graph, city[2], city[3]);

    Dijkstra(Graph, city[3], city[2]);
    

    // cout << "All flights: " << endl;
    // for(int i = 0; i < city.size(); i++){
    //     for(int j = i + 1; j < city.size(); j++){
    //         Dijkstra(Graph, city[i], city[j]);
    //     }
    //     cout << '\n';
    // }
    

    // Run: g++ p1.cpp -o p1.exe; ./p1.exe
    return 0;
}