#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isBeginningBracket(char& c){
    return c == '(' || c == '{' || c == '[';
}
bool isEndBracket(char& c){
    return c == ')' || c == '}' || c == ']';
}

bool validBrackets(string &s){
    stack<char> stack;
    for(int i = 0; i < s.length(); i++){
        if(isBeginningBracket(s[i]))
            stack.push(s[i]);
        else if(
                !stack.empty() && 
                ((stack.top() == '(' && s[i] == ')') ||
                 (stack.top() == '{' && s[i] == '}') ||
                 (stack.top() == '[' && s[i] == ']'))
            )
                stack.pop();
        else if(isEndBracket(s[i])){
            return false;
        }
    }
    return stack.empty();
}

void bracketChecking(string &s){
    int roundBracket = 0, squareBracket = 0, curlyBracket = 0;
    int totalBrackets = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '(' || s[i] == ')')  roundBracket++;
        else if(s[i] == '[' || s[i] == ']')  squareBracket++;
        else if(s[i] == '{' || s[i] == '}')  curlyBracket++;
        totalBrackets = roundBracket + squareBracket + curlyBracket;
    }
    if(validBrackets(s))
        cout << "Valid brackets" << endl;
    else if(totalBrackets %2 != 0)
        cout << "Invalid, no matching opening symbol" << endl;
    else if(roundBracket %2 != 0 || squareBracket %2 != 0 || curlyBracket %2 != 0)
        cout  << "Invalid, closing symbol does not match opening symbol" << endl;
    return;
}

int main(){
    string s[] = {"{ ( a + b ) * c1 }", "{ ( a + b ) * c1 ] ", "( ( a + b ) * c1 ) / 15 )", "( ( ( a + b ) * c1 ) / 15 ) "};
    for(int i = 0; i < 4; i++){
        bracketChecking(s[i]);
    }
    

    // g++ p1.cpp -o p1.exe; ./p1.exe
    return 0;
}