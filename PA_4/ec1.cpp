#include <iostream>
#include <string>
#include <stack>

using namespace std;

int order(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

bool isBracket(char c){
    return c =='(' || c == ')';
}

string infixToPostFix(string str){
    stack<char> stack;
    string output;
    for(int i = 0; i < str.length(); i++){
        if (isalnum(str[i])) {
            string number;
            while (i < str.length() && isdigit(str[i])) {
                number += str[i];
                i++;
            }
            output += number + " ";  // Append the number and a space
            i--;  // To counter the extra i++ from the inner while loop
        } 
        else if (str[i] == '-' && (i == 0 || !isalnum(str[i - 1]))) {
            output += '-';
        }
        else if(str[i] == '(')  stack.push('(');
        else if(str[i] == ')'){
            while(stack.top() != '('){
                output += stack.top();
                output += ' ';
                stack.pop();
            }
            stack.pop();
        }
        else{
            while(!stack.empty() && order(str[i]) <= order(stack.top())){
                output += stack.top();
                stack.pop();
            }
            stack.push(str[i]);
        }
    }
    while(!stack.empty()){
        output += stack.top();
        stack.pop();
    }
    return output;
}

int main(){ 
    string str[] = {"17/(2+3)-13", "5*(2+3)", "2*(3/2)","(-23+123)*12"};
    // 17 2 3 + / 13 -  => 17/(2+3)-13
    // 5 2 3 + *        => 5*(2+3)
    // 2 3 2 / *        => 2*(3/2)
    // -23 123 + 12 *    => (-23+123)*12
    for(int i = 0; i < 4; i++){
        cout << infixToPostFix(str[i]) << endl;
    }

    // g++ ec1.cpp -o ec1.exe; ./ec1.exe
    return 0;
}