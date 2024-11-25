/*  Program:    
    Author:     
    Class:      
    Date:       
    Description: 
    I certify that the code below is my own work.
    Exception(s): N/A
*/


#include <iostream>
#include <list>
#include <string>
#include <utility> // for std::pair
#include "graph/graph.h"
#include "graph/adjacency_list_graph.h"

using namespace dsac::graph;
using namespace std;




int main() {
    AdjacencyListGraph<string, int> graph;

    // Add vertices
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");

    // Add edges
    graph.add_undirected_edge("A", "B", 100);
    graph.add_undirected_edge("A", "C", 200);
    graph.add_undirected_edge("B", "D", 300);


    // Print the graph
    graph.print_graph();

    // Run: g++ p1.cpp -o p1.exe; ./p1.exe
    return 0;
}



