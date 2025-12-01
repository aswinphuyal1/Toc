 // C program to simulate Nondeterministic Finite Automata (NFA)

#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

struct Transition {
    int to;
    char symbol;   // input char or 'e' for epsilon
};

// Compute epsilon-closure of a state
void epsilonClosure(int state, vector<vector<Transition>>& nfa, set<int>& closure) {
    if (closure.count(state)) return;
    closure.insert(state);

    for (auto& t : nfa[state]) {
        if (t.symbol == 'e') { // epsilon transition
            epsilonClosure(t.to, nfa, closure);
        }
    }
}

// Move function: states reachable using input symbol
set<int> moveOnSymbol(const set<int>& states, char symbol, vector<vector<Transition>>& nfa) {
    set<int> result;
    for (int st : states) {
        for (auto& t : nfa[st]) {
            if (t.symbol == symbol) {
                result.insert(t.to);
            }
        }
    }
    return result;
}

int main() {
    int numStates, numTransitions, startState, numFinalStates;
    cout << "Enter number of states: ";
    cin >> numStates;

    vector<vector<Transition>> nfa(numStates);

    cout << "Enter number of transitions: ";
    cin >> numTransitions;

    cout << "Enter transitions (from to symbol) — use 'e' for epsilon:\n";
    for (int i = 0; i < numTransitions; i++) {
        int from, to;
        char symbol;
        cin >> from >> to >> symbol;
        nfa[from].push_back({to, symbol});
    }

    cout << "Enter start state: ";
    cin >> startState;

    cout << "Enter number of final states: ";
    cin >> numFinalStates;

    set<int> finalStates;
    cout << "Enter final states: ";
    for (int i = 0; i < numFinalStates; i++) {
        int fs;
        cin >> fs;
        finalStates.insert(fs);
    }

    string input;
    cout << "Enter input string: ";
    cin >> input;

    // Step 1: ε-closure of start state
    set<int> currentStates;
    epsilonClosure(startState, nfa, currentStates);

    // Step 2: Process each input symbol
    for (char c : input) {
        set<int> nextStates = moveOnSymbol(currentStates, c, nfa);

        // Apply epsilon-closure on all reachable states
        set<int> closure;
        for (int st : nextStates) {
            epsilonClosure(st, nfa, closure);
        }
        currentStates = closure;
    }

    // Step 3: Check acceptance
    for (int st : currentStates) {
        if (finalStates.count(st)) {
            cout << "\nString Accepted!\n";
            return 0;
        }
    }

    cout << "\nString Rejected.\n";
    return 0;
}
