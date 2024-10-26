#pragma once
#include <functional>    // defines std::less
#include <cstdlib>       // provides abs
#include <stdexcept>
#include <utility>
#include <vector>

#include "tree_map.h"

namespace dsac::search_tree {

template <typename Key, typename Value, typename Compare=std::less<Key>>
class SplayTreeMap : public TreeMap<Key,Value,Compare> {
  protected:
    typedef TreeMap<Key,Value,Compare> Base;
    using Base::tree, typename Base::Node;

    void splay(Node* p) {
        while (p->parent != tree.sentinel()) {
            Node* parent = p->parent;
            Node* grand = parent->parent;
            if (grand == tree.sentinel()) {                               // zig case
                tree.rotate(p);
            } else if ((parent == grand->left) == (p == parent->left)) {  // zig-zig case
                tree.rotate(parent);       // move PARENT up
                tree.rotate(p);            // then move p up
            } else {                                                      // zip-zag case
                tree.rotate(p);            // move p up
                tree.rotate(p);            // move p up again
            }
        }
    }

    // Rebalances the tree immediately after inserting the given node
    void rebalance_access(Node* p) { splay(p); }

    // Rebalances the tree immediately after inserting the given node
    void rebalance_insert(Node* p) { splay(p); }

    // Rebalances the the tree immediately after the deletion of a child of p
    void rebalance_delete(Node* p) {
        if (p != tree.sentinel()) splay(p);
    }
};

} // namespace dsac::map
