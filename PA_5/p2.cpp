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
    //        / | \
    //       B  C  D
    //      / \  \
    //     E   F  G
    
    Node<char>* root = new Node<char>('A');
    root->children.push_back(new Node<char>('B'));
    root->children.push_back(new Node<char>('C'));
    root->children.push_back(new Node<char>('D'));

    root->children[0]->children.push_back(new Node<char>('E'));
    root->children[0]->children.push_back(new Node<char>('F'));

    root->children[1]->children.push_back(new Node<char>('G'));

    levelOrderTraversal(root);
    // g++ p2.cpp -o p2.exe; ./p2.exe
    return 0;
}