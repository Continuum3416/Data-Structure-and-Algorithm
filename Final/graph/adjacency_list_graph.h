

#pragma once

#include <functional>       // defines std::hash
#include <iostream>         // only for debugging function
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>

namespace dsac::graph {

template <typename V, typename E>
class AdjacencyListGraph {
  private:
    class ActualVertex; // advanced declaration
    class ActualEdge;   // advanced declaration
    typedef std::list< ActualEdge* > IncidenceList;


    //---------- nested ActualVertex class ---------
    class ActualVertex {
      public:
        V element;
        IncidenceList outgoing;
        IncidenceList incoming;
        typename std::list<ActualVertex>::iterator pos;   // needed to erase from vertex_list
        ActualVertex(V elem) : element{elem} {}
    }; //---------- end of ActualVertex class ---------
    
    //---------- nested ActualEdge class ---------
    class ActualEdge {
      public:
        ActualVertex* origin;
        ActualVertex* dest;
        int weight;
        E element;
        typename std::list<ActualEdge>::iterator pos;   // needed to erase from edge_list
        ActualEdge(ActualVertex* u, ActualVertex* v, int w, E e)
            : origin{u}, dest{v}, weight{w}, element{e} {}
    }; //---------- end of ActualEdge class ---------

    // --------- Graph instance variables -----------
    std::list<ActualVertex> vertex_list;
    std::list<ActualEdge> edge_list;
    bool directed;

  public:
    
    /// Creates a new graph (directed or undirected, as specified by argument)
    AdjacencyListGraph(bool is_directed) : directed{is_directed} {}

    /// Returns true if graph is directed, false otherwise
    bool is_directed() const { return directed; }
    
    struct VertexHash;
    
    /// Vertex instance serves as a token for an underlying vertex
    class Vertex {
        friend AdjacencyListGraph;
        friend VertexHash;
        
      private:
        ActualVertex* vert{nullptr};
        Vertex(const ActualVertex* v) : vert{const_cast<ActualVertex*>(v)} {}
        
      public:
        Vertex() {}
        V& operator*() const { return vert->element; }
        V* operator->() const { return &(vert->element); }
        bool operator==(Vertex other) const { return vert == other.vert; }
        bool operator!=(Vertex other) const { return vert != other.vert; }
        bool operator<(Vertex other) const { return vert < other.vert; }   // arbitrary rule as map/pq key

        friend AdjacencyListGraph;
        friend VertexHash;
    };  //---------- end of Vertex class ---------

    struct VertexHash { size_t operator()(Vertex v) const { return size_t(v.vert); } };
    struct EdgeHash; 

    /// Edge instance serves as a token for an underlying edge
    class Edge {
        friend AdjacencyListGraph;
        friend EdgeHash;
        
      private:
        ActualEdge* edge{nullptr};
        Edge(const ActualEdge* e) : edge{const_cast<ActualEdge*>(e)} {}
        
      public:
        Edge() {}
        int weight() const { return edge->weight; }
        E& operator*() const { return edge->element; }
        E* operator->() const {return &(edge->element); }
        bool operator==(Edge other) const { return edge == other.edge; }
        bool operator!=(Edge other) const { return edge != other.edge; }
        bool operator<(Edge other) const { return edge < other.edge; }    // arbitrary rule as map/pq key
    };   //---------- end of Edge class ---------

    /// Hash functor that allows use of Edge as an unordered set/map key

    struct EdgeHash { size_t operator()(Edge e) const { return size_t(e.edge); } };

    /// Returns the number of vertices in the graph
    int num_vertices() const { return vertex_list.size(); }

    /// Returns the number of edges in the graph
    int num_edges() const { return edge_list.size(); }
    
    /// Returns a list of Vertex tokens
    std::list<Vertex> vertices() const {
        std::list<Vertex> result;
        for (const ActualVertex& v : vertex_list)  // Note: reference variable to get correct pointer
            result.push_back(Vertex(&v));
        return result;
    }

    /// Returns a list of Edge tokens
    std::list<Edge> edges() const {
        std::list<Edge> result;
        for (const ActualEdge& e : edge_list)      // Note: reference variable to get correct pointer
            result.push_back(Edge(&e));
        return result;
    }

    /// Return true if there exists an edge from u to v, false otherwise
    bool has_edge(Vertex u, Vertex v) const {
        return (u.vert->outgoing.count(v.vert) == 1);
    }
    
    /// Return the edge from u to v; undefined behavior if no such edge exists
    Edge get_edge(Vertex u, Vertex v) const {
        Edge edge;
        for (auto e = u.vert->outgoing.begin(); e != u.vert->outgoing.end(); ++e)
            if (opposite(*e, u) == v) {
                edge = *e;
            }
               
        return edge;  // find returns {ActualVertex*,ActualEdge*} pair
    }
    
