#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
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

    // Add edges (the graph described in the problem)
    graph.add_undirected_edge("A", "B"); // Undirected edge between A and B
    graph.add_undirected_edge("A", "C"); // Undirected edge between A and C
    graph.add_undirected_edge("B", "C"); // Undirected edge between B and C
    graph.add_undirected_edge("B", "D"); // Undirected edge between B and D
    graph.add_undirected_edge("B", "E"); // Undirected edge between B and E
    graph.add_undirected_edge("C", "D"); // Undirected edge between C and D

    // Perform DFS starting from vertex C
    graph.dfs("C");


    // Run: g++ p2.cpp -o p2.exe; ./p2.exe
    return 0;
}
