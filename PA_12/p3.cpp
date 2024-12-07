#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

void out_txt(const vector<int>& data, const string& filename) {
    ofstream outFile(filename);
    for (int value : data) {
        outFile << value << "\n";
    }
    outFile.close();
}

void out_bin_op1(const vector<int>& data, const string& filename) {
    ofstream outFile(filename, ios::binary);
    for (int value : data) {
        outFile.write(reinterpret_cast<const char*>(&value), sizeof(int));
    }
    outFile.close();
}

void out_bin_op2(const vector<int>& data, const string& filename) {
    ofstream outFile(filename, ios::binary);
    size_t blockSize = 256;
    for (size_t i = 0; i < data.size(); i += blockSize) {
        size_t currentBlockSize = min(blockSize, data.size() - i);
        outFile.write(reinterpret_cast<const char*>(&data[i]), currentBlockSize * sizeof(int));
    }
    outFile.close();
}

int main() {
    const size_t NUM_VALUES = 98304;
    vector<int> data;
    data.reserve(NUM_VALUES);

    // Read data from large100k.txt
    ifstream inFile("large100k.txt");
    int value;
    while (inFile >> value && data.size() < NUM_VALUES) {
        data.push_back(value);
    }
    inFile.close();

    if (data.size() != NUM_VALUES) {
        cerr << "Error: Did not read enough values from file!" << endl;
        return 1;
    }

    // Measure and output data to files
    auto start = chrono::high_resolution_clock::now();
    out_txt(data, "output_text.txt");
    auto end = chrono::high_resolution_clock::now();
    cout << "Text file output time: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << " ms\n";

    start = chrono::high_resolution_clock::now();
    out_bin_op1(data, "output_binary_one.bin");
    end = chrono::high_resolution_clock::now();
    cout << "Binary file (one at a time) output time: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << " ms\n";

    start = chrono::high_resolution_clock::now();
    out_bin_op2(data, "output_binary_block.bin");
    end = chrono::high_resolution_clock::now();
    cout << "Binary file (256 at a time) output time: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << " ms\n";


    // Run: g++ p3.cpp -o p3.exe; ./p3.exe
    return 0;
}

