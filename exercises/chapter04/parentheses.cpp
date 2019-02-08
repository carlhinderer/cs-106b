/* 
 * File: parentheses.cpp 
 * ------------------
 * This program takes a C++ expression and returns whether the braces,
 *   brackets, and parentheses are closed properly.
 */

#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool CheckParentheses(string str);
bool CheckClosingSymbols(stack<char> & symbols, char closeSymbol);
bool CheckEmptyStack(stack<char> & symbols, char closeSymbol);
bool CheckBraces(stack<char> & symbols, char closeSymbol);
bool CheckBrackets(stack<char> & symbols, char closeSymbol);
bool CheckParentheses(stack<char> & symbols, char closeSymbol);
void TestCheckParentheses();

int main() {
    TestCheckParentheses();
    return 0;
}

bool CheckParentheses(string str) {
    stack<char> symbols;
    for (int i=0; i < str.length(); i++) {
        if (str[i] == '{' || str[i] == '[' || str[i] == '(') {
            symbols.push(str[i]);
        }
        if (str[i] == '}' || str[i] == ']' || str[i] == ')') {
            bool valid = CheckClosingSymbols(symbols, str[i]);
        }
    }
    return symbols.empty();
}

bool CheckClosingSymbols(stack<char> & symbols, char closeSymbol) {
    if (!CheckEmptyStack(symbols, closeSymbol)) return false;
    if (!CheckBraces(symbols, closeSymbol)) return false;
    if (!CheckBrackets(symbols, closeSymbol)) return false;
    if (!CheckParentheses(symbols, closeSymbol)) return false;
    symbols.pop();
    return true;
}

bool CheckEmptyStack(stack<char> & symbols, char closeSymbol) {
    if (symbols.empty()) {
        cout << "Closing symbol encountered before opening symbol." << endl;
        return false;
    }
    return true;
}

bool CheckBraces(stack<char> & symbols, char closeSymbol) {
    if (closeSymbol == '}' && symbols.top() != '{') {
        cout << "Braces not closed correctly." << endl;
        return false;
    }
    return true;
}

bool CheckBrackets(stack<char> & symbols, char closeSymbol) {
    if (closeSymbol == ']' && symbols.top() != '[') {
        cout << "Brackets not closed correctly." << endl;
        return false;
    }
    return true;    
}

bool CheckParentheses(stac<char> & symbols, char closeSymbol) {
    if (closeSymbol == ')' && symbols.top() != '(') {
        cout << "Parentheses not closed correctly." << endl;
        return false;
    }
    return true;
}

void TestCheckParentheses() {
    string expressions[] = { "{ s = 2 * (a[2] + 3); x = (1 + (2)); }",
                             "()",
                             "(([)",
                             ")(",
                             "{(})" };

    for (int i=0; i < 5; i++) {
        string exp = expressions[i];
        bool valid = CheckParentheses(exp);
        cout << "Valid? " << exp << ": " << valid << endl;
    }
}