	#include <bits/stdc++.h>
using namespace std;

#define f(i, to) for (int i = 0; i < (to); ++i)
#define pb push_back
#define int long long
constexpr int INFL = 0x3f3f3f3f3f3f3f3f;
constexpr auto en = "\n";

template<typename T> using v = vector<T>;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using vvpii = vector<vpii>;
template<typename T> using mpq = priority_queue<T, vector<T>, greater<T>>;

void setIO(const string &name = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!name.empty()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}

void read(vvpii &g, int m, bool dec = true, bool dir = false) {
    f(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        if (dec) { u--; v--; }
        g[u].pb({v, w});
        if (!dir) g[v].pb({u, w});
    }
}

int t, k, n, m;

int32_t main() {
    setIO("dining");
    cin >> n >> m >> k;
    vvpii adj(n);
    read(adj, m);
    
    mpq<pii> q;    // Min heap of {weight, node}
    vi d(n, INFL); // distance array
    q.push({0, n - 1});
    d[n - 1] = 0;  // Start from the end
    while (!q.empty()) {
        auto [w, u] = q.top();
        q.pop();
        if (w != d[u]) continue;
        for (auto [v, dw] : adj[u]) {
            if (w + dw < d[v]) {
                d[v] = w + dw;
                q.push({d[v], v});
            }
        }
    }
    
	// secondary distances when only considering haybales as start points
	// with same graph but reduced starting distance
    vi nd(n, INFL);
    f(i, k) {
        int u, x;
        cin >> u >> x;
        u--;
        nd[u] = d[u] - x; // We can afford x more distance
        q.push({nd[u], u});
    }
    while (!q.empty()) {
        auto [w, u] = q.top();
        q.pop();
        if (w != nd[u]) continue;
        for (auto [v, dw] : adj[u]) {
            if (w + dw < nd[v]) {
                nd[v] = w + dw;
                q.push({nd[v], v});
            }
        }
    }
    
    f(i, n - 1) {
        cout << (nd[i] <= d[i] ? 1 : 0) << en;
    }
    return 0;
}