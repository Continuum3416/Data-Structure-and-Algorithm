#pragma once

#include <iostream>
#include <functional>       // defines std::hash
#include <list>             // for std::list
#include <unordered_map>
#include <unordered_set>
#include <queue>            // for priority_queue
#include <limits>           // for numeric_limits
#include <utility>          // for std::pair

using namespace std;


namespace dsac::graph {


// V: any type, E: usually numeric
template <typename V, typename E> class AdjacencyListGraph {
private:
    struct Edge {
        V vertex;            // Vertex this edge points to
        int weight;          // Edge weight
    };

    struct Vertex {
        V name;              // Name or identifier for the vertex
        list<Edge> adjacencies;  // List of adjacent vertices (edges)
    };

    list<Vertex> vertices;
    int edge_count = 0; // Tracks the number of edges in the graph
    unordered_map<V, bool> visited; // To track visited vertices

public:
    // Adds a vertex to the graph
    void add_vertex(const V& name) {
        vertices.push_back(Vertex{name});
    }


    void add_undirected_edge(const V& from, const V& to, int weight = 0) {
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

    // void add_undirected_duplicate_edge(const V& from, const V& to, int weight = 0) {
    //     auto from_vertex = find_vertex(from);
    //     auto to_vertex = find_vertex(to);
        
    //     // Add edge from 'from' to 'to'
    //     if (from_vertex) {
    //         from_vertex->adjacencies.push_back({to, weight});
    //     }
        
    //     // Add edge from 'to' to 'from' (for undirected graph)
    //     if (to_vertex) {
    //         to_vertex->adjacencies.push_back({from, weight});
    //     }
    // }

    void add_directed_edge(const V& from, const V& to, int weight = 0) {
        auto from_vertex = find_vertex(from);
        if (from_vertex) {
            from_vertex->adjacencies.push_back({to, weight});
            edge_count++; // Increment the edge count
        }
    }

    void print_graph() const {
        cout << vertices.size() << " vertices and " << edge_count << " edges\n";
        for (const auto& vertex : vertices) {
            cout << "Vertex " << vertex.name << endl;
            cout << vertex.adjacencies.size() << " adjacencies:";
            bool first = true;
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

    void dfs(const V& start) {
        visited.clear();  // Clear visited map before starting DFS
        dfs_helper(start);  // Start DFS traversal
    }

    // Dijkstra's algorithm to find the shortest path from source to destination
    void dijkstra(const V& source, const V& destination) {
        unordered_map<V, int> distances;    // Distance from source to each vertex
        unordered_map<V, V> previous;       // To reconstruct the path
        unordered_map<V, bool> visited;     // Track visited vertices
        auto compare = [](pair<V, int> a, pair<V, int> b) { return a.second > b.second; };
        priority_queue<pair<V, int>, vector<pair<V, int>>, decltype(compare)> pq(compare);

        // Initialize distances to infinity and source distance to 0
        for (const auto& vertex : vertices) {
            distances[vertex.name] = std::numeric_limits<int>::max();
            visited[vertex.name] = false;
        }
        distances[source] = 0;
        pq.push({source, 0});

        while (!pq.empty()) {
            V current = pq.top().first;
            pq.pop();

            // Skip if already visited
            if (visited[current]) continue;
            visited[current] = true;

            // Process neighbors of the current vertex
            auto current_vertex = find_vertex(current);
            if (current_vertex) {
                for (const auto& edge : current_vertex->adjacencies) {
                    if (!visited[edge.vertex]) {
                        int new_distance = distances[current] + edge.weight;
                        if (new_distance < distances[edge.vertex]) {
                            distances[edge.vertex] = new_distance;
                            previous[edge.vertex] = current;
                            pq.push({edge.vertex, new_distance});
                        }
                    }
                }
            }
        }

        // Print the shortest path and total cost
        if (distances[destination] == std::numeric_limits<int>::max()) {
            cout << "No path from " << source << " to " << destination << endl;
        } else {
            cout << "Shortest path from " << source << " to " << destination << ": ";
            print_path(previous, source, destination);
            cout << " with total cost of " << distances[destination] << endl;
        }
    }

    list<V> topological_sort() {
        unordered_map<V, int> in_degree;  // Track in-degree for each vertex
        unordered_map<V, Vertex*> vertex_map;

        // Initialize in-degree for all vertices
        for (auto& vertex : vertices) {
            in_degree[vertex.name] = 0;
            vertex_map[vertex.name] = &vertex;
        }

        // Calculate in-degree for each vertex
        for (const auto& vertex : vertices) {
            for (const auto& edge : vertex.adjacencies) {
                in_degree[edge.vertex]++;
            }
        }

        // Add vertices with in-degree 0 to the list
        list<V> zero_in_degree;
        for (const auto& entry : in_degree) {
            if (entry.second == 0) {
                zero_in_degree.push_back(entry.first);
            }
        }

        list<V> topo;  // Stores the topological order

        // Process vertices in topological order
        while (!zero_in_degree.empty()) {
            V current = zero_in_degree.front();
            zero_in_degree.pop_front();  
            topo.push_back(current);

            for (const auto& edge : vertex_map[current]->adjacencies) {
                in_degree[edge.vertex]--;
                if (in_degree[edge.vertex] == 0) {
                    zero_in_degree.push_back(edge.vertex); 
                }
            }
        }

        // cycle detection
        if (topo.size() != vertices.size()) {
            cerr << "This graph has a cycle. Topological sort not possible." << endl;
            return {};
        }

        return topo;
    }

private:
    // Helper function to find a vertex by name
    Vertex* find_vertex(const V& name) {
        for (auto& vertex : vertices) {
            if (vertex.name == name)
                return &vertex;
        }
        return nullptr;
    }


    bool edge_exists(const list<Edge>& edges, const V& vertex) const {
        for (const auto& edge : edges) {
            if (edge.vertex == vertex)
                return true;
        }
        return false;
    }

    // Helper function to print the path
    void print_path(unordered_map<V, V>& previous, const V& source, const V& destination) {
        if (source == destination) {
            cout << source;
        } else if (previous.find(destination) == previous.end()) {
            cout << "No path";
        } else {
            print_path(previous, source, previous[destination]);
            cout << " -> " << destination;
        }
    }

    // Helper function to perform DFS recursively
    void dfs_helper(const V& vertex) {
        visited[vertex] = true;  // Mark vertex as visited
        cout << "Visit vertex: " << vertex << endl;

        // Traverse all adjacent vertices
        auto current_vertex = find_vertex(vertex);
        if (current_vertex) {
            for (const auto& edge : current_vertex->adjacencies) {
                if (!visited[edge.vertex]) {
                    cout << "Discovery edge from " << vertex << " to " << edge.vertex << endl;
                    dfs_helper(edge.vertex);  // Recurse on the adjacent vertex
                }
            }
        }
    }


};

// template <typename V, typename E>
// using VertexList = std::list<typename AdjacencyListGraph<V,E>::Vertex>;


// template <typename V, typename E>
// using EdgeList = std::list<typename AdjacencyListGraph<V,E>::Edge>;
    

// template <typename V, typename E>
// using VertexSet = std::unordered_set<typename AdjacencyListGraph<V,E>::Vertex, typename AdjacencyListGraph<V,E>::VertexHash>;



// template <typename V, typename E, typename T>
// using VertexMap = std::unordered_map<typename AdjacencyListGraph<V,E>::Vertex, T, typename AdjacencyListGraph<V,E>::VertexHash>;


// template <typename V, typename E>
// using VertexIntMap = VertexMap<V,E,int>;


// template <typename V, typename E>
// using VertexVertexMap = VertexMap<V,E,typename AdjacencyListGraph<V,E>::Vertex>;
    

// template <typename V, typename E>
// using VertexEdge = VertexMap<V,E,typename AdjacencyListGraph<V,E>::Edge>;

// template <typename V, typename E>    
// VertexList<V,E> topological_sort_(const AdjacencyListGraph<V,E>& g) {
//     VertexList<V,E> topo;                 // list of vertices placed in topological order
//     VertexList<V,E> ready;                // list of vertices that have no remaining ocnstraints
//     VertexIntMap<V,E> incount;            // keep track of in-degree for each vertex
//     for (auto u : g.vertices()) {
//         incount[u] = g.degree(u, false);  // second argument requests incoming degree
//         if (incount[u] == 0)              // if u has no incoming edges,
//             ready.push_back(u);           // it is free of constraints
//     }
//     while (!ready.empty()) {
//         auto u = ready.front();           // vertex u is free of constraints
//         ready.pop_front();
//         topo.push_back(u);                // add u to the topological order
//         for (auto v : g.neighbors(u)) {   // consider each outgoing neighbor of u
//             incount[v]--;                 // v has one less constraint without u
//             if (incount[v] == 0)
//                 ready.push_back(v);
//         }
//     }
//     return topo;
// }

} // namespace dsac::graph
