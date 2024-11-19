#include <iostream>
#include "searchtree/tree_map.h"
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace dsac::search_tree;

string reverseKey(int key){
    string s = to_string(key);
    reverse(s.begin(), s.end());
    return s;
}

int totalNodesExamined = 0;
int findOperationsCount = 0;

class SimplePopMap{
private:
    TreeMap<int, string> tree_map;


public:
    void insert(const int& countyCode, double population, const string& countyName){
        population /= 1000.0;
        ostringstream oss;
        oss << std::fixed << std::setprecision(3) << population;
        string formattedPopulation = oss.str();
        string value = "Population: " + formattedPopulation + " million, County: " + countyName;
        tree_map.put(countyCode, value);
    }

    SimplePopMap(const string& filename){
        ifstream file(filename);

        string line;
        while(getline(file, line)){
            istringstream iss(line);
            string countyCode, populationStr, countyName;

            // Parse the line into countyCode, populationStr, and countyName
            getline(iss, countyCode, ',');  // Read county code
            getline(iss, populationStr, ','); // Read population string
            getline(iss, countyName);          // Read county name

            // Check if all fields were successfully parsed
            if (!countyCode.empty() && !populationStr.empty() && !countyName.empty()) {
                double population = std::stod(populationStr);
                insert(stoi(countyCode), population, countyName);
            }
        }
    }

    void print(){
        cout << "Print: " << endl;
        for(auto it = tree_map.begin(); it != tree_map.end(); it++){
            cout << it->key() << ": " << it->value() << endl;
        }
    }

    void findCounty(int countyCode) const{
        auto it = tree_map.begin();
        int nodesExamined = 0;

        // Iterate until we find the countyCode or reach the end
        while(it != tree_map.end() && it->key() != countyCode){
            ++it;
            ++nodesExamined;
        }
        
        cout << fixed << setprecision(2);
        if(it != tree_map.end()){
            cout << "Found: " << it->key() << ": " << it->value() << endl;
            ++nodesExamined;  // Increment for the found node
        }
        else
            cout << "County code " << countyCode << " not found." << endl;

        // Update counters
        totalNodesExamined += nodesExamined;
        ++findOperationsCount;
    }

    void erase(const int& countyCode){
        tree_map.erase(countyCode);
    }

    void printAverageFindOperations() const{
        if (findOperationsCount > 0) {
            double avgOperations = static_cast<double>(totalNodesExamined) / findOperationsCount;
            cout << endl<< "Average number of nodes examined per find operation: " << avgOperations << endl;
        } else {
            cout << "No find operations performed." << endl;
        }
    }
};

int main(){
    SimplePopMap population_map("test.txt");
    //population_map.print();
    population_map.findCounty(6037);
    population_map.findCounty(6000);
    // population_map.insert(6066, 1, "New County, CA");
    // population_map.insert(6065, 1, "2000, Riverside, CA");
    // population_map.erase(6999);
    // population_map.erase(6075);
    // population_map.erase(6055);
    // population_map.print();
    
    // Print the average number of nodes examined in find operations
    population_map.printAverageFindOperations();

    // g++ ec_ex_2.cpp -o ec_ex_2.exe; ./ec_ex_2.exe

    return 0;
}
