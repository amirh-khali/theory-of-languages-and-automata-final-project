#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 20;

vector<int> adj[N];
vector<char> w[N];
vector<char> push[N];
vector<char> pop[N];
vector<char> memory;
bool isFinal[N];
int n;
string s;
//bool mark[N];
vector<int> ansState;
vector<char> ansW;
vector<char> ansPop;
vector<char> ansPush;

void addEdge (int x, int y, char W, char Pop, char Push) {
    adj[x].push_back(y);
    w[x].push_back(W);
    pop[x].push_back(Pop);
    push[x].push_back(Push);
}

void build () {
    memory.push_back('$');
    addEdge(0, 0, 'b', '#', 'b');
    addEdge(0, 0, 'a', '#', 'a');
    addEdge(0, 1, 'c', '#', '#');
    addEdge(1, 1, 'a', 'a', '#');
    addEdge(1, 1, 'b', 'b', '#');
    addEdge(1, 2, '#', '$', '$');

    isFinal[2] = true;
}

bool dfs (int x, int c) {
    //mark[x] = true;
    if (c == s.size()) {
        //cout << x << ' ' << c << '\n';
        if (isFinal[x]) {
            ansState.push_back(x);
            return true;
        }
    }

    for (int i = 0; i < adj[x].size(); ++i) {
        int child = adj[x][i];
        char childW = w[x][i];
        char childPop = pop[x][i];
        char childPush = push[x][i];
        if ((childW == '#' || childW == s[c]) && (childPop == '#' || memory.back() == childPop)) {
            if (childPop != '#') memory.pop_back();
            if (childPush != '#') memory.push_back(childPush);
            //cout << x << " edge(" << childW << ", " << childPop << " => " << childPush << ") " << child << '\n';
            if ((childW == '#'? dfs(child, c) : dfs(child, c + 1))) {
                ansW.push_back(childW);
                ansPop.push_back(childPop);
                ansPush.push_back(childPush);
                ansState.push_back(x);
                return true;
            }
            if (childPush != '#') memory.pop_back();
            if (childPop != '#') memory.push_back(childPop);
        }
    }

    return false;
}

void print () {
    for (int i = ansState.size() - 1; i > 0; --i) {
        cout << ansState[i] << " edge(" << ansW[i - 1] << ", " << ansPop[i - 1] << " => " << ansPush[i - 1] << ") " << ansState[i - 1] << '\n';
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