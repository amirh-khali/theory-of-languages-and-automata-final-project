#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 20;

vector<int> adj[N];
vector<char> R[N];
vector<char> W[N];
vector<char> M[N];
bool isFinal[N];
string input;

vector<int> ansState;
vector<char> ansR;
vector<char> ansW;
vector<char> ansM;
vector<string> currentPos;

void addEdge (int x, int y, char read, char write, char move) {
    adj[x].push_back(y);
    R[x].push_back(read);
    W[x].push_back(write);
    M[x].push_back(move);
}

void build () {
    addEdge(0, 1, 'a', 'x', 'R');
    addEdge(0, 1, 'b', 'y', 'R');
    addEdge(0, 1, 'c', 'z', 'R');

    addEdge(1, 1, 'a', 'a', 'R');
    addEdge(1, 1, 'b', 'b', 'R');
    addEdge(1, 1, 'c', 'c', 'R');

    addEdge(1, 2, '$', '$', 'L');
    addEdge(1, 2, 'x', 'x', 'L');
    addEdge(1, 2, 'y', 'y', 'L');
    addEdge(1, 2, 'z', 'z', 'L');

    addEdge(2, 3, 'a', 'x', 'L');
    addEdge(2, 3, 'b', 'y', 'L');
    addEdge(2, 3, 'c', 'z', 'L');

    addEdge(3, 3, 'a', 'a', 'L');
    addEdge(3, 3, 'b', 'b', 'L');
    addEdge(3, 3, 'c', 'c', 'L'); 

    addEdge(3, 0, 'x', 'x', 'R');
    addEdge(3, 0, 'y', 'y', 'R');
    addEdge(3, 0, 'z', 'z', 'R');

    addEdge(0, 4, 'x', 'x', 'L');
    addEdge(0, 4, 'y', 'y', 'L');
    addEdge(0, 4, 'z', 'z', 'L');

    addEdge(4, 4, 'x', 'a', 'L');
    addEdge(4, 4, 'y', 'b', 'L');
    addEdge(4, 4, 'z', 'c', 'L');

    addEdge(4, 5, '$', '$', 'R');

    addEdge(5, 6, 'a', 'x', 'R');
    addEdge(5, 7, 'b', 'y', 'R');
    addEdge(5, 8, 'c', 'z', 'R');

    addEdge(6, 6, 'a', 'a', 'R');
    addEdge(6, 6, 'b', 'b', 'R');
    addEdge(6, 6, 'c', 'c', 'R');
    addEdge(6, 6, 'M', 'M', 'R');

    addEdge(7, 7, 'a', 'a', 'R');
    addEdge(7, 7, 'b', 'b', 'R');
    addEdge(7, 7, 'c', 'c', 'R');
    addEdge(7, 7, 'M', 'M', 'R');
    
    addEdge(8, 8, 'a', 'a', 'R');
    addEdge(8, 8, 'b', 'b', 'R');
    addEdge(8, 8, 'c', 'c', 'R');
    addEdge(8, 8, 'M', 'M', 'R');

    addEdge(6, 9, 'x', 'M', 'L');
    addEdge(7, 9, 'y', 'M', 'L');
    addEdge(8, 9, 'z', 'M', 'L');

    addEdge(9, 9, 'a', 'a', 'L');
    addEdge(9, 9, 'b', 'b', 'L');
    addEdge(9, 9, 'c', 'c', 'L');
    addEdge(9, 9, 'M', 'M', 'L');

    addEdge(9, 5, 'x', 'x', 'R');
    addEdge(9, 5, 'y', 'y', 'R');
    addEdge(9, 5, 'z', 'z', 'R');

    addEdge(5, 10, 'M', 'M', 'L');
    addEdge(0, 10, '$', '$', 'L');

    isFinal[10] = true;  
}

bool dfs (int x, int c) {
  
    if (isFinal[x]) {
        ansState.push_back(x);
        return true;
    }

    for (int i = 0; i < adj[x].size(); ++i) {
        int child = adj[x][i];
        char childR = R[x][i];
        char childW = W[x][i];
        char childM = M[x][i];
        if (input[c] == childR) {
            input[c] = childW;
            currentPos.push_back(input);
            if ((childM == 'R'? dfs(child, c + 1) : dfs(child, c - 1))) {
                ansR.push_back(childR);
                ansW.push_back(childW);
                ansM.push_back(childM);
                ansState.push_back(x);
                return true;
            }
            currentPos.pop_back();
            input[c] = childR;
        }
    }

    return false;
}

void print () {
    for (int i = ansState.size() - 1; i > 0; --i) {
        cout << ansState[i] << " edge(" << ansR[i - 1] << " => " << ansW[i - 1] << ", " << ansM[i - 1] << ") " << ansState[i - 1] << '\n';
        cout << currentPos[ansState.size() - i - 1] << '\n';
    }
}

int main () {
    build();
    cin >> input;
    input = "$" + input + "$";
    if (dfs(0, 1)) {
        print();
    } else {
        cout << "False\n";
    }
}