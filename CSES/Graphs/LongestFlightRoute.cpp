#include <bits/stdc++.h>
using namespace std;

// This has weights 1 but can support any weights with inverted dijkstras
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

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    vvpii adj(n+1);
    f(i, m) {
        int u, v; cin>>u>>v;
        adj[u].pb({v, 1});
    }

    vb vis(n+1, false);
    vi order;
    function<void(int)> dfs=[&](int u) {
        vis[u]=true;
        for(auto [v, w] : adj[u]) {
            if(!vis[v]) dfs(v);
        }
        order.pb(u);
    };
    f(i, n) if(!vis[i+1]) dfs(i+1);
    reverse(all(order));

    vll dist(n+1, LLONG_MIN);
    vi par(n+1, 0);
    dist[1]=0; par[1]=1;
    for(int u : order) {
        if(dist[u]==LLONG_MIN) continue;
        for(auto [v, w] : adj[u]) {
            int nw=dist[u]+w;
            if(nw>dist[v]) {
                par[v]=u;
                dist[v]=nw;
            }
        }
    }
    if(dist[n]==LLONG_MIN) cout<<"IMPOSSIBLE"<<en;
    else {
        vi res;
        int it=n;
        while(it != par[it]) {
            res.pb(it);
            it=par[it];
        }
        res.pb(1);
        reverse(all(res));
        cout<<res.size()<<en;
        for(int x : res) cout<<x<<" ";
    }
}