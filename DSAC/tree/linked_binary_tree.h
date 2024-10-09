#pragma once
#include "tree.h"
#include "binary_tree.h"

namespace dsac::tree {

template <typename E>
class LinkedBinaryTree {
  protected:
    //------ nested Node class ------
    class Node {
      public:                   // members public for convenience, as Node class is protected
        E element;
        Node* parent;
        Node* left{nullptr};
        Node* right{nullptr};

        Node(E e, Node* p = nullptr) : element{e}, parent{p} {}
    };  // end of Node class

    //------ data members of LinkedBinaryTree ------
    Node* rt{nullptr};
    int sz{0};

  public:
    //------ nested Position class ------
    class Position {
      private:
        Node* node;
        friend class LinkedBinaryTree;    // allow outer class access to node pointer
        
      public:
        Position(Node* nd = nullptr) : node{nd} {}
                 
        bool operator==(Position other) const { return node == other.node; }
        bool operator!=(Position other) const { return node != other.node; }

        bool is_null() const { return node == nullptr; }
        bool is_root() const { return node->parent == nullptr; }
        bool is_external() const { return node->left == nullptr && node->right == nullptr; }
        
        E& element() { return node->element; }                 // will allow element to be edited
        const E& element() const { return node->element; }
        Position parent() const { return Position(node->parent); }
        Position left() const { return Position(node->left); }
        Position right() const { return Position(node->right); }

        // conventions for positions of any tree types
        std::vector<Position> children() const {
            std::vector<Position> result;
            if (node->left != nullptr) result.push_back(Position(node->left));
            if (node->right != nullptr) result.push_back(Position(node->right));
            return result;
        }
        
        int num_children() const {
            int result{0};
            if (node->left != nullptr) result++;
            if (node->right != nullptr) result++;
            return result;
        }
    };  // end of Position class

    //------ member functions of LinkedBinaryTree ------

    /// Constructs a tree storing zero elements
    LinkedBinaryTree() {}       // empty tree

    /// Returns the number of elements stored in the tree
    int size() const { return sz; }

    /// Returns true if the tree does not have any elements
    bool empty() const { return sz == 0; }

    /// Returns a Position for the root (a null Position, if an empty tree)
    Position root() const { return Position(rt); }

    /// Returns an inorder sequence of positions
    std::vector<Position> positions() const {
        std::vector<Position> gather;
        if (rt) inorder(Position(rt), gather);
        return gather;
    }

    /// Creates a root for an empty tree, storing e as the element; should never be called on non-empty tree
    void add_root(const E& e = E()) {  // add root to (presumed) empty tree
        rt = new Node(e);
        sz = 1;
    }

    /// Creates a new node storing element e, and links the new node as the left child of position p.
    /// Should not be called if p already has a (non-null) left child.
    void add_left(Position p, const E& e) {
        p.node->left = new Node{e, p.node};           // parent of new node is p's node
        sz++;
    }
    
    /// Creates a new node storing element e, and links the new node as the right child of position p.
    /// Should not be called if p already has a (non-null) right child.
    void add_right(Position p, const E& e) {
        p.node->right = new Node{e, p.node};          // parent of new node is p's node
        sz++;
    }
    
    /// Removes the node (and element) at position p, replacing the node with its one child, if any.
    /// Should not be called on a node with two children.
    void erase(Position p) {
        Node* nd = p.node;
        Node* child{nd->left == nullptr ? nd->right : nd->left};  // lone child or else nullptr
        
        if (child != nullptr)
            child->parent = nd->parent;      // child's grandparent becomes parent

        if (nd == rt)
            rt = child;                      // child promoted to root
        else if (nd->parent->left == nd)     // node is left child of its parent
            nd->parent->left = child;
        else                                 // node is right child of its parent
            nd->parent->right = child;
        sz--;
        delete nd;
    }

    
    /// Attaches the internal structures of trees left and right and subtrees of leaf p,
    /// and resets left and right to empty trees. Should not be called on non-leaf p.
    void attach(Position p, LinkedBinaryTree& left, LinkedBinaryTree& right) {
        Node* nd = p.node;
        nd->left = left.rt;
        nd->right = right.rt;
        sz += left.sz + right.sz;

        // adjust parent pointers of old roots (if they exist)
        if (left.rt) left.rt->parent = nd;
        if (right.rt) right.rt->parent = nd;

        // reset other trees to an empty state
        left.sz = right.sz = 0;
        left.rt = right.rt = nullptr;
    }

    
  // ------------- Rule of five support ----------------
  private:
    void tear_down(Node* nd) {
        if (nd != nullptr) {
            tear_down(nd->left);
            tear_down(nd->right);
            delete nd;
        }
    }

    // Create cloned structure of model and return pointer to the new structure
    static Node* clone(Node* model) {
        if (model == nullptr) return nullptr;        // trivial clone
        Node* new_root{new Node(model->element)};
        new_root->left = clone(model->left);
        if (new_root->left) new_root->left->parent = new_root;
        new_root->right = clone(model->right);
        if (new_root->right) new_root->right->parent = new_root;
        return new_root;
    }
    
  public:
    // destructor
    ~LinkedBinaryTree() { tear_down(rt); }

    // copy constructor
    LinkedBinaryTree(const LinkedBinaryTree& other) : sz{other.sz}, rt{clone(other.rt)} {}

    // copy assignment
    LinkedBinaryTree& operator=(const LinkedBinaryTree& other) {
        if (this != &other) {        // bypass self-assignment
            tear_down(rt);
            rt = clone(other.rt);
            sz = other.sz;
        }
        return *this;
    }

    // move constructor
    LinkedBinaryTree(LinkedBinaryTree&& other) : sz{other.sz}, rt{other.rt} {
        // reset other to empty
        other.sz = 0;
        other.rt = nullptr;
    }

    // move assignment
    LinkedBinaryTree& operator=(LinkedBinaryTree&& other) {
        if (this != &other) {        // bypass self-assignment
            using std::swap;
            swap(sz, other.sz);
            swap(rt, other.rt);      // old structure will be destroyed by other
        }
        return *this;
    }
};

}  // namespace dsac::tree