    /// Returns the number of outgoing (or incoming) edges for Vertex v
    int degree(Vertex v, bool outgoing = true) const {
        IncidenceList& adj(outgoing || !directed ? v.vert->outgoing : v.vert->incoming);
        return adj.size();
    }

    /// Returns a list of outgoing (or incoming) Vertex tokens for neighbors of Vertex v
    // std::list<Vertex> neighbors(Vertex v, bool outgoing = true) const {
    //     std::list<Vertex> result;
    //     IncidenceList& adj(outgoing || !directed ? v.vert->outgoing : v.vert->incoming);
    //     for (auto p : adj)                           // p is {ActualVertex*,ActualEdge*} pair
    //         result.push_back(Vertex(p.first));
    //     return result;
    // }

    std::list<Vertex> neighbors(Vertex v, bool outgoing = true) const {
        std::list<Vertex> result;
        IncidenceList& adj(outgoing || !directed ? v.vert->outgoing : v.vert->incoming);
        for (auto edge : adj) {                       // edge is an ActualEdge*
            ActualVertex* neighbor = (edge->origin == v.vert) ? edge->dest : edge->origin;
            result.push_back(Vertex(neighbor));
        }
        return result;
    }
    
    /// Returns a list of outgoing (or incoming) Edge tokens for Vertex v
    std::list<Edge> incident_edges(Vertex v, bool outgoing = true) const {
        std::list<Edge> result;
        IncidenceList& adj(outgoing || !directed ? v.vert->outgoing : v.vert->incoming);
        for (auto p : adj)                           // p is {ActualVertex*,ActualEdge*} pair
            result.push_back(p);
        return result;
    }
    
    /// Returns the (origin,destination) pair for Edge e
    std::pair<Vertex,Vertex> endpoints(Edge e) const {
        return {Vertex(e.edge->origin), Vertex(e.edge->dest)};
    }
    
    /// Returns the opposite endpoint to Vertex v for Edge e
    Vertex opposite(Edge e, Vertex v) const {
        return Vertex(v.vert == e.edge->origin ? e.edge->dest : e.edge->origin);
    }
    
    /// Create a new vertex storing given element, and return Vertex token
    Vertex insert_vertex(V elem) {
        auto iter = vertex_list.emplace(vertex_list.end(), elem);
        iter->pos = iter;                            // save new vertex's position within vertex_list
        return Vertex(&*iter);                       // wrap the pointer to newly stored ActualVertex
    }

    /// Inserts new edge from u to v, storing given element, and given weight (default 1)
    /// If edge already exists, updates weight and element for that existing edge.
    /// Returns Edge token
    Edge insert_edge(Vertex u, Vertex v, int weight = 1, E elem = E()) {
        bool found = false;
        for (auto e = u.vert->outgoing.begin(); e != u.vert->outgoing.end(); ++e)
            if (opposite(*e, u) == v) {
                found = true;
                break;
            }
        if (!found) {                                     // update existing edge
            auto iter = edge_list.insert(edge_list.end(), ActualEdge(u.vert, v.vert, weight, elem));
            iter->pos = iter;                        // save new edge's position within edge_list
            ActualEdge* stored = &*iter;             // pointer to newly stored ActualEdge
            // now add edge to adjacency maps for vertices
            u.vert->outgoing.push_back(stored);       // outgoing edge for u
            IncidenceList& adj{ directed ? v.vert->incoming : v.vert->outgoing };
            adj.push_back(stored);                    // incoming edge for v (if directed graph)
            return Edge(stored);
        }
        else {                                     // update existing edge
            Edge e{ get_edge(u,v) };
            e.edge->weight = weight;
            e.edge->element = elem;
            return e;
        }
    }
   
    void erase(Edge e) {
        // first remove the edge from the endpoint adjacencies
        ActualVertex *u{e.edge->origin}, *v{e.edge->dest};
        u->outgoing.erase(v);
        IncidenceList& adj{directed ? v->incoming : v->outgoing};
        adj.erase(u);

        // now remove the edge from the edge list
        edge_list.erase(e.edge->pos);
    }

    // void erase(Vertex v) {
    //     for (auto p : v.vert->outgoing) {         // p is {ActualVertex*,ActualEdge*} pair
    //         IncidenceList& adj{directed ? p.first->incoming : p.first->outgoing};
    //         adj.erase(v.vert);                    // remove edge from opposite vertex's map
    //         edge_list.erase(p.second->pos);       // remove edge from overall edge_list
    //     }
    //     for (auto p : v.vert->incoming) {         // for undirected graph, incoming is empty
    //         p.first->outgoing.erase(v.vert);
    //         edge_list.erase(p.second->pos);
    //     }
        
    //     // now remove the vertex from the vertex list
    //     vertex_list.erase(v.vert->pos);
    // }


