#pragma once
#include <functional>    // defines std::less
#include <cstdlib>       // provides abs
#include <stdexcept>
#include <utility>
#include <vector>

#include "tree_map.h"

namespace dsac::search_tree {

template <typename Key, typename Value, typename Compare=std::less<Key>>
class RedBlackTreeMap : public TreeMap<Key,Value,Compare> {
  protected:
    typedef TreeMap<Key,Value,Compare> Base;
  public:
    using Base::size;
  protected:
    using Base::tree, Base::aux, Base::set_aux, typename Base::Node;

    // we use the inherited aux field with convention that 0=red and 1=black
    void make_black(Node* p) { set_aux(p, 1); }
    void make_red(Node* p) { set_aux(p, 0); }
    void set_color(Node* p, bool to_red) { set_aux(p, to_red ? 0 : 1); }
    bool is_black(Node* p) const { return aux(p) == 1; }
    bool is_red(Node* p) const { return p != nullptr && aux(p) == 0; }
    bool is_red_leaf(Node* p) const {
        return is_red(p) && p->left == nullptr && p->right == nullptr;
    }
    
    /// Return a red child of p (or nullptr, if no such child)
    Node* get_red_child(Node* p) {
        if (p->left != nullptr && is_red(p->left)) return p->left;
        if (p->right != nullptr && is_red(p->right)) return p->right;
        return nullptr;
    }
    
    Node* sibling(Node* p) {
        Node* parent = p->parent;
        return (p == parent->left ? parent->right : parent->left);
    }
    
    /// Remedies potential double-red violation above red p
    void resolve_red(Node* p) {
        if (p->parent == tree.sentinel())
            make_black(p);                                  // make root black
        else {
            Node* parent = p->parent;
            if (is_red(parent)) {                           // double-red problem
                Node* uncle = sibling(parent);
                if (!is_red(uncle)) {                       // Case 1: misshapen 4-node
                    Node* middle = tree.restructure(p);     // do trinode restructuring
                    make_black(middle);                     // and then fix colors
                    make_red(middle->left);
                    make_red(middle->right);
                } else {                                    // Case 2: overfull 5-node
                    Node* grand = parent->parent;
                    make_red(grand);                        // grandparent becomes red
                    make_black(grand->left);                // its children become black
                    make_black(grand->right);
                    resolve_red(grand);                     // recur at red grandparent
                }
            }
        }
    }
    
    // Rebalances the tree immediately after inserting the given node
    void rebalance_insert(Node* p) {
        resolve_red(p);                                     // new node is always initialized to red
    }

    // Resolve black deficit at z, where y is the root of z's heavier subtree
    void fix_deficit(Node* z, Node* y) {
        if (is_black(y)) {                                  // will apply Case 1 or 2
            Node* x = get_red_child(y);
            if (x != nullptr) {              // Case 1: y is black and has red child x; do "transfer"
                bool old_red = is_red(z);
                Node* middle = tree.restructure(x);
                set_color(middle, old_red);                 // middle gets old color of z
                make_black(middle->left);                   // children become black
                make_black(middle->right);
            } else {                         // Case 2: y is black, but no red children; recolor as "fusion"
                make_red(y);
                if (is_red(z))
                    make_black(z);                          // this resolves the problem
                else if (z->parent != tree.sentinel())
                    fix_deficit(z->parent, sibling(z));     // recur upward
            }
        } else {                             // Case 3: y is red; rotate misaligned 3-node and repeat
            tree.rotate(y);
            make_black(y);
            make_red(z);
            fix_deficit(z, (z == y->right ? z->left : z->right));
        }
    }
    
    // Rebalances the the tree immediately after the deletion of a child of p
    void rebalance_delete(Node* p) {
        if (p == tree.sentinel()) {
            if (size() == 1)
                make_black(tree.sentinel()->left);          // special case: ensure root is black
        } else {
            int n{0};                                       // count number of children
            if (p->left != nullptr) n++;
            if (p->right != nullptr) n++;
            if (n == 1) {                                   // deficit exists unless child is a red leaf
                Node* c = (p->left != nullptr ? p->left : p->right);
                if (!is_red_leaf(c))
                    fix_deficit(p, c);
            } else if (n == 2) {
                if (is_red_leaf(p->left))
                    make_black(p->left);
                else
                    make_black(p->right);
            }
        }
    }

  /*
  // ------------ debugging follows ------------
  public:
    int sanity_recurse(Node* p) {
        if (p == nullptr) return 0;  // black depth 0
        if (p->parent == tree.sentinel() && is_red(p)) return -1;  // root must be black
        if (is_red(p) && (is_red(p->left) || (is_red(p->right)))) return -1;  // double red

        int a = sanity_recurse(p->left);
        if (a == -1) return -1;
        int b = sanity_recurse(p->right);
        if (a != b) return -1;             // subtree must have same black depth

        return a + (is_red(p) ? 0 : 1);    // p's black depth
    }
    
    bool sanity_check() {
        if (sanity_recurse(tree.sentinel()->left) == -1) {
            std::cout << "VIOLATION of RB tree properties" << std::endl;
            Base::_dump();
            return false;
        } else
            return true;
    }
  */
    
};

} // namespace dsac::map
