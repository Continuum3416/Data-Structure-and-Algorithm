#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include "linked_binary_tree.cpp"

using namespace std;

int main(){
    LinkedBinaryTree<char> oak_tree;
    oak_tree.add_root('A');
    
    oak_tree.add_left(oak_tree.root(), 'B');
    oak_tree.add_right(oak_tree.root(), 'C');

    oak_tree.add_left(oak_tree.root().left(), 'D');
    oak_tree.add_right(oak_tree.root().left(), 'E');

    oak_tree.add_right(oak_tree.root().right(), 'F');

    cout << "Post Order Traversal: ";
    oak_tree.postOrderTraversal(oak_tree.root());

    oak_tree.erase(oak_tree.root().right().right());
    cout << "\nIn Order Traversal: ";
    oak_tree.postOrderTraversal(oak_tree.root());


    // g++ p3.cpp linked_binary_tree.cpp -o p3.exe; ./p3.exe
    return 0;
}