    void erase(Vertex v) {
        // Erase all outgoing edges
        for (auto edge : v.vert->outgoing) {
            IncidenceList& adj{directed ? edge->dest->incoming : edge->dest->outgoing};
            adj.remove(edge);                         // Remove from the destination's adjacency list
            edge_list.erase(edge->pos);               // Remove from the edge list
        }

        // Erase all incoming edges (for undirected, this will be empty)
        for (auto edge : v.vert->incoming) {
            edge->origin->outgoing.remove(edge);      // Remove from the origin's adjacency list
            edge_list.erase(edge->pos);               // Remove from the edge list
        }

        // Finally, remove the vertex itself
        vertex_list.erase(v.vert->pos);
    }

   
    
  private:
    // rebuild from scratch to get appropriate cross-referencing for internal pointers
    void clone(const AdjacencyListGraph& other) {
        directed = other.directed;
        vertex_list.clear();
        edge_list.clear();
        std::unordered_map<const ActualVertex*,Vertex> oldToNew;
        for (const auto& v : other.vertex_list)         // clone vertex v in new graph
            oldToNew[&v] = insert_vertex(v.element);   
        for (const auto& e : other.edge_list)           // clone edge e in new graph
            insert_edge(Vertex(oldToNew[e.origin]), Vertex(oldToNew[e.dest]), e.weight, e.element);
    }
    
 public:
    /// Copy constructor
    AdjacencyListGraph(const AdjacencyListGraph& other) { clone(other); }

    /// Copy assignment
    AdjacencyListGraph& operator=(const AdjacencyListGraph& other) {
        if (this != &other) { clone(other); }
        return *this;
    }

    /// Move constructor
    AdjacencyListGraph(AdjacencyListGraph&&) = default;
    
    /// Move assignment
    AdjacencyListGraph& operator=(AdjacencyListGraph&&) = default;
    
    /// Destructs a graph
    ~AdjacencyListGraph() = default;
    
    
};

// ------------------------------------------------------------------------------------------
// Convenient shorthands for some commonly used templated types in the graph algorithms
// ------------------------------------------------------------------------------------------

/// VertexList is a std::list of Vertex instances for Graph<V,E>
template <typename V, typename E>
using VertexList_ALG = std::list<typename AdjacencyListGraph<V,E>::Vertex>;

// /// EdgeList is a std::list of Edge instances for Graph<V,E>
template <typename V, typename E>
using EdgeList_ALG = std::list<typename AdjacencyListGraph<V,E>::Edge>;
    
// /// VertexSet is a std::unordered_set of Vertex instances for Graph<V,E>
template <typename V, typename E>
using VertexSet_ALG = std::unordered_set<typename AdjacencyListGraph<V,E>::Vertex, typename AdjacencyListGraph<V,E>::VertexHash>;


///// VertexMap is a std::unordered_map from Vertex to type T for Graph<V,E>
template <typename V, typename E, typename T>
using VertexMap_ALG = std::unordered_map<typename AdjacencyListGraph<V,E>::Vertex, T, typename AdjacencyListGraph<V,E>::VertexHash>;


/// VertexIntMap is a std::unordered_map from Vertex to int for Graph<V,E>
template <typename V, typename E>
using VertexIntMap_ALG = VertexMap_ALG<V,E,int>;

/// VertexVertexMap is a std::unordered_map from Vertex to Vertex for Graph<V,E>
template <typename V, typename E>
using VertexVertexMap_ALG = VertexMap_ALG<V,E,typename AdjacencyListGraph<V,E>::Vertex>;
    
/// VertexEdgeMap is a std::unordered_map from Vertex to Edge for Graph<V,E>
template <typename V, typename E>
using VertexEdge_ALG = VertexMap_ALG<V,E,typename AdjacencyListGraph<V,E>::Edge>;


/// Outputs graph representation to given stream

template <typename V, typename E>
void dump(const AdjacencyListGraph<V,E>& G, std::ostream& out) {
    out << G.num_vertices() << " vertices and " << G.num_edges() << " edges" << std::endl;
    for (typename AdjacencyListGraph<V,E>::Vertex v : G.vertices()) {
        out << "Vertex " <<*v;
        if (G.is_directed()) out << std::endl << " out (" << G.degree(v,true) << ")";
        out << ":";
        for (typename AdjacencyListGraph<V,E>::Edge e : G.incident_edges(v,true))
            out << " " << *(G.opposite(e, v)) << "(" << e.weight() << ")";

        if (G.is_directed()) {
            out << std::endl << "  in (" << G.degree(v,false) << "):";
            for (typename AdjacencyListGraph<V,E>::Edge e : G.incident_edges(v,false))
                out << " " << *(G.opposite(e, v)) << "(" << e.weight() << ")";
        }
        out << std::endl;
    }
    out << std::endl;
}
    
    
} // namespace dsac::graph



