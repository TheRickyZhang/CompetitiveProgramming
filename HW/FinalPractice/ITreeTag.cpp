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
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-37; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n'; constexpr char sp = ' ';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

constexpr int N = 100000;
int n, a, b, da, db;
vvi adj;

auto bfs = []() {
    queue<pii> q;  q.push({a, -1});
    int d=0;
    while(!q.empty()) {
        int sz=q.size();
        f(i, sz) {
            auto [u, p] = q.front(); q.pop();
            if(u==b) return d;
            for(int v : adj[u]) {
                if(v!=p) q.emplace(v, u);
            }
        }
        d++;
    }
    return INF;
};

function<pii(int)> furthest = [](int s) {
    queue<pii> q;  q.push({s, -1});
    int d=0; int node=-1;
    while(!q.empty()) {
        int sz=q.size();
        f(i, sz) {
            auto [u, p] = q.front(); q.pop();
            node=u;
            for(int v : adj[u]) {
                if(v != p) q.emplace(v, u);
            }
        }
        d++;
    }
    return make_pair(d-1, node);
};

void solve() {
    cin>>n>>a>>b>>da>>db;
    adj.assign(n+1, vi());
    f(i, n-1) {
        int u, v;
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int dist=bfs();
    auto [d1, x] = furthest(a);
    auto [diam, _] = furthest(x);
    // cout<<dist<<en<<x<<" "<<diam<<en;

    // Case 1: dist(a, b) <= da
    if(dist<=da) {
        cout<<"Alice"<<en; return;
    }

    // Case 2: 2*da >= diam;
    if(2*da >= diam) {
        cout<<"Alice"<<en; return;
    }

    // Case 3: db > 2*da
    if(db > 2*da) {
        cout<<"Bob"<<en;
    } else {
        cout<<"Alice"<<en;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin>>t;
    f(i, t) {
        solve();
    }
}