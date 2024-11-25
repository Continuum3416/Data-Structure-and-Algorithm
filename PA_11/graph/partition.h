#pragma once

#include <list>

namespace dsac::graph {

/// A representation of a universe of elements organized into disjoint sets
///
/// This implementation uses a tree-based representation of sets with path
/// compression during the find operation and performing union with
/// union-by-size heuristic
template <typename T>
class Partition {

  private:
    //---------- nested Cluster class ----------
    class Cluster {
      public:
        friend Partition;
        T element;
        int size{1};
        Cluster* parent;
        Cluster(T elem) : element{elem} { }   // will set parent after cluster copied to the list
    }; //---------- end of Cluster class ----------

    std::list<Cluster> clusters;    // clusters kept in a list so that destructor destroys them
    
  public:    
    //---------- nested Position class ----------
    class Position {
      private:
        friend Partition;
        Cluster* cluster{nullptr};
        Position(Cluster* c) : cluster{c} {}
        
      public:
        Position() {}
        bool operator==(Position other) const { return cluster == other.cluster; }
        bool operator!=(Position other) const { return cluster != other.cluster; }
        T& operator*() const { return cluster->element; }
        T* operator->() const { return &(cluster->element); }
    }; //---------- end of Position class ----------

    /// Adds the given element to the universe and returns its Position token
    Position make_cluster(T elem) {
        clusters.push_back(Cluster(elem));
        Cluster& newest = clusters.back();
        newest.parent = &newest;
        return Position(&newest);
    }

    /// Finds the cluster currently containing the element indicated by Position p
    /// and returns the Position for the cluster's leader
    Position find(Position p) {
        if (p.cluster->parent != p.cluster) {
            p.cluster->parent = find(p.cluster->parent).cluster;    // overwrite old parent after recursion
        }
        return Position(p.cluster->parent);
    }

    /// Combines the clusters containing elements indicated by p and q (if not already the same cluster)
    void combine(Position p, Position q) {
        Cluster* a = find(p).cluster;
        Cluster* b = find(q).cluster;
        if (a != b) {
            if (a->size > b->size) {
                b->parent = a;
                a->size += b->size;
            } else {
                a->parent = b;
                b->size += a->size;
            }
        }
    }
};
    
} // namespace dsac::graph
