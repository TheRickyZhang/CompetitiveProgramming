#include <bits/stdc++.h>
using namespace std;

// edge struct:
//  v = endpoint vertex
//  c = residual capacity
//  r = index of reverse edge (for fast reference)
struct E{ int v, c, r; };

int n, m, s, t;
vector<vector<E>> adj;
vector<int> lvl, pos; // pos[u] = where is our current i in adj[u]?

void ae(int u, int v, int c) {
    int ui = adj[u].size(), vi = adj[v].size();
    adj[u].pb({v, c, vi}), adj[v].pb({u, 0, ui});
}

// build level graph via BFS; returns true if t is reachable
bool bfs() {
    lvl.assign(n, -1);
    queue<int> q;
    q.push(s), lvl[s] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for(auto [v, c, r] : adj[u]) {
            if (lvl[v] == -1 && c > 0) {
                lvl[v] = lvl[u] + 1;
                q.push(v);
            }
        }
    }
    return lvl[t] >= 0;
}

// try to push up to f units from u to t along the level graph
int dfs(int u, int f) {
    if (u == t) return f;         // reached sink
    int pushed = 0;

    // current‐arc optimization: continue from it[u]
    for (int& i = pos[u]; i < adj[u].size(); ++i) {
        auto& [v, c, r] = adj[u][i];
        if (lvl[v] == lvl[u] + 1 && c > 0) {
            int w = dfs(v, min(f, c));
            if (w > 0) {
                c -= w, f -= w;
                adj[v][r].c += w, pushed += w;
                if (f == 0) break;
            }
        }
    }
    return pushed;
}

// main Dinic loop
int dinic() {
    int flow = 0;
    while (bfs()) {
        pos.assign(n, 0);
        flow += dfs(s, INT_MAX);
    }
    return flow;
}

int main(){
    cin>>n>>m>>s>>t;
    adj.assign(n, {});
    lvl.assign(n,0);
    pos.assign(n,0);

    f(_,m){
        int u,v,c;
        cin>>u>>v>>c;
        ae(u,v,c);
    }

    int maxflow = dinic();
    printf("%d\n", maxflow);
    return 0;
}
