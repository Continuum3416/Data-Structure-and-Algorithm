#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <limits>
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

    // Add directed edges with weights
    graph.add_directed_edge("B", "A", 3);
    graph.add_directed_edge("B", "C", 4);
    graph.add_directed_edge("A", "D", 5);
    graph.add_directed_edge("A", "E", 10);
    graph.add_directed_edge("C", "D", 2);
    graph.add_directed_edge("D", "E", 3);
    graph.add_directed_edge("E", "C", 6);

    // Find shortest path from B to E
    graph.dijkstra("B", "E");


    // Run: g++ p3.cpp -o p3.exe; ./p3.exe
    return 0;
}
