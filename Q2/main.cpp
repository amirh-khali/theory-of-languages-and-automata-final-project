#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 20;

vector<int> adj[N];
vector<char> w[N];
bool isFinal[N];
int n;
string s;
//bool mark[N];
vector<int> ansState;
vector<char> ansEdge;

void build () {
    n = 2;
    adj[0].push_back(1);
    w[0].push_back('a');
    adj[0].push_back(2);
    w[0].push_back('b');
    adj[0].push_back(0);
    w[0].push_back('c');

    adj[1].push_back(2);
    w[1].push_back('a');
    adj[1].push_back(0);
    w[1].push_back('b');
    adj[1].push_back(1);
    w[1].push_back('c');
    
    adj[2].push_back(0);
    w[2].push_back('a');
    adj[2].push_back(1);
    w[2].push_back('b');
    adj[2].push_back(2);
    w[2].push_back('c');

    isFinal[1] = true;
}

bool dfs (int x, int c) {
    //mark[x] = true;
    if (c == s.size()) {
        if (isFinal[x]) {
            ansState.push_back(x);
            return true;
        }
        return false;
    }

    for (int i = 0; i < adj[x].size(); ++i) {
        int child = adj[x][i];
        char childW = w[x][i];
        if (childW == s[c]) {
            if (dfs(child, c + 1)) {
                ansEdge.push_back(childW);
                ansState.push_back(x);
                return true;
            }
        }
    }

    return false;
}

void print () {
    for (int i = ansState.size() - 1; i > 0; --i) {
        cout << ansState[i] << " -" << ansEdge[i - 1] << "-> " << ansState[i - 1] << '\n';
    }
}

int main () {
    build();
    cin >> s;
    if (dfs(0, 0)) {
        print();
    } else {
        cout << "False\n";
    }
}