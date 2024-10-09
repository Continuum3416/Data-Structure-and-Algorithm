#include <chrono>
#include <cstdlib>  // provides EXIT_SUCCESS
#include <iostream>
#include <iomanip>
#include <string>   // provides std::stoi

using namespace std;
using namespace std::chrono;

/// Uses appropriate string constructor to fill with n copies of character c
string repeat0(int n, char c) {
    string pattern(n,c);
    return pattern;
}

/// Uses repeated += operator to compose a String with n copies of character c
string repeat1(int n, char c) {
    string pattern;
    for (int j = 0; j < n; j++)
        pattern += c;              // note use of += operator
    return pattern;
}

/// Uses repeated addition to compose a String with n copies of character c
string repeat2(int n, char c) {
    string pattern;
    for (int j = 0; j < n; j++)
        pattern = pattern + c;       // note use of + operator
    return pattern;
}


/// Tests the three versions of the 'repeat' algorithm, with each trial doubling the size.
/// The first command line argument can be used to change the number of trials, and the second
/// to adjust the start value
int main(int argc, char* argv[]) {
    int start{argc >= 2 ? stoi(argv[1]) : 50000};      // starting size (default 50000)
    int trials{argc >= 3 ? stoi(argv[2]) : 10};        // number of trials (default 10)

    // array of three function pointers.
    string (*functions[])(int,char) = {repeat0, repeat1, repeat2};

    // go from most efficient to least efficient
    for (int f=0; f <= 2; f++) {
        cout << endl << "Testing repeat" << (f) << "..." << endl;
        int n{start};
        for (int t=0; t < trials; t++) {
            auto start = high_resolution_clock::now();
            string temp{ (*functions[f])(n,'-')};
            auto stop = high_resolution_clock::now();
            auto elapsed = duration_cast<milliseconds>(stop-start).count();
            cout << "n=" << setw(9) << temp.size() << " took " << setw(12) << elapsed << " milliseconds" << endl;
            n *= 2;  // double problem size
        }
    }
    
    return EXIT_SUCCESS;
}


/* 
Sample output:

Testing repeat0...
n=    50000 took            0 milliseconds
n=   100000 took            0 milliseconds
n=   200000 took            0 milliseconds
n=   400000 took            0 milliseconds
n=   800000 took            0 milliseconds
n=  1600000 took            0 milliseconds
n=  3200000 took            1 milliseconds
n=  6400000 took            2 milliseconds
n= 12800000 took            5 milliseconds
n= 25600000 took            9 milliseconds

Testing repeat1...
n=    50000 took            0 milliseconds
n=   100000 took            0 milliseconds
n=   200000 took            1 milliseconds
n=   400000 took            2 milliseconds
n=   800000 took            5 milliseconds
n=  1600000 took            9 milliseconds
n=  3200000 took           18 milliseconds
n=  6400000 took           39 milliseconds
n= 12800000 took           78 milliseconds
n= 25600000 took          170 milliseconds

Testing repeat2...
n=    50000 took           47 milliseconds
n=   100000 took          170 milliseconds
n=   200000 took          648 milliseconds
n=   400000 took         2939 milliseconds
n=   800000 took        10889 milliseconds
n=  1600000 took        43434 milliseconds
n=  3200000 took       345668 milliseconds

*/
