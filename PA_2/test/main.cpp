#include <iostream>

class MyClass {
private:
    int privateVar;

public:
    MyClass() : privateVar(42) {}
};

int main() {
    MyClass obj;
    int* privateVarPtr = (int*)&obj;  // Direct memory access to private member
    std::cout << "Private variable value (via pointer): " << *privateVarPtr << std::endl;
    // Run: g++ main.cpp -o main.exe; ./main.exe
    return 0;
}
