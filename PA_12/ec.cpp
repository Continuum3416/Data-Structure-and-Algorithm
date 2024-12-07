#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;


void print(const vector<int>& data) {
    cout << "First 5 values: ";
    size_t size = data.size();
    for (size_t i = 0; i < 5; ++i) cout << data[i] << " ";
    cout << "\nLast 5 values: ";
    for (size_t i = size - 5; i < size; ++i) cout << data[i] << " ";
    cout << endl;
}

// Output functions
void out_txt(const vector<int>& data, const string& filename) {
    ofstream outFile(filename);
    for (int value : data) {
        outFile << value << "\n";
    }
    outFile.close();
}
//output To Binary File one at a time
void out_bin_op1(const vector<int>& data, const string& filename) {
    ofstream outFile(filename, ios::binary);
    for (int value : data) {
        outFile.write(reinterpret_cast<const char*>(&value), sizeof(int));
    }
    outFile.close();
}

//output To Binary File In Block
void out_bin_op2(const vector<int>& data, const string& filename) {
    ofstream outFile(filename, ios::binary);
    size_t blockSize = 256;
    for (size_t i = 0; i < data.size(); i += blockSize) {
        size_t currentBlockSize = min(blockSize, data.size() - i);
        outFile.write(reinterpret_cast<const char*>(&data[i]), currentBlockSize * sizeof(int));
    }
    outFile.close();
}

// Input functions
void in_txt(vector<int>& data, const string& filename) {
    ifstream inFile(filename);
    int value;
    while (inFile >> value) {
        data.push_back(value);
    }
    inFile.close();
}

void in_bin_op1(vector<int>& data, const string& filename) {
    ifstream inFile(filename, ios::binary);
    int value;
    while (inFile.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        data.push_back(value);
    }
    inFile.close();
}

void in_bin_op2(vector<int>& data, const string& filename) {
    ifstream inFile(filename, ios::binary);
    size_t blockSize = 256;
    vector<int> buffer(blockSize);
    while (inFile.read(reinterpret_cast<char*>(buffer.data()), blockSize * sizeof(int))) {
        size_t numRead = inFile.gcount() / sizeof(int);
        data.insert(data.end(), buffer.begin(), buffer.begin() + numRead);
    }
    inFile.close();
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
    cout <<"Original file: " << endl;
    print(data);
    

    // Output data to files
    out_txt(data, "output_text.txt");
    out_bin_op1(data, "output_binary_one.bin");
    out_bin_op2(data, "output_binary_block.bin");

    cout << endl<<endl;
    vector<int> textData, binaryDataOne, binaryDataBlock;

    auto start = chrono::high_resolution_clock::now();
    in_txt(textData, "output_text.txt");
    auto end = chrono::high_resolution_clock::now();
    cout << "Text file input time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()<< " ms\n";
   // cout << "Text file data: " << endl;
    print(textData);

    cout << endl<<endl; 
    start = chrono::high_resolution_clock::now();
    in_bin_op1(binaryDataOne, "output_binary_one.bin");
    end = chrono::high_resolution_clock::now();
    cout << "Binary file (one at a time) input time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms\n";

    //cout << "Binary file (one at a time) data: "<<endl;
    print(binaryDataOne);

     cout << endl <<endl;
    start = chrono::high_resolution_clock::now();
    in_bin_op2(binaryDataBlock, "output_binary_block.bin");
    end = chrono::high_resolution_clock::now();
    cout << "Binary file (256 at a time) input time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms\n";
   // cout << "Binary file (256 at a time) data: " << endl;
    print(binaryDataBlock);

    // Run: g++ ec.cpp -o ec.exe; ./ec.exe
    return 0;
}
