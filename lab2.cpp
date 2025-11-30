// Program to construct a DFA which accepts the language L = { a^n b^m | n mod 2 = 0, m >= 1 }

#include <iostream>
#include <string>
using namespace std;

// DFA state
int dfa = 0;

// Q0 (start)
void start(char c) {
    if (c == 'a') dfa = 1;
    else if (c == 'b') dfa = 3;
    else dfa = -1;  // invalid symbol
}

// Q1
void state1(char c) {
    if (c == 'a') dfa = 2;
    else if (c == 'b') dfa = 4;
    else dfa = -1;
}

// Q2
void state2(char c) {
    if (c == 'a') dfa = 1;
    else if (c == 'b') dfa = 3;
    else dfa = -1;
}

// Q3 (Accepting state)
void state3(char c) {
    if (c == 'b') dfa = 3;
    else if (c == 'a') dfa = 4;
    else dfa = -1;
}

// Q4 (dead state)
void state4(char c) {
    dfa = -1;
}

bool isAccepted(string str) {
    for (char c : str) {
        if (dfa == 0) start(c);
        else if (dfa == 1) state1(c);
        else if (dfa == 2) state2(c);
        else if (dfa == 3) state3(c);
        else if (dfa == 4) state4(c);
        else return false; // invalid symbol
    }

    // Accepting state: Q3
    return dfa == 3;
}

int main() {
    string str;
    cout << "Enter the string: ";
    cin >> str;

    if (isAccepted(str))
        cout << "ACCEPTED\n";
    else
        cout << "NOT ACCEPTED\n";

    return 0;
}
