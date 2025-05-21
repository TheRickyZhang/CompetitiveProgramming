#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int n, m;
int state[N], par[N];
vector<int> adj[N];
int startNode = -1, endNode = -1;

bool dfs(int u) {
    state[u] = 1; // Mark as visiting
    for (int v : adj[u]) {
        if (state[v] == 0) {
            par[v] = u;
            if (dfs(v)) return true;
        } else if (state[v] == 1) {
            // Found a back edge, cycle detected
            startNode = v;
            endNode = u;
            return true;
        }
    }
    state[u] = 2; // Mark as done
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    fill(par, par + n + 1, -1);

    for (int i = 1; i <= n; i++) {
        if (state[i] == 0 && dfs(i)) {
            vector<int> cycle;
            cycle.push_back(startNode);
            for (int cur = endNode; cur != startNode; cur = par[cur]) {
                cycle.push_back(cur);
            }
            cycle.push_back(startNode);
            reverse(cycle.begin(), cycle.end());
            cout << cycle.size() << "\n";
            for (int x : cycle) cout << x << " ";
            cout << "\n";
            return 0;
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
