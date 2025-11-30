//Program to construct a DFA which accepts the language L = {aN | N ≥ 1
#include <iostream>
#include <string>
using namespace std;

void isAcceptedDFA(string s) {
    // Check if string is empty
    if (s.empty()) {
        cout << "Not Accepted";
        return;
    }
    
    // Check if all characters are 'a'
    for (char c : s) {
        if (c != 'a') {
            cout << "Not Accepted";
            return;
        }
    }
    
    cout << "Accepted";
}

int main() {
    string S = "aaaaa";
    isAcceptedDFA(S);
    return 0;
}