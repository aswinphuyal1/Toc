// C program to simulate Nondeterministic Finite Automata (NFA)
#include <iostream>
using namespace std;

int row = 0;

// Node for adjacency list
struct Node {
    int data;
    char edgetype;
    Node* next;
    Node(int d, char e) : data(d), edgetype(e), next(nullptr) {}
};

// Add edge
Node* push(Node* first, char edgetype, int data) {
    Node* newNode = new Node(data, edgetype);
    newNode->next = first;
    return newNode;
}

// String length
int strLength(char str[]) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

// Copy string
void strCopy(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// NFA recursive acceptance
int nfa(Node* graph[], int current, char input[], int accept[], int start, int len) {
    if (start == len)
        return accept[current];

    Node* temp = graph[current];
    while (temp != nullptr) {
        if (input[start] == temp->edgetype)
            if (nfa(graph, temp->data, input, accept, start + 1, len))
                return 1;
        temp = temp->next;
    }
    return 0;
}

// 2^exp
int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}

// Generate binary strings
void generate(char arr[][20], int size, char prefix[], int level) {
    if (level == size) {
        prefix[level] = '\0';
        strCopy(arr[row++], prefix);
        return;
    }

    prefix[level] = '0';
    generate(arr, size, prefix, level + 1);

    prefix[level] = '1';
    generate(arr, size, prefix, level + 1);
}

int main() {
    int n;
    cin >> n;  // number of states

    Node* graph[100];
    int accept[100];

    for (int i = 0; i < n; i++) {
        graph[i] = nullptr;
        accept[i] = 0;
    }

    // Input transitions
    for (int i = 0; i < n; i++) {
        int index, acc, number_nodes;
        cin >> index >> acc >> number_nodes;

        accept[index] = acc;

        for (int j = 0; j < number_nodes; j++) {
            char edge;
            int nextState;
            cin >> edge >> nextState;
            graph[index] = push(graph[index], edge, nextState);
        }
    }

    int size = 1;
    int count = 0;

    // Empty string check
    if (accept[1] == 1) {
        cout << "e\n";
        count++;
    }

    while (count < 10) {
        int total = power(2, size);
        char arr[1024][20];
        char prefix[20];

        row = 0;
        generate(arr, size, prefix, 0);

        for (int i = 0; i < total; i++) {
            char* input = arr[i];
            int len = strLength(input);

            if (nfa(graph, 1, input, accept, 0, len)) {
                cout << input << "\n";
                count++;
                if (count == 10) return 0;
            }
        }
        size++;
    }

    return 0;
}
