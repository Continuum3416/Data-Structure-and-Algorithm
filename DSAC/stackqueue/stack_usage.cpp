#include "stackqueue/stack.h"
#include <cstdlib>                      // provides EXIT_SUCCESS
#include <iostream>
using namespace dsac::stackqueue;
using namespace std;

int main() {
    stack<int> S;                              // contents: ()
    S.push(5);                                 // contents: (5)
    S.push(3);                                 // contents: (5, 3)
    cout << S.size() << endl;                  // contents: (5, 3)        outputs 2
    S.pop();                                   // contents: (5)
    cout << boolalpha << S.empty() << endl;    // contents: (5)           outputs false
    S.pop();                                   // contents: ()
    cout << boolalpha << S.empty() << endl;    // contents: (5)           outputs true
    S.push(7);                                 // contents: (7)
    S.push(9);                                 // contents: (7, 9)
    cout << S.top() << endl;                   // contents: (7, 9)        outputs 9
    S.push(4);                                 // contents: (7, 9, 4)
    cout << S.size() << endl;                  // contents: (7, 9, 4)     outputs 3
    S.pop();                                   // contents: (7, 9)
    S.push(6);                                 // contents: (7, 9, 6)
    S.push(8);                                 // contents: (7, 9, 6, 8)
    S.pop();                                   // contents: (7, 9, 6)
    cout << S.top() << endl;                   // contents: (7, 9, 6)     outputs 6
    
    return EXIT_SUCCESS;
}
