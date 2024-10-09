#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>  // provides EXIT_SUCCESS

using namespace std;

void init(char temp[][5], int nr, char fill) {
    for (int r = 0; r < nr; r++)
        for (int c = 0; c < 5; c++)
            temp[r][c] = fill;
}

void display(char (*temp)[5], int nr, int nc) {
    for (int r = 0; r < nr; r++) {
        for (int c = 0; c < nc; c++)
            cout << temp[r][c];
        cout << endl;
    }
}

template <typename T>
void display(vector<vector<T>>& data) {
    for (int r = 0; r < data.size(); r++) {
        for (int c = 0; c < data[r].size(); c++)
            cout << data[r][c] << " ";
        cout << endl;
    }
}

int main() {
    char board[3][5] = { {'I','N','R','O','W'}, {'M','A','J','O','R'}, {'O','R','D','E','R'} };
    display(board,3,5);
    init(board,3,'X');
    display(board,3,5);

    //    char other[3][5] = { 'I','N','R','O','W', 'M','A','J','O','R', 'O','R','D','E','R' };
    char other[][5] = { {'I','N','R','O','W'}, {'M','A','J','O','R'}, {'O','R','D','E','R'} };
    display(other,3,5);

    const int r{5},c{7};
    double warning[r][c];
    

    auto smart = make_unique<unique_ptr<double[]>[]>(r);
    for (int i = 0; i < r; i++)
        smart[i] = make_unique<double[]>(c);


    vector<vector<double>> weights(5, vector<double>(8,0.001));
    display(weights);
    
    return EXIT_SUCCESS;
}
