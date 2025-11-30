//Design a DFA machine accepting odd numbers of 0’s or even numbers of 1’s
#include <iostream>
using namespace std;

int main() {
    char ch;
    int zeroParity = 0;   // 0 = even, 1 = odd
    int oneParity  = 0;   // 0 = even, 1 = odd

    cout << "Enter a string of 0s and 1s: ";

    while (true) {
        cin.get(ch);

        if (ch == '\n')      // End of input
            break;

        if (ch != '0' && ch != '1') {
            cout << "Invalid input! Program terminated.\n";
            return 0;
        }

        if (ch == '0')
            zeroParity = 1 - zeroParity;   // Toggle parity
        else
            oneParity = 1 - oneParity;     // Toggle parity
    }

    // Acceptance condition:
    // Accept if (odd number of 0’s) OR (even number of 1’s)
    if (zeroParity == 1 || oneParity == 0)
        cout << "String Accepted\n";
    else
        cout << "String Rejected\n";

    return 0;
}
