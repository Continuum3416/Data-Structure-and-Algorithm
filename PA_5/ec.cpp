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


template<typename T> void postOrderTransversal(Node<T>* root){
    if(root == nullptr)
        return;
    
    stack<Node<T>*> node_stack_1, node_stack_2;
    node_stack_1.push(root);

    while(!node_stack_1.empty()){
        Node<T> *current = node_stack_1.top();
        node_stack_1.pop();
        node_stack_2.push(current);

        // push n children
        for(int i = 0; i < current->children.size(); i++)
            node_stack_1.push(current->children[i]);
    }

    while(!node_stack_2.empty()){
        cout << node_stack_2.top() -> data << " ";
        node_stack_2.pop();
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


    postOrderTransversal(root);
    // g++ ec.cpp -o ec.exe; ./ec.exe
    return 0;
}