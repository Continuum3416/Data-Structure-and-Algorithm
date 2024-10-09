#pragma once
#include <functional>    // defines std::less
#include <stdexcept>
#include <utility>
#include <vector>

#include "map/abstract_map.h"
#include "tree/linked_binary_tree.h"

namespace dsac::search_tree {

template <typename Key, typename Value, typename Compare=std::less<Key>>
class TreeMap : public dsac::map::AbstractMap<Key,Value> {
  protected:
    typedef dsac::map::AbstractMap<Key,Value> Base;           // shorthand for the base class

  public:
    using Base::empty, Base::erase, typename Base::Entry, typename Base::const_iterator;
    
  protected:

    /// ------------ nested BalanceableBinaryTree class -------------------
    /// A specialized version of the LinkedBinaryTree class with additional mutators to
    /// support binary search tree operations, and with the tree element type storing
    /// an additional auxiliary instance variable for balancing data.
    typedef std::pair<Entry,int> BSTEntry;                  // include auxiliary int for balancing info
    typedef dsac::tree::LinkedBinaryTree<BSTEntry> TreeBase;
    class BalanceableBinaryTree : public TreeBase {
      public:
        friend TreeMap;
        using TreeBase::rt, typename TreeBase::Node;

        // the root node that serves as the end() sentinel
        Node* sentinel() const { return TreeBase::rt; }

        // link child (possibly nullputr) to the indicated side of the parent
        void relink(Node* parent, Node* child, bool make_left_child) {
            if (make_left_child)
                parent->left = child;
            else
                parent->right = child;
            if (child != nullptr)
                child->parent = parent;
        }
        
        /// Rotates non-root node x above its parent.
        /// Switches between these configurations, depending on whether
        /// x=a or x=b in the following:
        ///
        ///         b                  a
        ///        / \                / \
        ///       a  t2             t0   b
        ///      / \                    / \
        ///     t0  t1                 t1  t2
        void rotate(Node* x) {
            Node* y = x->parent;         // we assume parent exists within the tree map
            Node* z = y->parent;         // grandparent (possibly the sentinel)
            relink(z, x, y == z->left);     // x becomes direct child of z
            // now rotate x and y, including transfer of middle subtree
            if (x == y->left) {
                relink(y, x->right, true);  // x's right child becomes y's left child
                relink(x, y, false);        // y becomes x's right child
            } else {
                relink(y, x->left, false);  // x's left child becomes y's right child
                relink(x, y, true);         // y becomes left child of x
            }
        }

        /// Performs a trinode restructuring of Node x with its parent/grandparent.
        /// Returns the Node that becomes the root of the restructured subtree.
        ///
        ///
        /// Assumes the nodes are in one of the following configurations:
        ///
        ///     z=a                 z=c           z=a               z=c
        ///    /  \                /  \          /  \              /      \
        ///   t0  y=b             y=b  t3       t0   y=c          y=a  t3
        ///      /  \            /  \               /  \         /        \
        ///     t1  x=c         x=a  t2            x=b  t3      t0   x=b
        ///        /  \        /  \               /  \              /     \
        ///       t2  t3      t0  t1             t1  t2            t1  t2
        ///
        /// The subtree will be restructured so that the node with key b becomes its root.
        ///
        ///           b
        ///         /   \
        ///       a       c
        ///      / \     / \
        ///     t0  t1  t2  t3
        Node* restructure(Node* x) {
            Node* y = x->parent;
            Node* z = y->parent;
            if ((x == y->right) == (y == z->right)) {                // matching alignments
                rotate(y);                                           // single rotation (of y)
                return y;                                            // y is new subtree root
            } else {                                                 // opposite alignments
                rotate(x);                                           // double rotation (of x)
                rotate(x);
                return x;                                            // x is new subtree root
            }
        }
    }; // --------- end of nested BalanceableBinaryTree class ------------
    typedef typename BalanceableBinaryTree::Node Node;
    typedef typename BalanceableBinaryTree::Position Position;

    // hooks for balanced search tree operations

    // Rebalances the tree after an access to the given node
    virtual void rebalance_access(Node*) { }
    
    // Rebalances the tree immediately after inserting the given node
    virtual void rebalance_insert(Node*) { }

    // Rebalances the the tree immediately after the deletion of a child of p
    virtual void rebalance_delete(Node*) { }


    // instance variables for a TreeMap
    BalanceableBinaryTree tree; 
    Compare less_than;                          // determines "a < b" relationship among keys

    Key key(Node* nd) const { return nd->element.first.key(); }
    int aux(Node* nd) const { return nd->element.second; }
    void set_aux(Node* nd, int value) { nd->element.second = value; }
    
    bool equals(Key a, Key b) const {           // equality based on the less_than comparator
        return (!less_than(a,b) && !less_than(b,a));
    }
   
    // Return pointer to node storing key k, or the last node on a failed search
    Node* search(Key k) const {
        if (empty()) return tree.rt;
        Node* walk = tree.rt->left;                      // start to the left of end sentinel
        while (true) {
            if (less_than(k, key(walk))) {               // consider left subtree
                if (walk->left == nullptr) return walk;  //     failed search
                walk = walk->left;                       //     continue at left child
            } else if (less_than(key(walk), k)) {        // consider right subtree
                if (walk->right == nullptr) return walk; //     failed search
                walk = walk->right;                      //     continue at right child
            } else {
                return walk;                             // successful match for key
            }
        }
    }
    
