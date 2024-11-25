#include <iostream>
#include <list>
#include <string>
#include <utility> // for std::pair
#include <unordered_map>
#include <queue>
#include "graph/adjacency_list_graph.h"

using namespace std;
using namespace dsac::graph;





int main() {
    AdjacencyListGraph<string, int> graph;

    // Add vertices
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");
    graph.add_vertex("E");
    graph.add_vertex("F");

    // Add edges
    
    graph.add_directed_edge("B", "A");
    graph.add_directed_edge("A", "D");
    graph.add_directed_edge("B", "C");
    graph.add_directed_edge("C", "D");
    graph.add_directed_edge("A", "F");
    graph.add_directed_edge("D", "E");

    // Print the graph
    graph.print_graph();

    list<string> topological_order = graph.topological_sort();
    cout << "\nTopological Order: ";
    for (const string& vertex : topological_order) {
        cout << vertex << " ";
    }
    cout << endl;



    // auto topo_order = topological_sort_(graph);

    // // Print the topological order
    // std::cout << "Topological Sort Order: ";
    // for (const auto& vertex : topo_order) {
    //     std::cout << vertex << " ";
    // }
    // std::cout << std::endl;

    // Run: g++ ec.cpp -o ec.exe; ./ec.exe
    return 0;
}



