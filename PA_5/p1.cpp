#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template<typename T> struct Node {
    T data;
    vector<Node<T>*> children;

    Node(T data) {
        this->data = data;
    }
};


template<typename T> void preorderTraversal(Node<T>* root){
    if(root == nullptr)
        return;
    
    stack<Node<T>*> node_stack;
    node_stack.push(root);

    while(!node_stack.empty()){
        Node<T>* current = node_stack.top();
        node_stack.pop();

        cout << current->data << " ";

        for(int i = current->children.size() - 1; i >= 0; i--)
            node_stack.push(current->children[i]);
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

    preorderTraversal(root);
    // g++ p1.cpp -o p1.exe; ./p1.exe
    return 0;
}