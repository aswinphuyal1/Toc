///8. A simple and basic program in C to convert NFA to DFA (does not handle null moves)
#include <iostream>
using namespace std;

int dfa[100][2][100] = {0};
int stateUsed[10000] = {0};
int goToState[10000][2] = {0};
int newStates[10000] = {0};

int main() {
    int st, fin, inState;
    int finalStates[10];
    int rel;

    cout << "\nFollow zero-based indexing";
    cout << "\nEnter number of NFA states: ";
    cin >> st;

    cout << "Give state numbers from 0 to " << st - 1 << "\n";

    // Mark initial single states as used
    for (int i = 0; i < st; i++)
        stateUsed[(1 << i)] = 1;

    cout << "\nEnter number of final states: ";
    cin >> fin;

    cout << "Enter final states: ";
    for (int i = 0; i < fin; i++)
        cin >> finalStates[i];

    cout << "\nEnter number of transition rules in NFA: ";
    cin >> rel;

    cout << "\nDefine transitions as  \"initial input final\"\n";
    cout << "(Input symbol: 0 or 1)\n";

    int p, q, r;
    for (int i = 0; i < rel; i++) {
        cin >> p >> q >> r;
        dfa[p][q][r] = 1;
    }

    cout << "\nEnter initial state: ";
    cin >> inState;
    inState = (1 << inState);

    cout << "\nSolving DFA transitions...\n";

    int x = 0;

    // Build initial transitions
    for (int i = 0; i < st; i++) {
        for (int j = 0; j < 2; j++) {
            int newState = 0;
            for (int k = 0; k < st; k++) {
                if (dfa[i][j][k] == 1)
                    newState |= (1 << k);
            }
            goToState[(1 << i)][j] = newState;
            if (newState != 0 && stateUsed[newState] == 0) {
                newStates[x++] = newState;
                stateUsed[newState] = 1;
            }
            cout << "{" << "q" << i << "} --" << j << "--> {";
            for (int k = 0; k < st; k++)
                if (newState & (1 << k)) cout << "q" << k << " ";
            cout << "}\n";
        }
    }

    // Handle newly created states
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < 2; j++) {
            int merged = 0;
            for (int k = 0; k < st; k++) {
                if (newStates[i] & (1 << k)) {
                    merged |= goToState[(1 << k)][j];
                }
            }
            if (merged != 0 && stateUsed[merged] == 0) {
                newStates[x++] = merged;
                stateUsed[merged] = 1;
            }
            goToState[newStates[i]][j] = merged;
        }
    }

    // Display final DFA transition table
    cout << "\n\nDFA States and Transitions:\n";
    cout << "STATE\t0\t1\n";
    for (int i = 0; i < 10000; i++) {
        if (stateUsed[i] == 1) {
            cout << "{";
            for (int j = 0; j < st; j++)
                if (i & (1 << j)) cout << "q" << j << " ";
            cout << "}\t";
            cout << "{";
            for (int j = 0; j < st; j++)
                if (goToState[i][0] & (1 << j)) cout << "q" << j << " ";
            cout << "}\t{";
            for (int j = 0; j < st; j++)
                if (goToState[i][1] & (1 << j)) cout << "q" << j << " ";
            cout << "}\n";
        }
    }

    // Test strings
    for (int test = 0; test < 3; test++) {
        string str;
        cout << "\nEnter string of 0s and 1s: ";
        cin >> str;

        int curr = inState;
        cout << "\nPath: {";
        for (int j = 0; j < st; j++)
            if (curr & (1 << j)) cout << "q" << j << " ";
        cout << "}";

        for (size_t i = 0; i < str.length(); i++) {
            curr = goToState[curr][str[i] - '0'];
            cout << " -> {";
            for (int j = 0; j < st; j++)
                if (curr & (1 << j)) cout << "q" << j << " ";
            cout << "}";
        }

        bool accepted = false;
        for (int i = 0; i < fin; i++) {
            if (curr & (1 << finalStates[i])) {
                accepted = true;
                break;
            }
        }

        if (accepted)
            cout << "\nResult: ACCEPTED\n";
        else
            cout << "\nResult: REJECTED\n";
    }

    return 0;
}
