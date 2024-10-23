#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include <algorithm> // reverse
#include <iomanip>

using namespace std;
using namespace std::chrono;

string reverseKey(int key){
    string s = to_string(key);
    reverse(s.begin(), s.end());
    return s;
}

void search(unordered_map<int, string>& map, int target){
    if(map.find(target) != map.end())
        cout << "Found "<< target << ": " << target << " -> " << map[target] << endl;
    else
        cout << target << " not found" << endl;
    return;
}

void insertAndMeasure(const string &filename, int table_size){
    unordered_map<int, string> map;
    map.reserve(table_size); 
    ifstream file(filename);

    int value;
    auto start = high_resolution_clock::now();
    while(file >> value){
        map[value] = reverseKey(value);
    }
    auto end = high_resolution_clock::now();
    auto duration_ms = duration_cast<duration<double, milli>>(end - start);

    cout << "Runtime: " << setprecision(6) << duration_ms.count() << " ms" << endl;
    return;
}

int main(){
    unordered_map<int, string> map;

    map[13] = reverseKey(13); // 13 -> "31"
    map[21] = reverseKey(21);
    map[5] = reverseKey(5);
    map[37] = reverseKey(37);
    map[15] = reverseKey(15);

    search(map, 10);
    search(map, 21);

    map.erase(20);
    map.erase(37);

    search(map, 37);

    cout << "\nEntries in the map: \n";
    for(auto &entry : map)
        cout << "(" << entry.first << " -> " << entry.second << ")" << endl; 
    
    cout << "\nsmall1k.txt: " << endl;
    insertAndMeasure("small1k.txt", 2 * 1000 + 1);
    cout << '\n';

    cout << "large100k.txt " << endl;
    insertAndMeasure("large100k.txt", 2 * 100000 + 1);

    // g++ p1.cpp -o p1.exe; ./p1.exe

    return 0;
}