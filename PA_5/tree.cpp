#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template<typename T> struct Node {
    T data;
    Node* left;
    Node* right;

    Node(T data){
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};


int main(){
    // Creating nodes with template type `int`
    Node<int>* root = new Node<int>(1);  // root node with value 1
    root->left = new Node<int>(2);  // left child of root
    root->right = new Node<int>(3); // right child of root
    root->left->left = new Node<int>(4);  // left child of node 2
    root->left->right = new Node<int>(5); // right child of node 2

    // The structure of the tree is now:
    //        1
    //      /   \
    //     2     3
    //    / \
    //   4   5

    cout << "Root Node: " << root->data << endl;
    cout << "Left Child of Root: " << root->left->data << endl;
    cout << "Right Child of Root: " << root->right->data << endl;
    cout << "Left Child of Node 2: " << root->left->left->data << endl;
    cout << "Right Child of Node 2: " << root->left->right->data << endl;
    // g++ tree.cpp -o tree.exe; ./tree.exe
    return 0;
}