// templated utility functions for many useful algorithms for general trees

#pragma once

#include <queue>        // used for breadth-first traversal

namespace dsac::tree {

/// returns the number of proper ancestors of p
template <typename Position>
int depth(Position p) {
    if (p.is_root())
        return 0;
    else
        return 1 + depth(p.parent());
}

template <typename Tree>
int height_bad(const Tree& t) {              // works, but quadratic worst-case
    int answer{0};
    for (auto p : t.positions())
        if (p.is_external())                 // max depth must be at a leaf
            answer = std::max(answer, depth(p));
    return answer;
}
    
template <typename Position>
int height(Position p) {
    int h{0};
    for (Position child : p.children())
        h = std::max(h, 1 + height(child));
    return h;
}
    
template <typename Position, typename Container>
void preorder(Position p, Container& visited) {
    visited.push_back(p);
    for (Position child : p.children())
        preorder(child, visited);
}

template <typename Position, typename Container>
void postorder(Position p, Container& visited) {
    for (Position child : p.children())
        postorder(child, visited);
    visited.push_back(p);
}

template <typename Position>
std::queue<Position> breadthfirst(Position p) {
    std::queue<Position> result;
    if (!p.is_null()) {
        std::queue<Position> fringe;
        fringe.push(p);                       // start exploring from p
        while (!fringe.empty()) {
            Position p = fringe.front();      // explore from front of queue
            result.push(p);
            fringe.pop();
            for (Position c : p.children())
                fringe.push(c);               // pushed to back of the queue
        }
    }
    return result;
}
    
             
}  // namespace dsac::tree
