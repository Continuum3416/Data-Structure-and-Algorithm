#include <iostream>
#include <vector>
#include <cstdlib>  // for rand()
#include <ctime>    // for seeding rand()
#include <fstream>

using namespace std;


int comparison_count = 0;

// partition the array
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        comparison_count++;
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

// Randomized partition to select a random pivot
int randomized_partition(vector<int>& arr, int low, int high) {
    int pivot_idx = low + rand() % (high - low + 1);
    swap(arr[pivot_idx], arr[high]);  // Move the random pivot to the end
    return partition(arr, low, high);
}

// Randomized QuickSelect to find the k-th smallest element
int randomized_quick_select(vector<int>& arr, int low, int high, int k) {
    if (low <= high) {
        int pivot_index = randomized_partition(arr, low, high);

        // If pivot is the k-th smallest element
        if (pivot_index == k)
            return arr[pivot_index];
        else if (pivot_index > k)
            return randomized_quick_select(arr, low, pivot_index - 1, k);
        else
            return randomized_quick_select(arr, pivot_index + 1, high, k);
    }
    return -1;  // Edge case: k is out of bounds
}


vector<int> read_file(const string& filename) {
    vector<int> data;
    ifstream file(filename);
    if (file.is_open()) {
        int num;
        while (file >> num)
            data.push_back(num);
        file.close();
    } 
    else 
        return {};
    return data;
}

int main() {
    srand(time(0));


    vector<int> arr = {10, 4, 5, 8, 6, 11, 26, 15, 20, 30};
    int n = arr.size();

    // Test k = 1 (smallest), k = n/2 (median), k = n (largest)
    vector<int> test_cases = {1, n / 2, n};


    for (int k : test_cases) {
        comparison_count = 0;
        int result = randomized_quick_select(arr, 0, n - 1, k - 1);
        cout << "The " << k << "-th smallest element is: " << result << endl;
        cout << "Number of comparisons: " << comparison_count << endl;
    }

    // Test on files
    vector<int> small_data = read_file("small1k.txt");
    vector<int> large_data = read_file("large100k.txt");

    // Finding the median
    comparison_count = 0;
    int small_median = randomized_quick_select(small_data, 0, small_data.size() - 1, small_data.size() / 2);
    cout << "Median of small1k.txt: " << small_median << endl;
    cout << "Number of comparisons: " << comparison_count << endl;

    comparison_count = 0;
    int large_median = randomized_quick_select(large_data, 0, large_data.size() - 1, large_data.size() / 2);
    cout << "Median of large100k.txt: " << large_median << endl;
    cout << "Number of comparisons: " << comparison_count << endl;


    // Run: g++ p1_0.cpp -o p1_0.exe; ./p1_0.exe
    return 0;
}
