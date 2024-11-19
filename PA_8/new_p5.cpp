#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include "new_avl.h"



using namespace std;
using namespace dsac::search_tree;

class BetterPopMap {
private:
    AVLTreeMap<int, string> tree_map;

public:
    void insert(const int& countyCode, double population, const string& countyName) {
        population /= 1000.0; // Convert to millions
        ostringstream oss;
        oss << fixed << setprecision(2) << population;
        string formattedPopulation = oss.str();
        string value = "Population: " + formattedPopulation + " million, County: " + countyName;
        tree_map.put(countyCode, value);
    }

    void readData(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string countyCode, populationStr, countyName;

            getline(iss, countyCode, ',');
            getline(iss, populationStr, ',');
            getline(iss, countyName);

            if (!countyCode.empty() && !populationStr.empty() && !countyName.empty()) {
                double population = std::stod(populationStr);
                insert(stoi(countyCode), population, countyName);
            }
        }
    }

    // void display() {
    //     tree_map.display();
    // }

    // void findCounty(int countyCode) const {
    //     // Assuming you would implement a find method in AVLTreeMap
    //     // Placeholder function for illustration
    // }

    // void erase(const int& countyCode) {
    //     // Placeholder function for erase, assuming you'll implement this
    // }

    void draw() const {
        tree_map.display(); // Show the tree structure
    }
};

int main() {
    BetterPopMap bpm;

    // Manually inserting nodes according to the specified structure
    bpm.insert(1234, 2000, "County A"); // Root
    bpm.insert(1000, 500, "County B");  // Left child
    bpm.insert(2000, 1500, "County C"); // Right child
    bpm.insert(1500, 1000, "County D"); // Right child's left child
    bpm.insert(2500, 2000, "County E"); // Right child's right child

    // Display the tree structure
    bpm.draw();


    // g++ new_p5.cpp -o new_p5.exe; ./new_p5.exe
    return 0;
}
