#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vpll = vector<pll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
using vvi = vector<vector<int>>; using vvll = vector<vector<ll>>; using mpq = priority_queue<ll, vector<ll>, greater<>>; using mpqq = priority_queue<pll, vpll, greater<>>;
#define ump unordered_map
#define ust unordered_set
#define f(i, to) for (int i = 0; i < (to); ++i)
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-96; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y,auto x,auto m,auto n) {return y >= 0 && y < m && x >= 0 && x < n; };

int N = 200001;
int n, q, a, b;
int ln = log2(N)+1;
vvi adj(N);
vvi par(N, vi(ln, 0));
vi depth(N, 0);

int query(int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];

    f(i, ln) if(diff & (1<<i)) a = par[a][i]; // Can use 1<< here since we know align
    if(a==b) return a;

    // Must decreasing steps to know for sure
    for(int i = ln-1; i>=0; --i) {
        if(par[a][i] != par[b][i]) {
            a = par[a][i];
            b = par[b][i];
        }
    }
    return par[a][0]; // since we track based on diff parent return one above
}

int main() {
    cin>>n>>q;
    par[1][0] = 0; // 1 is the boss
    for(int i = 2; i<=n; ++i) {
        int j; cin>>j;
        par[i][0] = j;
        adj[i].pb(j);
        adj[j].pb(i);
    }
    // Build parent table
    for(int j = 1; j < ln; ++j) {
        for(int i = 1; i<=n; ++i) {
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }

    // Get depths
    int d = 0;
    queue<pii> qq;
    qq.emplace(1, 0);
    while(!qq.empty()) {
        int sz = qq.size();
        f(i, sz) {
            auto [u, p] = qq.front(); qq.pop();
            depth[u] = d;
            for(int v : adj[u]) {
                if(v==p) continue;
                qq.emplace(v, u);
            }
        }
        d++;
    }
    // f(i, n) cout<<par[i+1]<<" "<<depth[i+1]<<en;

    f(i, q) {
        cin>>a>>b;
        cout<<query(a, b)<<en;
    }
}
