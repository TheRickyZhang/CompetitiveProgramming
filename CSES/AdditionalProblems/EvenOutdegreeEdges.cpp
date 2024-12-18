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
constexpr int MOD = 1000000007; constexpr ll INF = INT_MAX-37; constexpr ll INFL = 0x3f3f3f3f3f3f3f3f; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
constexpr char EN = '\n'; constexpr char SP = ' '; auto en = EN; auto sp = SP;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = enable_if_t<!is_same_v<T_container, string>, typename T_container::value_type>> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

constexpr int N = 100000;
ll t, n, m, k, a, b;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>m;
    vvi adj(n);
    f(i, m) {
        int u, v; cin>>u>>v; u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi vis(n, 0); vi odd(n, 0);
    int t=1;
    vpii res;
    function<void(int, int)> dfs = [&](int u, int p) {
        vis[u]=t++;
        for(int v : adj[u]) {
            if(v==p) continue;
            if(!vis[v]) { // This part is simple - handling a tree = determine children parity first and adjust accordingly
                dfs(v, u);
                if(odd[v]) {
                    res.pb({v, u});
                    odd[v]=0;
                } else {
                    res.pb({u,v});
                    odd[u] ^= 1;
                }
            } else if (vis[u] > vis[v]) { // tricky logic - if we process children first then always u->v backedges = account for direction beforehand
                res.pb({u, v});
                odd[u] ^= 1;
            }
        }
    };
    f(i, n) {
        if(!vis[i]) dfs(i, -1);
    }
    if(accumulate(all(odd), 0)) {
        cout<<"IMPOSSIBLE"<<en;
    } else {
        for(auto [u, v] : res) {
            cout<<u+1<<SP<<v+1<<EN;
        }
    }
}