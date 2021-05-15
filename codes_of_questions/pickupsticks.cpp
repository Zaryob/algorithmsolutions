#include <bitset>
#include <vector>
#include <iostream>

using namespace std;

#define maxN 100111

int n, color[maxN];
vector<int> adj[maxN], sortedNode;
bool possible;

void visit(int u) {
    if (!possible) return;
    color[u] = 1;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (color[v] == 0) visit(v);
        else if (color[v] == 1) {
            possible = false;
            return;
        }
    }
    sortedNode.push_back(u);
    color[u] = 2;
}

int main() {
    int m, u, v;
    while (scanf("%d %d", &n, &m) && (n || m)) {
        for (int i = 1; i <= n; i++)
            color[i] = 0, adj[i].clear();
        while (m--) {
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
        }
        possible = true;
        sortedNode.clear();
        for (int i = 1; i <= n && possible; i++)
            if (color[i] == 0) visit(i);
        if (!possible) {
            puts("IMPOSSIBLE");
            return 0;
        }
        else {
            for (int i = sortedNode.size() - 1; i >= 0; i--)
                printf("%d\n", sortedNode[i]);
            return 0;
        }
    }
    return 0;
}

