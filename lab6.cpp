// C program to simulate Nondeterministic Finite Automata (NFA)
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int row = 0;

// Node structure for adjacency list
struct Node {
    int data;
    char edgetype;
    Node* next;
    Node(int d, char e) : data(d), edgetype(e), next(nullptr) {}
};

// Add an edge to adjacency list
Node* push(Node* first, char edgetype, int data) {
    if (first == nullptr)
        return new Node(data, edgetype);

    first->next = push(first->next, edgetype, data);
    return first;
}

// Recursive NFA acceptance check
int nfa(vector<Node*>& graph, int current, const string& input,
        vector<int>& accept, int start)
{
    if (start == input.length())
        return accept[current];

    Node* temp = graph[current];
    while (temp != nullptr)
    {
        if (input[start] == temp->edgetype)
            if (nfa(graph, temp->data, input, accept, start + 1))
                return 1;

        temp = temp->next;
    }
    return 0;
}

// Generate all binary strings of given size
void generate(vector<string>& arr, int size, string prefix)
{
    if (size == 0)
    {
        arr[row++] = prefix;
        return;
    }

    generate(arr, size - 1, "0" + prefix);
    generate(arr, size - 1, "1" + prefix);
}

int main()
{
    int n;
    cin >> n;

    vector<Node*> graph(n + 1, nullptr);
    vector<int> accept(n + 1, 0);

    // Read NFA transitions
    for (int i = 0; i < n; i++)
    {
        int index, acc, number_nodes;
        cin >> index >> acc >> number_nodes;

        accept[index] = acc;

        for (int j = 0; j < number_nodes; j++)
        {
            int edge, node_add;
            cin >> edge >> node_add;

            graph[index] = push(graph[index], char('0' + edge), node_add);
        }
    }

    int size = 1;
    int count = 0;

    // Empty string check
    if (accept[1] == 1)
    {
        cout << "e\n";
        count++;
    }

    while (count < 11)
    {
        int power = pow(2, size);
        vector<string> arr(power, "");

        row = 0;
        generate(arr, size, "");

        for (int i = 0; i < power; i++)
        {
            string input = arr[i];

            int result = nfa(graph, 1, input, accept, 0);

            if (result == 1)
            {
                cout << input << "\n";
                count++;
            }

            if (count == 10)
                return 0;
        }
        size++;
    }

    return 0;
}
