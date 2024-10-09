#include <iostream>
#include <utility>
#include <vector>
#include "ordered_table_map.h"
#include "cost_performance.h"
using namespace std;
using namespace dsac::map;

template <typename OrderedMap>
void validate(const CostPerformanceDatabase<OrderedMap>& db) {
    int oldCost{-1}, oldPerf{-1};
    for (auto entry : db) {
        if (entry.value() <= oldPerf)
            cout << "(" << oldCost << "," << oldPerf << ") dominates (" << entry.key() << "," << entry.value() << ")" << endl;
        oldCost = entry.key();
        oldPerf = entry.value();
    }
    
}

int main() {
    CostPerformanceDatabase database;

    vector<pair<int,int>> sample = {
        {10,20}, {20,30}, {30,40}, {40,50}, {50,60}, {60,70}, {70,80}, {80,90},
        {100,5}, {100,90}, {100,85}, {65,5}, {65,85}, {35,100}, {1,100}
    };

    for (auto pair : sample) {
        database.add(pair.first, pair.second);
        validate(database);
        for (auto entry : database) cout << "(" << entry.key() << "," << entry.value() << ") ";
        cout << endl;
    }
    
}
