//Construct deterministic finite automata (DFA) for the language L = { w : w has odd
//number of 0’s and w has odd number of 1’s},over the alphabet Σ = {0, 1}.
#include <iostream>
using namespace std;

// DFA states
int EE = 0, OE = 1, OO = 2, EO = 3;
int state = 0;      // initial state
char input;

int main() {
    cout << "Enter a string of 0s and 1s: ";

    while (true) {
        cin.get(input);

        if (input == '\n')      // end of input
            break;

        if (input != '0' && input != '1') {
            cout << "Invalid input! Program terminating.\n";
            return 0;
        }

        // State transitions
        if (state == EE) {                // 0
            state = (input == '0') ? OE : EO;
        }
        else if (state == OE) {           // 1
            state = (input == '0') ? EE : OO;
        }
        else if (state == OO) {           // 2
            state = (input == '0') ? EO : OE;
        }
        else {                             // EO (3)
            state = (input == '0') ? OO : EE;
        }
    }

    // Accepting state is OO (odd 0’s, odd 1’s)
    if (state == OO)
        cout << "Input accepted\n";
    else
        cout << "Input rejected\n";

    return 0;
}
