#include <iostream>
#include <unordered_map>
#include <memory>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include "priority/heap_priority_queue.h"
#include "tree/linked_binary_tree.h"

using namespace std;
using namespace dsac::tree;
using namespace dsac::priority;




class Huffman {
private:
    struct HuffmanNode {

        char character;
        int frequency;
        LinkedBinaryTree<pair<char, int>> tree;

        // Constructor for leaf nodes
        HuffmanNode(char c, int freq) : character(c), frequency(freq) {
            tree.add_root({c, freq});
        }

        // Constructor for internal nodes
        HuffmanNode(int freq, HuffmanNode* left, HuffmanNode* right) : character('*'), frequency(freq) {
            tree.add_root({'*', freq});
            tree.attach(tree.root(), left->tree, right->tree);
        }

        // Overload less-than
        bool operator < (const HuffmanNode& other) const {
            return frequency < other.frequency;
        }
    };



public:
    unordered_map<char, int> freq_map;
    string encoded_message_bits;

    void generateHuffmanTree(const string& text) {
        // Step 1: Preprocess text and calculate frequencies
        for (char c : text) {
            if (c == ' ') c = '_';
            freq_map[c]++;
        }

        // Step 2: Initialize priority queue
        HeapPriorityQueue<HuffmanNode> pq;

        // Step 3: Insert all characters into the priority queue
        for (const auto& [character, frequency] : freq_map) {
            pq.insert(HuffmanNode(character, frequency));
        }

        // Step 4: Build the Huffman tree
        while (pq.size() > 1) {
            HuffmanNode* left = new HuffmanNode(pq.min());
            pq.remove_min();

            HuffmanNode* right = new HuffmanNode(pq.min());
            pq.remove_min();

            HuffmanNode combined(left->frequency + right->frequency, left, right);
            pq.insert(combined);

            // Free temporary nodes
            delete left;
            delete right;
        }

        // Final Huffman tree
        HuffmanNode root = pq.min();
        pq.remove_min();


        generate_encodings(root.tree, root.tree.root(), "");

        // Output
        cout << "Text: \"" << text << "\"\n";
        cout << "Number of characters: " << text.size() << "\n";
        cout << "Huffman coding tree:\n";
        print_tree(root.tree, root.tree.root());

        // Store tree
        this->root = root.tree.root();

        printEncodingTable(text);
    }

    
    void printEncodingTable(const string& text){
        cout << "\nChar Frequency Encoded bits\n";
        for (const auto& [character, encoding] : encodings) {
            cout << character << "    " << freq_map[character] << "         " << encoding << "\n";
        }


        int total_bits = 0;
        
        for (char c : text) {
            if (c == ' ') c = '_';
            encoded_message_bits += encodings[c];
            total_bits += encodings[c].size();
        }
        cout << "Number of bits to encode message: " << total_bits << "\n";
        cout << encoded_message_bits << "\n";
    }

    // Decode the encoded bits back into the original text
    string decode(const string& encodedBits) {
        string decodedText = "";
        LinkedBinaryTree<pair<char, int>>::Position currentNode = this->root;

        for (char bit : encodedBits) {
            if (bit == '0')
                currentNode = currentNode.left();
            else if (bit == '1')
                currentNode = currentNode.right();

            // If a leaf node is reached, add the character to the decoded text
            if (currentNode.is_external()) {
                decodedText += currentNode.element().first;
                currentNode = this->root;
            }
        }

        return decodedText;
    }

private:
    unordered_map<char, string> encodings;
     // Generate Huffman encodings recursively
    void generate_encodings(const LinkedBinaryTree<pair<char, int>>& tree,
                            LinkedBinaryTree<pair<char, int>>::Position pos,
                            const string& code) {
        if (pos.is_null()) return;

        if (pos.left().is_null() && pos.right().is_null()) {
            char character = pos.element().first;
            encodings[character] = code;
            return;
        }

        generate_encodings(tree, pos.left(), code + "0");
        generate_encodings(tree, pos.right(), code + "1");
    }

    // print tree using preorder
    void print_tree(const LinkedBinaryTree<pair<char, int>>& tree, LinkedBinaryTree<pair<char, int>>::Position pos, int depth = 0) {
        if (pos.is_null()) return;

        cout << string(depth * 4, ' ') << pos.element().second << " " << pos.element().first << "\n";

        print_tree(tree, pos.left(), depth + 1);
        print_tree(tree, pos.right(), depth + 1);
    }

    LinkedBinaryTree<pair<char, int>>::Position root;
};


void testDrive(string text){
    Huffman huffman;
    huffman.generateHuffmanTree(text);

    string encodedBits = huffman.encoded_message_bits;

    string decodedText = huffman.decode(encodedBits);
    cout << "Decoded Text: \"" << decodedText << "\"\n";
}


int main() {
    cout << "Test case 1: " << endl;
    testDrive("more money needed"); // "011000001111010011000101110010010101111110011100"


    cout << "\nTest case 2: " << endl;
    testDrive("aaabbb");

    return 0;
}

// Run: g++ p3_1.cpp -o p3_1.exe; ./p3_1.exe

