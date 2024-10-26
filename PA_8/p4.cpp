#include <iostream>
#include "searchtree/tree_map.h"
#include "searchtree/avl_tree_map.h"
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

class BetterPopMap{
private:
    AVLTreeMap<int, string> tree_map;
public:
    void insert(const int& countyCode, double population, const string& countyName){
        population /= 1000.0;
        ostringstream oss;
        oss << std::fixed << std::setprecision(2) << population;
        string formattedPopulation = oss.str();
        string value = "Population: " + formattedPopulation + " million, County: " + countyName;
        tree_map.put(countyCode, value);
    }


    void readData(const string& filename){
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

    void display(){
        for(auto it = tree_map.begin(); it != tree_map.end(); it++){
            cout << it->key() << ": " << it->value() << endl;
        }
    }

    void findCounty(int countyCode) const{
        auto it = tree_map.find(countyCode);
        cout << fixed << setprecision(2);
        if(it != tree_map.end())
            cout << "Found: " << it->key() << ": " << it->value() << endl;
        else
            cout << "County code " << countyCode << " not found." << endl;
    }

    void erase(const int& countyCode){
        tree_map.erase(countyCode);
    }
};

int main(){
    BetterPopMap population_map;
    population_map.readData("popSmall.txt");
    population_map.display();
    population_map.findCounty(6037);
    population_map.findCounty(6000);
    population_map.insert(6066, 1, "New County, CA");
    population_map.insert(6065, 1, "New County, CA");
    population_map.erase(6999);
    population_map.erase(6075);
    population_map.erase(6055);
    population_map.display();

    // g++ p4.cpp -o p4.exe; ./p4.exe

    return 0;
}