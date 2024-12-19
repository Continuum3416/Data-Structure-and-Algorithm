#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_set>

using namespace std;


vector<int> readFile(const string &filename) {
    vector<int> numbers;
    ifstream infile(filename);
    int num;
    while (infile >> num) {
        numbers.push_back(num);
    }
    infile.close();
    return numbers;
}


void writeFile(const string &filename, const vector<int> &numbers) {
    ofstream outfile(filename);
    for (size_t i = 0; i < numbers.size(); ++i) {
        outfile << numbers[i];
        if (i < numbers.size() - 1) {
            outfile << " ";
        }
    }
    outfile.close();
}

// three-way merge
void threeWayMerge(const string &file1, const string &file2, const string &file3, const string &outputFile, bool removeDuplicates) {
    vector<int> vec1 = readFile(file1);
    vector<int> vec2 = readFile(file2);
    vector<int> vec3 = readFile(file3);


    vector<int> merged;
    size_t i = 0, j = 0, k = 0;

    while (i < vec1.size() || j < vec2.size() || k < vec3.size()) {
        int minValue = numeric_limits<int>::max();

        if (i < vec1.size()) minValue = min(minValue, vec1[i]);
        if (j < vec2.size()) minValue = min(minValue, vec2[j]);
        if (k < vec3.size()) minValue = min(minValue, vec3[k]);

        if (i < vec1.size() && vec1[i] == minValue) {
            merged.push_back(vec1[i]);
            i++;
        } 
        else if (j < vec2.size() && vec2[j] == minValue) {
            merged.push_back(vec2[j]);
            j++;
        } 
        else if (k < vec3.size() && vec3[k] == minValue) {
            merged.push_back(vec3[k]);
            k++;
        }


        if (removeDuplicates) {
            while (i < vec1.size() && vec1[i] == minValue) i++;
            while (j < vec2.size() && vec2[j] == minValue) j++;
            while (k < vec3.size() && vec3[k] == minValue) k++;
        }
    }


    writeFile(outputFile, merged);
}

void threeWayIntersectMerge(const string &file1, const string &file2, const string &file3) {
    vector<int> vec1 = readFile(file1);
    vector<int> vec2 = readFile(file2);
    vector<int> vec3 = readFile(file3);

    size_t i = 0, j = 0, k = 0;
    vector<int> result;

    while (i < vec1.size() || j < vec2.size() || k < vec3.size()) {
        int minValue = numeric_limits<int>::max();

        if (i < vec1.size()) minValue = min(minValue, vec1[i]);
        if (j < vec2.size()) minValue = min(minValue, vec2[j]);
        if (k < vec3.size()) minValue = min(minValue, vec3[k]);

        // Check occurrences in at least two lists
        int count = 0;
        if (i < vec1.size() && vec1[i] == minValue){ count++; i++;}
        if (j < vec2.size() && vec2[j] == minValue){ count++; j++;}
        if (k < vec3.size() && vec3[k] == minValue){ count++, k++;}

        if (count >= 2) {
            if (result.empty() || result.back() != minValue) {
                result.push_back(minValue);
            }
        }
    }


    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
}

void printFile(const string& filename){
    ifstream outfile(filename);
    cout << "outfile.txt: ";
    int value;
    while (outfile >> value) {
        cout << value << " ";
    }
    cout << endl;
    outfile.close();
}

int main()
{
    string infile1 = "infile1.txt";
    string infile2 = "infile2.txt";
    string infile3 = "infile3.txt";

    // Test with duplicates kept
    string outfile1 = "outfile.txt";
    threeWayMerge(infile1, infile2, infile3, outfile1, false);
    printFile(outfile1);
    

    // Test with duplicates removed
    string outfile2 = "outfile_true.txt";
    threeWayMerge("infile1_.txt", "infile2_.txt", "infile3_.txt", outfile2, true);
    printFile(outfile2);
    

    // Test three-way intersect merge
    cout << "Intersection of elements present in at least two files: ";
    threeWayIntersectMerge("infile1_.txt", "infile2_.txt", "infile3_.txt");

    

    // Run: g++ p2.cpp -o p2.exe; ./p2.exe
 
    return 0;
}