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

using namespace std;

using namespace std;

class AdjacencyListGraph {
private:
    struct Edge {
        string vertex;
        int weight;
    };

    struct Vertex {
        string name;
        list<Edge> adjacencies;
    };

    list<Vertex> vertices;
    int edge_count = 0; // Tracks the number of edges in the graph

public:
    // Adds a vertex to the graph
    void add_vertex(const string& name) {
        vertices.push_back(Vertex{name});
    }

    // Adds an edge between two vertices
    void add_edge(const string& from, const string& to, int weight) {
        auto from_vertex = find_vertex(from);
        auto to_vertex = find_vertex(to);

        if (from_vertex && to_vertex) {
            // Add edge if it doesn't already exist (to avoid duplicates)
            if (!edge_exists(from_vertex->adjacencies, to)) {
                from_vertex->adjacencies.push_back({to, weight});
                to_vertex->adjacencies.push_back({from, weight}); // Undirected graph
                edge_count++; // Increment the edge count
            }
        }
    }

    // Prints the graph
    void print_graph() const {
        cout << vertices.size() << " vertices and " << edge_count << " edges\n";
        for (const auto& vertex : vertices) {
            cout << "Vertex " << vertex.name << endl;
            cout << vertex.adjacencies.size() << " adjacencies:";
            bool first = true; // Control comma placement
            for (const auto& edge : vertex.adjacencies) {
                if (!first) {
                    cout << ",";
                }
                cout << "(" << edge.vertex << ", " << edge.weight << ")";
                first = false;
            }
            cout << endl;
        }
    }

private:
    // Helper function to find a vertex by name
    Vertex* find_vertex(const string& name) {
        for (auto& vertex : vertices) {
            if (vertex.name == name)
                return &vertex;
        }
        return nullptr;
    }

    // Helper function to check if an edge exists
    bool edge_exists(const list<Edge>& edges, const string& vertex) const {
        for (const auto& edge : edges) {
            if (edge.vertex == vertex)
                return true;
        }
        return false;
    }
};

int main() {
    AdjacencyListGraph graph;

    // Add vertices
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");

    // Add edges
    graph.add_edge("A", "B", 100);
    graph.add_edge("A", "C", 200);
    graph.add_edge("B", "D", 300);

    // Print the graph
    graph.print_graph();

    // // Run: g++ p1_0.cpp -o p1_0.exe; ./p1_0.exe

    return 0;
}



