#pragma once

#include <list>
#include <string>
#include <tuple>
#include <map>
#include "graph.h"

namespace dsac::graph {

template <typename V, typename E>
Graph<V,E> graph_from_edgelist(std::list<std::tuple<V,V,E,int>> edgelist, bool is_directed = false) {
    Graph<V,E> G(is_directed);
    std::map<V, typename Graph<V,E>::Vertex> seen;
    for (auto entry : edgelist) {
        V orig,dest;
        E elem;
        int weight;
        std::tie(orig,dest,elem,weight) = entry;
        typename Graph<V,E>::Vertex u,v;
        if (seen.find(orig) == seen.end())
            seen[orig] = G.insert_vertex(orig);
        u = seen[orig];
        if (seen.find(dest) == seen.end())
            seen[dest] = G.insert_vertex(dest);
        v = seen[dest];

        G.insert_edge(u, v, weight, elem);
    }
    return G;
}


/// Returns the unweighted, directed graph from Figure 14.1.2 of DSAC
Graph<std::string,std::string> figure_14_1_2() {
    std::list<std::tuple<std::string,std::string,std::string,int>> edges = {
        {"BOS","JFK","NW 35", 1},
        {"BOS","MIA","DL 247", 1},
        {"JFK","SFO","SW 45", 1},
        {"JFK","DFW","AA 1387", 1},
        {"JFK","MIA","AA 903", 1},
        {"MIA","LAX","AA 411", 1},
        {"MIA","DFW","AA 523", 1},
        {"DFW","ORD","DL 335", 1},
        {"DFW","LAX","AA 49", 1},
        {"ORD","DFW","UA 877", 1},
        {"LAX","ORD","UA 120", 1}
    };
    return graph_from_edgelist(edges, true);
}
    
/// Returns the unweighted, directed graph from Figure 14.1.3 of DSAC
Graph<std::string,std::string> figure_14_1_3() {
    std::list<std::tuple<std::string,std::string,std::string,int>> edges = {
        {"BOS","SFO","",1}, {"BOS","JFK","",1}, {"BOS","MIA","",1},
        {"JFK","BOS","",1}, {"JFK","DFW","",1}, {"JFK","MIA","",1},
        {"JFK","SFO","",1}, {"ORD","DFW","",1}, {"ORD","MIA","",1},
        {"LAX","ORD","",1}, {"DFW","SFO","",1}, {"DFW","ORD","",1},
        {"DFW","LAX","",1}, {"MIA","DFW","",1}, {"MIA","LAX","",1}
    };
    return graph_from_edgelist(edges, true);
}

/// Returns the unweighted, directed graph from Figure 14.4.1 of DSAC
Graph<std::string,std::string> figure_14_4_1() {
    std::list<std::tuple<std::string,std::string,std::string,int>> edges = {
        {"BOS","SFO","",1}, {"BOS","JFK","",1}, {"BOS","MIA","",1},
        {"JFK","BOS","",1}, {"JFK","DFW","",1}, {"JFK","MIA","",1},
        {"JFK","SFO","",1}, {"ORD","DFW","",1}, {"ORD","MIA","",1},
        {"LAX","ORD","",1}, {"DFW","SFO","",1}, {"DFW","ORD","",1},
        {"DFW","LAX","",1}, {"MIA","DFW","",1}, {"MIA","LAX","",1},
        {"SFO","LAX","",1}
    };
    return graph_from_edgelist(edges, true);
}

/// Returns the unweighted, undirected graph from Figure 14.4.2 of DSAC
Graph<std::string,std::string> figure_14_4_2() {
    std::list<std::tuple<std::string,std::string,std::string,int>> edges = {
        {"A","B","",1}, {"A","E","",1}, {"A","F","",1}, {"B","C","",1},
        {"B","F","",1}, {"C","D","",1}, {"C","G","",1}, {"D","G","",1},
        {"D","H","",1}, {"E","F","",1}, {"E","I","",1}, {"F","I","",1},
        {"G","J","",1}, {"G","K","",1}, {"G","L","",1}, {"H","L","",1},
        {"I","J","",1}, {"I","M","",1}, {"I","N","",1}, {"J","K","",1},
        {"K","N","",1}, {"K","O","",1}, {"L","P","",1}, {"M","N","",1}
    };
    return graph_from_edgelist(edges, false);
}

/// Returns the unweighted, undirected graph from Figure 14.4.3 of DSAC
/// (same as Figure 14.4.2)    
Graph<std::string,std::string> figure_14_4_3() { return figure_14_4_2(); }
    

/// Returns the unweighted, directed graph from Figure 14.5.1 of DSAC
Graph<std::string,std::string> figure_14_5_1() {
    std::list<std::tuple<std::string,std::string,std::string,int>> edges = {
        {"BOS","JFK","",1}, {"BOS","MIA","",1}, {"JFK","BOS","",1}, {"JFK","DFW","",1},
        {"JFK","MIA","",1}, {"JFK","SFO","",1}, {"ORD","DFW","",1},
        {"LAX","ORD","",1}, {"DFW","SFO","",1}, {"DFW","ORD","",1},
        {"DFW","LAX","",1}, {"MIA","DFW","",1}, {"MIA","LAX","",1}
    };
    return graph_from_edgelist(edges, true);
}

/// Returns the unweighted, directed graph from Figure 14.6.1 of DSAC
Graph<std::string,std::string> figure_14_6_1() {
    std::list<std::tuple<std::string,std::string,std::string,int>> edges = {
        {"A","C","",1}, {"A","D","",1}, {"B","D","",1}, {"B","F","",1},
        {"C","D","",1}, {"C","E","",1}, {"C","H","",1}, {"D","F","",1},
        {"E","G","",1}, {"F","G","",1}, {"F","H","",1}, {"G","H","",1}
    };
    return graph_from_edgelist(edges, true);
}

/// Returns the unweighted, directed graph from Figure 14.6.2 of DSAC
/// (same as Figure 14.6.1)
Graph<std::string,std::string> figure_14_6_2() { return figure_14_6_1(); }


/// Returns the unweighted, undirected graph from Figure 14.7.1 of DSAC
Graph<std::string,std::string> figure_14_7_1() {
    std::list<std::tuple<std::string,std::string,std::string,int>> edges = {
        {"SFO", "LAX", "", 337}, {"SFO", "BOS", "", 2704}, {"SFO", "ORD", "", 1846},
        {"SFO", "DFW", "", 1464}, {"LAX", "DFW", "", 1235}, {"LAX", "MIA", "", 2342},
        {"DFW", "ORD", "", 802}, {"DFW", "MIA", "", 1121}, {"ORD", "BOS", "", 867},
        {"ORD", "JFK", "", 740}, {"MIA", "JFK", "", 1090}, {"MIA", "BOS", "", 1258},
        {"JFK", "BOS", "", 187}        
    };
    return graph_from_edgelist(edges, false);
}

/// Returns the unweighted, undirected graph from Figure 14.7.2 of DSAC
Graph<std::string,std::string> figure_14_7_2() {
    std::list<std::tuple<std::string,std::string,std::string,int>> edges = {
        {"SFO", "LAX", "", 337}, {"SFO", "BOS", "", 2704}, {"SFO", "ORD", "", 1846},
        {"SFO", "DFW", "", 1464}, {"LAX", "DFW", "", 1235}, {"LAX", "MIA", "", 2342},
        {"DFW", "ORD", "", 802}, {"DFW", "JFK", "", 1391}, {"DFW", "MIA", "", 1121},
        {"ORD", "BOS", "", 867}, {"ORD", "PVD", "", 849}, {"ORD", "JFK", "", 740},
        {"ORD", "BWI", "", 621}, {"MIA", "BWI", "", 946}, {"MIA", "JFK", "", 1090},
        {"MIA", "BOS", "", 1258}, {"BWI", "JFK", "", 184}, {"JFK", "PVD", "", 144},
        {"JFK", "BOS", "", 187}
    };
    return graph_from_edgelist(edges, false);
}

/// Returns the unweighted, undirected graph from Figure 14.8.2 of DSAC
/// (same as Figure 14.7.2)    
Graph<std::string,std::string> figure_14_8_2() { return figure_14_7_2(); }


/// Returns the unweighted, undirected graph from Figure 14.8.3 of DSAC
/// (same as Figure 14.7.2 and 14.8.2)    
Graph<std::string,std::string> figure_14_8_3() { return figure_14_7_2(); }

    
} // namespace dsac::graph
