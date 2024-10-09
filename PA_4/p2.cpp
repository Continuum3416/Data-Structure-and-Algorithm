#include <iostream>
#include <string>
#include <stack>
#define SIZE 10

using namespace std;

template<typename T> class MyArrayStack{
private:
    T A[SIZE];
    int count = 0;
public:
    MyArrayStack(){}
    void push(T element){
        if(count < SIZE){
            for(int i = count; i > 0; i--)
                A[i] = A[i - 1];
            A[0] = element;
            count++;
        }
        else
            std::cout << "Stack is full" << endl;
    }
    void pop(){
        if(count != 0){
            for(int i = 0; i < count; i++)
                A[i] = A[i + 1];
            A[count] = T();
            count--;
        }
        else 
            std::cout << "Nothing left to pop." << endl;
    }
    bool empty(){ return count == 0;}
    int top(){return A[0];}
    int size(){return count;}

    void printStack(){
        cout << "\nstack: ";
        for(int i = 0; i < count; i++)
            cout << A[i] << " ";
        std::cout << std::endl;
        return;
    }
};


int postFixCalculation(std::string &str){
    MyArrayStack<int> stack;
    string sum;
    for(int i = 0; i < str.length(); i++){
        if(str[i] == '-' && (i == 0 || !isspace(str[i - 1])))
            sum = '-' + sum;
        else if(isdigit(str[i]))
            sum += str[i];
        else if(isspace(str[i])){
            if(!sum.empty()){
                stack.push(stoi(sum));
                sum = "";
            }
        }
        else{
            int a = stack.top(); stack.pop();
            int b = stack.top(); stack.pop();
            switch(str[i]){
                case '+': stack.push(b + a); break;
                case '-': stack.push(b - a); break;
                case '*': stack.push(b * a); break;
                case '/': stack.push(b / a); break;
            }
        }
    }
    return stack.top();
}

// 17, -3 -> push
// +, -, *, / -> pop twice -> evaluate -> push result

int main(){ 
    string str[] = {"17 2 3 + / 13 - ","5 2 3 + *" , "2 3 2 / *", "-23 123 + 2 *"};

    for(int i = 0; i < 4; i++){
        cout << "Output: " << postFixCalculation(str[i]) << endl;
    }

    // g++ p2.cpp -o p2.exe; ./p2.exe
    return 0;
}