    // return the inorder successor of position p
    static Node* successor(Node* p)  {
        if (p->right == nullptr) {         // no right subtree so look upward
            while (p == p->parent->right)
                p = p->parent;
            return p->parent;      // original p was max of left subtree of returned
        } else {
            // find smallest entry in right subtree
            p = p->right;
            while (p->left != nullptr)
                p = p->left;
            return p;
        }
    }
        
    // a position within our map is described by a node pointer
    using typename Base::abstract_iter_rep, Base::get_rep;
    class iter_rep : public abstract_iter_rep {              // specialize abstract version
      public:
        Node* node;
        iter_rep(Node* nd) : node{nd} {}

        const Entry& entry() const { return node->element.first; }
        void advance() { node = successor(node); }
        abstract_iter_rep* clone() const { return new iter_rep(node); }
        bool equals(const abstract_iter_rep* other) const {
            const iter_rep* p = dynamic_cast<const iter_rep*>(other);   // cast abstract argument to our iter_rep
            return p != nullptr && node == p->node;
        }
    };  //------- end of class iter_rep --------
    
  public:
    /// Creates an empty map
    TreeMap() {
        tree.add_root();            // root serves as our end() position; entry irrelevant
    }
    
    /// Returns the number of entries in the map
    int size() const { return tree.size() - 1;  }   // disregard the end sentinel

    /// Returns a const_iterator to first entry
    const_iterator begin() const {
        Node* walk = tree.sentinel();
        while (walk->left != nullptr)
            walk = walk->left;
        return const_iterator(new iter_rep(walk));
    }

    /// Returns a const_iterator representing the end
    const_iterator end() const { return const_iterator(new iter_rep(tree.rt)); }

    /// Returns a const_iterator to the entry with a given key, or end() if no such entry exists
    const_iterator find(const Key& k) const {
        if (empty()) return end();
        Node* p{search(k)};
        const_cast<TreeMap*>(this)->rebalance_access(p);                  // find could trigger rebalance of tree
        if (equals(k, key(p)))                                            // exact match
            return const_iterator(new iter_rep(p));
        else                                                              // unsuccessful search
            return end();
    }

    /// Associates given key with given value. If key already exists previous value is overwritten.
    /// Returns a const_iterator to the entry associated with the key
    const_iterator put(const Key& k, const Value& v) {
        Node* p{search(k)};
        if (p != tree.rt && equals(k, key(p))) {                          // exact match
            p->element.first.value() = v;                                 // update entry's value
            rebalance_access(p);
        } else {                                                          // unsuccessful search
            if (p == tree.rt || less_than(k, key(p))) {
                tree.add_left(Position(p), {{k,v},0});
                p = p->left;
            } else {
                tree.add_right(Position(p), {{k,v},0});
                p = p->right;
            }
            rebalance_insert(p);
        }
        return const_iterator(new iter_rep(p));
    }

    /// Removes the entry indicated by the given iterator, and returns const_iterator to next entry in iteration order
    const_iterator erase(const_iterator loc) {
        Node* p = dynamic_cast<iter_rep*>(get_rep(loc))->node;
        if (p->left != nullptr && p->right != nullptr) {         // p has two children
            Node* before = p->left;
            while (before->right != nullptr)
                before = before->right;
            p->element.first = before->element.first;            // move predecessor's entry to p
            p = before;                                          // and now consider deleting predecessor
        }
        // now p has at most one child
        Node* parent = p->parent;
        Node* after = successor(p);
        tree.erase(Position(p));                                 // inherited from LinkedBinaryTree
        rebalance_delete(parent);
        return const_iterator(new iter_rep(after));
    }
    
    /// Returns a const_iterator to the first entry with key greater than or equal to k, or end() if no such entry exists
    const_iterator lower_bound(const Key& k) const {
        if (empty()) return end();
        Node* p{search(k)};
        if (less_than(key(p), k))      // unsuccessful search ended at leaf with smaller key
            p = successor(p);
        return const_iterator(new iter_rep(p));
    }
    
    /// Returns a const_iterator to the first entry with key strictly greater than k, or end() if no such entry exists
    const_iterator upper_bound(const Key& k) const {
        if (empty()) return end();
        Node* p{search(k)};
        if (!less_than(k, key(p)))     // need entry with strictly greater key
            p = successor(p);
        return const_iterator(new iter_rep(p));
    }


    //----------- remainder for debugging only -----------
    static void _dumpNode(Node* p)  {
        std::cout << p->element.first.key() << "(" << p->element.second << "):" << p->element.first.value();
    }
    
    static void _dump(Node* p, int depth) {
        if (p) {
            _dump(p->left, 1+depth);
            std::cout << std::string(2*depth,' ');
            _dumpNode(p);
            std::cout << std::endl;
            _dump(p->right, 1+depth);
        }
    }
    
    /// used for debugging only
    void _dump() const {
        std::cout << std::string(30,'-') << std::endl;
        _dump(tree.sentinel()->left, 0);
        std::cout << std::string(30,'-') << std::endl;
    }
    
};

} // namespace dsac::map
