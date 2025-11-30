// Design deterministic finite automata (DFA) with ∑ = {0, 1} that accepts the
// languages ending with “01” over the characters {0, 1}.
#include <iostream>
using namespace std;

#define MAX 100

int main() {
    char str[MAX];
    char state = 'a';   // initial state

    cout << "Enter the string to be checked: ";
    cin >> str;

    // Process string without <cstring>
    for (int i = 0; str[i] != '\0'; i++) {
        switch(state) {
            case 'a':
                if (str[i] == '0') state = 'b';
                else if (str[i] == '1') state = 'a';
                break;

            case 'b':
                if (str[i] == '0') state = 'b';
                else if (str[i] == '1') state = 'c';
                break;

            case 'c':
                if (str[i] == '0') state = 'b';
                else if (str[i] == '1') state = 'a';
                break;
        }
    }

    if (state == 'c')
        cout << "\nString is accepted\n";
    else
        cout << "\nString is not accepted\n";

    return 0;
}
