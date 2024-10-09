#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include "linked_binary_tree.cpp"

using namespace std;

int main(){
    //       A
    //     /   \
    //     B    C
    //    / \    \
    //    D  E    F
    //  /
    // G

    LinkedBinaryTree<char> oak_tree;
    oak_tree.add_root('A');
    
    oak_tree.add_left(oak_tree.root(), 'B');
    oak_tree.add_right(oak_tree.root(), 'C');

    oak_tree.add_left(oak_tree.root().left(), 'D');
    oak_tree.add_right(oak_tree.root().left(), 'E');

    oak_tree.add_right(oak_tree.root().right(), 'F');

    oak_tree.add_right(oak_tree.root().left().right(), 'G');

    cout << "\nPre Order Traversal: ";
    oak_tree.preOrderTraversal(oak_tree.root());

    cout << "\nPost Order Traversal: ";
    oak_tree.postOrderTraversal(oak_tree.root());

    cout << "\nIn Order Traversal: ";
    oak_tree.inOrderTraversal(oak_tree.root());

    cout << "\nLevel Order Traversal: ";
    oak_tree.levelOrderTraversal(oak_tree.root());


    // g++ p3_q2.cpp linked_binary_tree.cpp -o p3_q2.exe; ./p3_q2.exe
    return 0;
}