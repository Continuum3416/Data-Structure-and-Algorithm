#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "map/chain_hash_map.h"

using namespace std;

// read data from file and populate hash map, counting probes
// Count probes during insertion
int countProbesAndInsert(ChainHashMap<int, string>& chainMap, int key, const string& value, int tableSize) {
    std::hash<int> hashFunc;
    int hash = hashFunc(key) % tableSize; // Hashing the key
    int probes = 1;

    // Check if the key exists in the chain map
    if (chainMap.find(key) != chainMap.end()) {
        probes++; // Increment probes if the key is found
    }

    // Insert the key-value pair
    chainMap.put(key, value); 
    return probes;
}

void readData(const string& filename, ChainHashMap<int, string>& hashMap, double loadFactor) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    int N;
    file >> N; // number of records
    int tableSize = static_cast<int>(N / loadFactor) + 1;
    cout << "Table Size (before initialization): " << tableSize << endl;
    hashMap = ChainHashMap<int, string>(tableSize); // Initialize hash map with calculated size

    int totalProbes = 0;
    int maxProbes = 0;
    string line;
    file.ignore(); // Ignore the newline after reading N

    while (getline(file, line)) {
        stringstream ss(line);
        int key;
        string value;

        ss >> key; // county/state code
        ss.ignore(); // Ignore the comma after key
        getline(ss, value);
        value.erase(remove(value.begin(), value.end(), '"'), value.end()); // Remove quotes if necessary

        int currentProbes = countProbesAndInsert(hashMap, key, value, tableSize);
        totalProbes += currentProbes;
        if (currentProbes > maxProbes) {
            maxProbes = currentProbes;
        }
    }

    file.close();

    double averageProbes = static_cast<double>(totalProbes) / N;
    cout << "Final Table Size: " << hashMap.size() << endl;
    cout << "Total Number of Probes: " << totalProbes << endl;
    cout << "Maximum Probes for Worst Case: " << maxProbes << endl;
    cout << "Average Number of Probes: " << averageProbes << endl;
}




int main() {
    string filename = "popLarge.txt";

    // cout << "Enter file name: "; cin >> filename;

    vector<double> loadFactors = {0.25, 0.5, 0.75};
    for (double loadFactor: loadFactors) { 
        ChainHashMap<int, string> hashMap;
        readData(filename, hashMap, loadFactor);
        cout << "Load Factor: " << loadFactor << endl;
    }

    // g++ ec.cpp -o ec.exe; ./ec.exe
    return 0;
}
