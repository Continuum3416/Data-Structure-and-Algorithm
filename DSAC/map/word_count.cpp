#include <cstdlib>
#include <iostream>

#include "probe_hash_map.h"

using namespace std;
using namespace dsac::map;
#define Map ProbeHashMap

int main() {
    Map<string,int> freq;             // maps strings to count of occurrences
    string word;
    while (cin >> word) {             // continue reading until ctrl-D
        int count{1};                 // count for this occurrence
        if (freq.contains(word))
            count += freq.at(word);   // and previous occurrences
        freq.put(word, count);
    }

    int max_count{0};
    string max_word{""};
    for (Map<string,int>::Entry entry : freq) {
        if (entry.value() > max_count) {
            max_count = entry.value();
            max_word = entry.key();
        }
    }
    
    cout << "The most frequent word is '" << max_word
         << "' with " << max_count << " occurrences." << endl;
}
