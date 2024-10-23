#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include <cctype>
#include <unordered_set>
#include "hashtable.h" 
using namespace std;


// Function to compute cyclic shift hash code
unsigned long long cyclic(const string &word, int shift) {
    unsigned long long hash_value = 0;
    for (char c : word) 
    {
        hash_value = (hash_value << shift) ^ c;  // Shift and XOR with character
    }
    return hash_value;
}


template <typename Key, typename Value>
pair<int, int> count_collisions(const vector<string> &words, int shift) {
    ChainHashMap<Key, Value> hash_map;
    unordered_set<string> uni_wd;
    int collisions = 0;

    for (const auto &word : words) {
        if (uni_wd.find(word) != uni_wd.end()) {
            continue; // Skip already seen words
        }
        uni_wd.insert(word);

        unsigned long long hash_value = cyclic(word, shift);
        int bucket_count = hash_map.table_size(); // Get the current number of buckets

        // Prevent arithmetic exception
        if (bucket_count == 0) {
            continue; // Or handle it appropriately (e.g., break or throw an error)
        }

        int bucket_index = hash_value % bucket_count; // Use the current bucket count

        // Check if the bucket already has elements
        if (hash_map.bucket_size(bucket_index) > 0) {
            collisions++; // Increment collisions since this bucket already has an entry
        }

        hash_map.put(word, 1); // Use a dummy value
    }

    return {uni_wd.size(), collisions};
}


int main() {
    string filename = "USDeclIndFormatted.txt"; 
    string word;
    
    ifstream file(filename);
    vector<string> words;
    

    while (file >> word) 
    {
        transform(word.begin(), word.end(), word.begin(),[](unsigned char c){ return std::tolower(c); });
        if (!word.empty()) 
        {
            words.push_back(word);
        }
    }


    // Shift values for cyclic shift hash codes
    vector<int> shift_values = {0, 1, 5, 13};

    // Store results
    for (int shift : shift_values) {
        auto [unique_count, collision_count] = count_collisions<string, int>(words, shift);
        cout << "Shift = " << shift << ": Unique words = " << unique_count << ", Collisions = " << collision_count << endl;
    }

    // g++ p3.cpp -o p3.exe; ./p3.exe
    return 0;
}