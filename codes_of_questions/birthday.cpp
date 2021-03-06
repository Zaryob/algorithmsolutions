#include <bits/stdc++.h>

using namespace std;

int total = 2;

void deep_first_search(vector<vector<int>>& adj, vector<int>& up, vector<int>& down, int parent, int start) {
    for(auto next : adj[start]) {
        if(up[next] == -1) {
            up[next] = total;
            down[next] = total;
            total++;
            deep_first_search(adj, up, down, start, next);
            down[start] = min(down[start], down[next]);
        }

        else {
            if(next != parent) {
                down[start] = min(down[start], down[next]);
            }
        }
    }
}

bool find_connection(vector<vector<int>>& adj) {
    int n = adj.size();

    vector<int> up(n, -1);
    vector<int> down(n);

    up[0] = 1;
    down[0] = 1;
    deep_first_search(adj, up, down, 0, 0);

    for(int i = 1; i < n; i++) {
        if(up[i] == down[i]) {
            return true;
        }
    }
    return false;
}

int find(vector<int>& d, int a) {
    if(d[a] == -1) {
        return a;
    }

    d[a] = find(d, d[a]);
    return d[a];
}

void join(vector<int>& d, int a, int b) {
    a = find(d, a);
    b = find(d, b);

    if(a == b) {
        return;
    }

    d[a] = b;
}

int main() {

    int n, m;
    while(cin >> n && cin >> m && !(n == 0 && m == 0)) {
        vector<vector<int>> adj(n);
        vector<int> d(n, -1);
        for(int i = 0; i < m; i++) {
            int n1, n2;
            cin >> n1 >> n2;

            adj[n1].push_back(n2);
            adj[n2].push_back(n1);

            join(d, n1, n2);
        }

        bool connected = true;
        for(int i = 1; i < n; i++) {
            if(find(d, i) != find(d, 0)) {
                connected = false;
            }
        }

        if(!connected || find_connection(adj)) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
}

