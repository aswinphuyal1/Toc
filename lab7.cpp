//7. Program to implement NFA from Regular Expression
#include <iostream>
#include <string>
using namespace std;

int fa[10][10][10];       // NFA transitions
int states[2][10];        // Start and final states
int curr, row = 0, col = 0, sr = 0, sc = 0, th = 0;
int in;

// Recursive NFA simulation
int nfa(const string& s, int state, int pos)
{
    for (int i = 0; i <= row; i++)
    {
        if (pos < s.length())
        {
            curr = fa[state][s[pos] - 'a'][i];
            if (curr == -1)
                break;

            if (nfa(s, curr, pos + 1))
                return 1;
        }
        else
        {
            if (states[1][i] == -1)
                break;

            if (state == states[1][i])
                return 1;
        }
    }
    return 0;
}

int main()
{
    // Initialize all arrays
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 10; j++)
            states[i][j] = -1;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
                fa[i][j][k] = -1;

    // Interactive input instead of file
    int numStates, numSymbols, numFinal, numTrans;
    cout << "Enter number of NFA states: ";
    cin >> numStates;
    cout << "Enter number of input symbols (e.g., 2 for 'a' and 'b'): ";
    cin >> numSymbols;

    cout << "Enter start state: ";
    cin >> states[0][0];

    cout << "Enter number of final states: ";
    cin >> numFinal;
    cout << "Enter final states: ";
    for (int i = 0; i < numFinal; i++)
        cin >> states[1][i];

    cout << "Enter number of transitions: ";
    cin >> numTrans;
    cout << "Enter transitions as: from_state input_symbol_index to_state\n";
    cout << "Input symbol index: 0 for 'a', 1 for 'b', etc.\n";
    for (int i = 0; i < numTrans; i++) {
        int from, symbol, to;
        cin >> from >> symbol >> to;
        // Find next available slot for this transition
        int slot = 0;
        while (fa[from][symbol][slot] != -1) slot++;
        fa[from][symbol][slot] = to;
    }

    string input;
    cout << "\nEnter the string (using 'a', 'b', ...): ";
    cin >> input;

    int start_state = states[0][0];

    if (nfa(input, start_state, 0))
        cout << "\nString is Accepted\n";
    else
        cout << "\nString Not Accepted\n";

    return 0;
}
