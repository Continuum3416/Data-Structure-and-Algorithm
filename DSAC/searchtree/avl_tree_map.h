#pragma once
#include <functional>    // defines std::less
#include <cstdlib>       // provides abs
#include <stdexcept>
#include <utility>
#include <vector>

#include "tree_map.h"

namespace dsac::search_tree {

template <typename Key, typename Value, typename Compare=std::less<Key>>
class AVLTreeMap : public TreeMap<Key,Value,Compare> {
  protected:
    typedef TreeMap<Key,Value,Compare> Base;
    using Base::tree, Base::aux, Base::set_aux, typename Base::Node;
    
    /// Returns the height of the given node (nullptr is considered 0)
    int height(Node* p) const {
        return (p == nullptr ? 0 : aux(p));
    }

    /// Recomputes the height of the given position based on its children's heights
    void recompute_height(Node* p) {
        set_aux(p, 1 + std::max(height(p->left),height(p->right)));
    }

    /// Returns true if position has balance factor between -1 and +1 inclusive
    bool is_balanced(Node* p) const {
        return abs(height(p->left) - height(p->right)) <= 1;
    }

    /// Returns a child of p with height no smaller than that of the other child
    /// In case of tie, chooses the "aligned" child
    Node* taller_child(Node* p) {
        if (height(p->left) > height(p->right)) return p->left;  // clear winner
        if (height(p->left) < height(p->right)) return p->right; // clear winner
        // with equal height children, break tie while matching parent's orientation
        if (p == p->parent->left) return p->left;
        else return p->right;
    }

    /// Utility used to rebalance after an insertion or deletion.
    /// This traverses the path upward from p, performing a trinode
    /// restructuring when imbalance is found, continuing until
    /// balance is restored.
    void rebalance(Node* p) {
        int old_height, new_height;
        do {
            old_height = height(p);          // not yet recalculated if internal
            if (!is_balanced(p)) {           // imbalance detected
                // perform trinode restructuring, setting p to resulting root,
                // and recompute new local heights after the restructuring
                p = tree.restructure(taller_child(taller_child(p)));
                recompute_height(p->left);
                recompute_height(p->right);
            }
            recompute_height(p);
            new_height = height(p);
            p = p->parent;
        } while (old_height != new_height && p != tree.sentinel());
    }

    // Rebalances the tree immediately after inserting the given node
    void rebalance_insert(Node* p) { rebalance(p); }

    // Rebalances the the tree immediately after the deletion of a child of p
    void rebalance_delete(Node* p) {
        if (p != tree.sentinel())
            rebalance(p);
    }
};

} // namespace dsac::map
