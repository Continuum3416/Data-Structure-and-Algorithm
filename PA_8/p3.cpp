#include <iostream>
#include "searchtree/tree_map.h"
#include "searchtree/avl_tree_map.h"
#include <string>

using namespace std;
using namespace dsac::search_tree;

string reverseKey(int key){
    string s = to_string(key);
    reverse(s.begin(), s.end());
    return s;
}

template<typename S, typename T>
void search(AVLTreeMap<S, T> tree_map, int key){
    auto it = tree_map.find(key);
    if(it != tree_map.end())
        cout << "Found: " << it->key() << " -> " << it->value() << endl;
    else
        cout << "Key " << key << " not found." << endl;
}

int main(){
    AVLTreeMap<int, string> tree_map;

    tree_map.put(10, reverseKey(10));
    tree_map.put(20, reverseKey(20));
    tree_map.put(4, reverseKey(4));
    tree_map.put(8, reverseKey(8));
    tree_map.put(15, reverseKey(15));
    tree_map.erase(8);
    tree_map.erase(10);

    for(auto it = tree_map.begin(); it != tree_map.end(); it++){
        cout << it->key() << "-> " << it->value() << endl;
    }

    search(tree_map, 15);
    search(tree_map, 30);
    search(tree_map, 8);
    // g++ p3.cpp -o p3.exe; ./p3.exe

    return 0;
}