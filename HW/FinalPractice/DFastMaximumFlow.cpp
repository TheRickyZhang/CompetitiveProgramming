#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Edge {
    int to;
    LL rem;
    int rev;
};

const LL INF = 1e18;
vector<vector<Edge>> edges;
int level[5010], pos[5010];
int s, t;

void addEdge(int u, int v, LL cap) {
    Edge a = {v, cap, (int)edges[v].size()};
    Edge b = {u, 0, (int)edges[u].size()};
    edges[u].push_back(a);
    edges[v].push_back(b);
}

bool BFS() {
    memset(level, -1, sizeof(level));
    queue<int> Q;
    Q.push(s);
    level[s] = 0;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (auto &e : edges[u]) {
            if (e.rem > 0 && level[e.to] == -1) {
                level[e.to] = level[u] + 1;
                Q.push(e.to);
                if (e.to == t) return true;
            }
        }
    }
    return level[t] != -1;
}

LL DFS(int u, LL flow) {
    if (u == t) return flow;
    for (; pos[u] < edges[u].size(); ++pos[u]) {
        Edge &e = edges[u][pos[u]];
        if (e.rem > 0 && level[e.to] == level[u] + 1) {
            LL pushed = DFS(e.to, min(flow, e.rem));
            if (pushed > 0) {
                e.rem -= pushed;
                edges[e.to][e.rev].rem += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

LL Dinic() {
    LL max_flow = 0;
    while (BFS()) {
        memset(pos, 0, sizeof(pos));
        while (LL flow = DFS(s, INF)) {
            max_flow += flow;
        }
    }
    return max_flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    s = 0; t = n + 1;
    edges.resize(n + 2);

    addEdge(s, 1, INF);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u != v) {
            addEdge(u, v, w);
            addEdge(v, u, w);  // If the graph is undirected
        }
    }
    addEdge(n, t, INF);

    cout << Dinic() << '\n';
    return 0;
}
