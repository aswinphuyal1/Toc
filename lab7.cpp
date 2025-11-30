//7. Program to implement NFA from Regular Expression
#include <iostream>
#include <fstream>
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

    ifstream file("Nfa_ip.txt");
    if (!file)
    {
        cout << "Error: Cannot open Nfa_ip.txt\n";
        return 0;
    }

    int flag = 0;
    char c;

    while (file >> in)
    {
        file.get(c);

        if (flag)
        {
            states[sr][sc++] = in;
            if (c == '\n')
            {
                sr++;
                sc = 0;
            }
        }
        else if (c == '#')
        {
            flag = 1;
            fa[row][col][th] = in;
            cout << "\nfa[" << row << "][" << col << "][" << th << "]=" << in;
        }
        else if (!flag)
        {
            fa[row][col][th] = in;
            cout << "\nfa[" << row << "][" << col << "][" << th << "]=" << in;

            if (c == ',')
            {
                th++;
            }
            else if (c == '\n')
            {
                col = 0;
                row++;
                th = 0;
            }
            else
            {
                col++;
                th = 0;
            }
        }
    }

    file.close();

    string input;
    cout << "\n\nEnter the string: ";
    cin >> input;

    int start_state = states[0][0];

    if (nfa(input, start_state, 0))
        cout << "\nString is Accepted\n";
    else
        cout << "\nString Not Accepted\n";

    return 0;
}
