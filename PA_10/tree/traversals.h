// demonstrations of custom traversals

#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace dsac::tree {

/// Prints preorder representation of subtree rooted at p having depth d
template <typename Position>
void print_preorder_indent(Position p, int d = 0) {
    std::cout << std::string(2 * d, ' ') << p.element() << std::endl;       // indent based on d
    for (Position c : p.children())
        print_preorder_indent(c, d + 1);                     // child depth is d+1
}

/// Prints labeled representation of subtree rooted at p having depth d
template <typename Position>
void print_preorder_labeled(Position p, std::vector<int>& path) {
    int d = path.size();                                     // depth equals length of path
    std::cout << std::string(2 * d, ' ');                              // indent based on d
    // next print path numbers, joined by '.' and final trailing space (e.g. "1.3.2 ")
    for (int j = 0; j < d; j++) std::cout << path[j] << (j < d-1 ? '.' : ' ');
    std::cout << p.element() << std::endl;                             // now print the actual element
    path.push_back(1);                                       // add path label to denote child of p
    for (Position c : p.children()) {
        print_preorder_labeled(c, path);
        path[d]++;                                           // increment last label on path
    }
    path.pop_back();                                         // restore path to its incoming state
}

/// Prints parenthesized representation of subtree rooted at p
template <typename Position>
void parenthesize(Position p) {
    std::cout << p.element();
    if (!p.is_external()) {
        std::string preface{" ("};                           // opening parenthesis before first child
        for (Position c : p.children()) {
            std::cout << preface;
            preface = ", ";                                  // all further children preceded by comma
            parenthesize(c);                                 // recur on child
        }
        std::cout << ")";                                    // closing parenthesis after last child
    }
}

/// Returns total disk space of elements stored in subtree rooted at p
template <typename Position>
int disk_space(Position p) {
    int subtotal{p.element()};                               // we assume element represents space usage
    for (Position c : p.children())
        subtotal += disk_space(c);
    return subtotal;
}

/// Returns total disk space of elements stored in subtree rooted at p
/// d represents the known depth of p and x represents the next x-coordinate to be assigned
/// returns the greatest x-coordinate that was assigned
template <typename Position>
int layout(Position p, int d, int x) {
    if (!p.left().is_null())
        x = layout(p.left(), d + 1, x);                      // resulting x will be increased
    p.element().setX(x++);                                   // post-increment x
    p.element().setY(d);                                     // y is based upon depth
    if (!p.right().is_null())
        x = layout(p.right(), d + 1, x);                     // resulting x will be increased
    return x;
}
    
    
}  // namespace dsac::tree
