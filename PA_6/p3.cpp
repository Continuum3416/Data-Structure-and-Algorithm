#include <iostream>
#include <vector>
#include <stack>
#include "heap_priority_queue.h"

using namespace std;



int main(){
    HeapPriorityQueue<int> min_heap; //less is default
    HeapPriorityQueue<int, std::greater<int>> max_heap;
    std::cout << "Min-Heap Operations:" << std::endl;
    
    min_heap.insert(5);
    min_heap.insert(4);
    min_heap.insert(7);
    min_heap.insert(1);
    std::cout << "Min: " << min_heap.min() << std::endl;  // min() -> 1
    
    min_heap.remove_min();  // remove 1
    min_heap.insert(3);
    min_heap.insert(6);
    std::cout << "Min: " << min_heap.min() << std::endl;  // min() -> 3
    
    min_heap.remove_min();  // remove 3
    std::cout << "Min: " << min_heap.min() << std::endl;  // min() -> 4
    
    min_heap.remove_min();  // remove 4
    min_heap.insert(8);
    std::cout << "Min: " << min_heap.min() << std::endl;  // min() -> 5
    
    min_heap.remove_min();  // remove 5
    min_heap.insert(2);
    std::cout << "Min: " << min_heap.min() << std::endl;  // min() -> 2
    
    min_heap.remove_min();  // remove 2
    std::cout << "Min: " << min_heap.min() << std::endl;  // min() -> 6
    
    min_heap.remove_min();  // remove 6

    std::cout << "\nMax-Heap Operations:" << std::endl;

   // Performing operations on the max-heap
    max_heap.insert(5);
    max_heap.insert(4);
    max_heap.insert(7);
    max_heap.insert(1);
    std::cout << "Max: " << max_heap.min() << std::endl;  // min() -> 7 (max of max-heap)
    
    max_heap.remove_min();  // remove 7
    max_heap.insert(3);
    max_heap.insert(6);
    std::cout << "Max: " << max_heap.min() << std::endl;  // min() -> 6
    
    max_heap.remove_min();  // remove 6
    std::cout << "Max: " << max_heap.min() << std::endl;  // min() -> 5
    
    max_heap.remove_min();  // remove 5
    max_heap.insert(8);
    std::cout << "Max: " << max_heap.min() << std::endl;  // min() -> 8
    
    max_heap.remove_min();  // remove 8
    max_heap.insert(2);
    std::cout << "Max: " << max_heap.min() << std::endl;  // min() -> 4
    
    max_heap.remove_min();  // remove 4
    std::cout << "Max: " << max_heap.min() << std::endl;  // min() -> 3
    
    max_heap.remove_min();  // remove 3
    // g++ p3.cpp -o p3.exe; ./p3.exe
    return 0;
}