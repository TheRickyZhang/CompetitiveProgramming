#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vvpii = vector<vpii>; using vpll = vector<pll>; using vvpll = vector<vpll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
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

const int N = 200001;
const int ln= log2(N)+2;
int t=0;
ll n, m, k, a, b;
vi in(N, 0), out(N, 0), sub(N, 0);
vvi par(N, vi(ln, 0));
vvi adj(N);

void dfs(int u, int p) {
    in[u]=++t;
    par[u][0]=p;
    for(int i=1; i<ln; ++i) {
        par[u][i]=par[par[u][i-1]][i-1];
    }
    for(int v : adj[u]) {
        if(v!=p) dfs(v, u);
    }
    out[u]=++t;
}
void propogate(int u) {
    for(int v : adj[u]) {
        if(v==par[u][0]) continue;
        propogate(v);
        sub[u]+=sub[v];
    }
}
bool ancestor(int u, int v) {
    return in[u]<=in[v] && out[u]>=out[v];
}
int lca(int u, int v) {
    if(ancestor(u, v)) return u;
    if(ancestor(v, u)) return v;
    repr(i, ln, 0) {
        if(!ancestor(par[u][i], v)) u=par[u][i];
    }
    return par[u][0];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    f(i, n-1) {
        int u, v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1, 1);

    f(i, m) {
        int a, b; cin>>a>>b;
        int l=lca(a, b);
        sub[a]++; sub[b]++; sub[l]--;
        if(l!=1) sub[par[l][0]]--;
    }
    propogate(1);
    f(i, n) cout<<sub[i+1]<<" ";
}