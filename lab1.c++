// Program to construct a DFA which accepts the language L = { a^N | N ≥ 1 }



#include <iostream>
#include <string>
using namespace std;

void isAcceptedDFA(string s) {
    // Check if string is empty (N must be >= 1)
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
    string s;
    cout << "Enter the string: ";
    cin >> s;   // user inputs the string
    
    isAcceptedDFA(s);
    
    return 0;
}
