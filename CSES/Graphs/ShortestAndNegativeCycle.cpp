#include <bits/stdc++.h>
using namespace std;

// Custom optimized implementation that uses DFS from node 1 and from node N to check for bad cycles
using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vvpii = vector<vpii>; using vpll = vector<pll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
using vvi = vector<vector<int>>; using vvll = vector<vector<ll>>; using mpq = priority_queue<ll, vector<ll>, greater<>>; using mpqq = priority_queue<pll, vpll, greater<>>;
#define ump unordered_map
#define ust unordered_set
#define f(i, to) for (int i = 0; i < (to); ++i)
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
constexpr int MOD = 1000000007; constexpr ll INF = INT_MAX-37; constexpr ll INFL = 0x3f3f3f3f3f3f3f3f; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n'; constexpr char sp = ' ';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

constexpr int N = 100000;
ll t, n, m, k, a, b;

struct edge {
    ll u, v, w;
    edge() : u(0), v(0), w(0) {}
    edge(ll u, ll v, ll w) : u(u), v(v), w(w) {}
};
vector<edge> edges;

void dfs(ll u, vvll& adj, vb& vis) {
    if(vis[u]) return;
    vis[u]=true;
    for(int v : adj[u]) {
        dfs(v, adj, vis);
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    vvll adj(n+1), radj(n+1);
    vb vis(n+1), rvis(n+1);
    edges.resize(m);
    f(i, m) {
        int u, v, w; cin>>u>>v>>w;
        adj[u].pb(v);
        radj[v].pb(u);
        edges[i] = edge(u, v, -w);
    }
    dfs(1, adj, vis);
    dfs(n, radj, rvis);
    // cout<<adj<<en<<radj<<en;

    vll dp(n+1, INFL);
    dp[1]=0;
    f(i, n) {  // Relax weights - note order/liveliness doesn't matter due to timing
        bool valid=false;
        f(j, m) {
            ll u=edges[j].u, v=edges[j].v, w= edges[j].w; // Since we want positive weight cycle negate weight
            ll nw=dp[u]+w;
            if(nw < dp[v]) {
                valid=true;
                dp[v]=nw;
                if(i==n-1 && vis[v] && rvis[v]) {
                    cout<<-1<<en; return 0;
                }
            }
        }
        if(!valid) break;
    }
    cout<<-dp[n]<<en;
}