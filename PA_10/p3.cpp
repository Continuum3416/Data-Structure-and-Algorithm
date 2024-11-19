#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unordered_map>
#include <map>
#include "priority/heap_priority_queue.h"
#include "tree/linked_binary_tree.h"

using namespace std;
using namespace dsac::tree;
using namespace dsac::priority;

class HuffmanTree {
public:
    struct HuffmanEntry {
        char character;
        int frequency;
        LinkedBinaryTree<char>* tree;

        HuffmanEntry(char c, int freq) : character(c), frequency(freq), tree(nullptr) {}
    };

    struct CompareHuffmanEntry {
        bool operator()(const HuffmanEntry& entry1, const HuffmanEntry& entry2) {
            return entry1.frequency > entry2.frequency; // Min-heap (smallest frequency at the top)
        }
    };

    LinkedBinaryTree<char> buildHuffmanTree(const string& text) {
        map<char, int> freq_map;
        for (char c : text) {
            freq_map[c]++;
        }

        cout << "Print map: " << endl;
        for(auto& entry : freq_map){
            cout << ((isspace(entry.first)) ? '_' : entry.first);
            cout << " -> " << entry.second << endl;
        }

        HeapPriorityQueue<HuffmanEntry, CompareHuffmanEntry> pq;
        for (const auto& entry : freq_map) {
            LinkedBinaryTree<char>* tree = new LinkedBinaryTree<char>();
            tree->add_root(entry.first);
            HuffmanEntry huff_entry(entry.first, entry.second);
            huff_entry.tree = tree;

            // insert T into Q with key f(c)
            pq.insert(huff_entry);
        }

        while (pq.size() > 1) {
            HuffmanEntry entry1 = pq.min();
            pq.remove_min();
            HuffmanEntry entry2 = pq.min();
            pq.remove_min();

            LinkedBinaryTree<char>* new_tree = new LinkedBinaryTree<char>();
            new_tree->add_root('*');
            new_tree->attach(new_tree->root(), *entry1.tree, *entry2.tree);

            HuffmanEntry new_entry('*', entry1.frequency + entry2.frequency);
            new_entry.tree = new_tree;
            pq.insert(new_entry);
        }

        HuffmanEntry final_entry = pq.min();
        return *final_entry.tree;
    }

};

int main() {
    string text = "more money needed";

    // Step 1: Create a Huffman tree from the given text
    HuffmanTree huffman;
    LinkedBinaryTree<char> huffmanTree = huffman.buildHuffmanTree(text);

    // Step 2: Print the number of characters and the Huffman tree
    cout << "Text: \"" << text << "\"" << endl;
    cout << "Number of characters: " << text.length() << endl;
    cout << "Huffman coding tree:" << endl;


    
    // Run: g++ p3.cpp -o p3.exe; ./p3.exe
    return 0;
}
