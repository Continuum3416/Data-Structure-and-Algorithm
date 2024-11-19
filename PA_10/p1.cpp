#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int comparison_count = 0;

// partition the sequence into three parts
void partition(const vector<int>& S, int pivot, vector<int>& L, vector<int>& E, vector<int>& G) {
    for (int element : S) {
        comparison_count++;
        if (element < pivot)
            L.push_back(element);
        else if (element == pivot)
            E.push_back(element);
        else
            G.push_back(element);
    }
}


int quick_select(vector<int>& S, int k) {
    int n = S.size();
    if (n == 1)
        return S[0]; // Base case: only one element


    // Pick a random pivot
    int pivot = S[rand() % n];


    vector<int> L, E, G;
    partition(S, pivot, L, E, G);

    if (k <= L.size())
        return quick_select(L, k);
    else if (k <= L.size() + E.size())
        return pivot;
    else
        return quick_select(G, k - L.size() - E.size());
}

vector<int> load_file(const string& filename) {
    ifstream file(filename);
    vector<int> data;
    int num;
    while (file >> num)
        data.push_back(num);
    return data;
}

int main() {
    srand(time(0));

    // Test case with small array
    vector<int> small_test = {10, 4, 5, 8, 6, 11, 26, 15, 20, 30};

    int n = small_test.size();

    // Test k = 1 (smallest), k = n/2 (median), k = n (largest)
    vector<int> test_cases = {1, n / 2, n};
    for (int k : test_cases) {
        comparison_count = 0;
        int result = quick_select(small_test, k);
        cout << "The " << k << "-th smallest element is: " << result << endl;
        cout << "Number of comparisons: " << comparison_count << endl;
    }

    // Test with files
    vector<int> small_data = load_file("small1k.txt");
    vector<int> large_data = load_file("large100k.txt");

    comparison_count = 0;
    int small_median = quick_select(small_data, small_data.size() / 2);
    cout << "Median of small1k.txt: " << small_median << ", comparisons = " << comparison_count << endl;

    comparison_count = 0;
    int large_median = quick_select(large_data, large_data.size() / 2);
    cout << "Median of large100k.txt: " << large_median << ", comparisons = " << comparison_count << endl;

    // Run: g++ p1.cpp -o p1.exe; ./p1.exe
    return 0;
}
