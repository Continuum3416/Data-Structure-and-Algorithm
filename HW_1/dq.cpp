#include <iostream>
#include <deque>
#include <queue>

using namespace std;

void print_queue(std::queue<int> q){
  while (!q.empty())
  {
    cout << q.front() << " ";
    q.pop();
  }
  cout << std::endl;
}

void print_deque(std::deque<int> d){
    for (int x : d) {
        std::cout << x << " ";
    }
}

int main() {
    std::deque<int> D = {1, 2, 3, 4, 5, 6, 7, 8};
    std::queue<int> Q;
    // Move elements from deque D to queue Q
    while (!D.empty()) {
        Q.push(D.front());
        D.pop_front();
    }

    print_queue(Q);

    // Move elements from queue Q back to deque D in the original order
    while (!Q.empty()) {
        D.push_back(Q.front());
        Q.pop();
    }

    print_deque(D);

    // Run: g++ dq.cpp -o dq.exe; ./dq.exe
    return 0;
}
