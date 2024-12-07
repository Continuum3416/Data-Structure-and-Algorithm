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
    AdjacencyListGraph<string, int> Graph(false); // undirected graph

    // type = AdjacencyListGraph<string, int>::Vertex 
    auto A = Graph.insert_vertex("A");
    auto B = Graph.insert_vertex("B");
    auto C = Graph.insert_vertex("C");
    auto D = Graph.insert_vertex("D");


    // Add directed edges with weights
    Graph.insert_edge(A, B, 100);
    Graph.insert_edge(A, C, 200);
    Graph.insert_edge(B, D, 300);

    dump(Graph, cout);



    // Run: g++ p1.cpp -o p1.exe; ./p1.exe
    return 0;
}



