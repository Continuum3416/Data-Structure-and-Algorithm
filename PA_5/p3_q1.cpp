#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

template<typename T> struct Node {
    T data;
    vector<Node<T>*> children;

    Node(T data) {
        this->data = data;
    }
};


template<typename T> void postOrderTraversal(Node<T>* root) {
    if (root == nullptr)
        return;

    for (auto child : root->children) {
        postOrderTraversal(child);
    }
    cout << root->data << " ";
}

template<typename T> void preOrderTraversal(Node<T>* root) {
    if (root == nullptr)
        return;

    cout << root->data << " ";

    for (auto child : root->children) {
        preOrderTraversal(child);
    }
}

template<typename T> void levelOrderTraversal(Node<T>* root){
    if(root == nullptr)
        return;
    
    queue<Node<T>*> node_queue;
    node_queue.push(root);

    while(!node_queue.empty()){
        Node<T>* current = node_queue.front();
        node_queue.pop();

        cout << current->data << " ";

        // push n children
        for(int i = 0; i < current->children.size(); i++)
            node_queue.push(current->children[i]);
    }
    return;
}

int main(){
    //          A
    //        / |  \
    //       B  C    D
    //      / \    / | \
    //     E   F  G  H  I
    
    Node<char>* root = new Node<char>('A');
    root->children.push_back(new Node<char>('B'));
    root->children.push_back(new Node<char>('C'));
    root->children.push_back(new Node<char>('D'));

    root->children[0]->children.push_back(new Node<char>('E'));
    root->children[0]->children.push_back(new Node<char>('F'));

    root->children[2]->children.push_back(new Node<char>('G'));
    root->children[2]->children.push_back(new Node<char>('H'));
    root->children[2]->children.push_back(new Node<char>('I'));

    cout << "Preorder Traversal: ";
    preOrderTraversal(root);

    cout << "\nPostorder Traversal: ";
    postOrderTraversal(root);

    cout << "\nLevel-order Traversal: ";
    levelOrderTraversal(root);

    // g++ p3_q1.cpp -o p3_q1.exe; ./p3_q1.exe
    return 0;
}