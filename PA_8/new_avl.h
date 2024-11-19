#pragma once
#include <functional>    // defines std::less
#include <cstdlib>       // provides abs
#include <stdexcept>
#include <utility>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

namespace dsac::search_tree {

template <typename Key, typename Value, typename Compare=std::less<Key>>
class AVLTreeMap {
protected:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        Node* parent;
        int height;

        Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* p) const {
        return (p == nullptr ? 0 : p->height);
    }

    void update_height(Node* p) {
        p->height = 1 + std::max(height(p->left), height(p->right));
    }

    int balance_factor(Node* p) const {
        return height(p->left) - height(p->right);
    }

    void rotate_left(Node*& p) {
        Node* q = p->right;
        p->right = q->left;
        q->left = p;
        update_height(p);
        update_height(q);
        p = q;
    }

    void rotate_right(Node*& p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        update_height(p);
        update_height(q);
        p = q;
    }

    void rebalance(Node*& p) {
        update_height(p);
        if (balance_factor(p) == 2) {
            if (balance_factor(p->left) < 0) rotate_left(p->left); // Left-Right case
            rotate_right(p); // Left-Left case
        } else if (balance_factor(p) == -2) {
            if (balance_factor(p->right) > 0) rotate_right(p->right); // Right-Left case
            rotate_left(p); // Right-Right case
        }
    }

    void insert(Node*& p, const Key& key, const Value& value) {
        if (p == nullptr) {
            p = new Node(key, value);
            return;
        }
        if (key < p->key) {
            insert(p->left, key, value);
            p->left->parent = p;
        } else if (key > p->key) {
            insert(p->right, key, value);
            p->right->parent = p;
        } else {
            p->value = value; // Update existing key
        }
        rebalance(p);
    }

public:
    AVLTreeMap() : root(nullptr) {}

    void put(const Key& key, const Value& value) {
        insert(root, key, value);
    }

    Node* get_root() const {
        return root;
    }

    // For drawing the tree
    void draw(Node* node, int level) const {
        if (node == nullptr) {
            return;
        }
        // Print the current node
        std::cout << std::setw(level * 5) << node->key << std::endl;

        // Print the left and right children with increased indentation
        draw(node->left, level + 1);
        draw(node->right, level + 1);
    }

    void display() const {
        draw(root, 0);
    }
};

} // namespace dsac::search_tree
