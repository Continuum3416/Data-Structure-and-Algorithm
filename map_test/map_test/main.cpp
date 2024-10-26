#include <iostream>
#include "map.h"
#include <fstream>
#include <sstream>
#include <chrono> // For time measurement
#include <string>
#include <algorithm> // For reverse
#include <iomanip>

using namespace std;
using namespace std::chrono;

string reverseKey(int key) {
    string s = to_string(key);
    reverse(s.begin(), s.end());
    return s;
}

void insertAndMeasure(const string& filename, int table_size) {
    ChainHashMap<int, string> chain_map;
    chain_map.resize(table_size);
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Error: File '" + filename + "' not found or unable to open.");
        return;
    }

    int value;
    auto start = high_resolution_clock::now();
    while (file >> value) {
        chain_map.put(value, reverseKey(value));
    }
    auto end = high_resolution_clock::now();
    auto duration_ms = duration_cast<duration<double, milli>>(end - start);

    cout << "Runtime: " << setprecision(6) << duration_ms.count() << " ms" << endl;
    return;
}

void search(ChainHashMap<int, string>& map, int target) {
    auto it = map.find(target);
    if (it != map.end())
        cout << target << " was found: " << it->key() << " -> " << it->value() << endl;
    else
        cout << target << " not found" << endl;
    return;
}

int main() {
    ChainHashMap<int, string> chain_map;

    chain_map.put(13, reverseKey(13));
    chain_map.put(21, reverseKey(21));
    chain_map.put(5, reverseKey(5));
    chain_map.put(37, reverseKey(37));
    chain_map.put(15, reverseKey(15));

    search(chain_map, 10);
    search(chain_map, 21);

    chain_map.erase(20);
    chain_map.erase(37);

    search(chain_map, 37);

    cout << "\nEntries in the map: \n";
    //for (auto it = chain_map.begin(); it != chain_map.end(); ++it) {
        //cout << "(" << it->key() << ", " << it->value() << ")" << endl;
    //}

    //cout << "\nsmall1k.txt: " << endl;
    // insertAndMeasure("D:/map_txt/small1k.txt", 2 * 1000 + 1);
    //cout << '\n';

    //cout << "large100k.txt " << endl;
    //insertAndMeasure("large100k.txt", 2 * 100000 + 1);

    // g++ p2.cpp -o p2.exe; ./p2.exe
    return 0;
}