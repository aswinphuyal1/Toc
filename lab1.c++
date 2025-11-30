//Program to construct a DFA which accepts the language L = {aN | N ≥ 1
#include <stdio.h>
using namespace std;
// Function to check whether the string
// S satisfy the given DFA or not
void isAcceptedDFA(string s, int N)
{
// Stores the count of characters
int count = 0;
// Iterate over the range [0, N]
for (int i = 0; i < N; i++) {
// Count and check every
// element for 'a'
if (s[i] == 'a')
count++;
}
// If string matches with DFA
if (count == N && count != 0) {
cout << "Accepted";
}
// If not matches
else {
cout << "Not Accepted";
}
}
// Driver Code
int main()
{
string S = "aaaaa";
// Function Call
isAcceptedDFA(S, S.size());
return 0;
}
