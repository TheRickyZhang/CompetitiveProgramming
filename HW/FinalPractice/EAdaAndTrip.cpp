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

int main() {
    int n, m, qq;
    cin>>n>>m>>qq;
    vector<vpii> adj(n);
    f(i, m) {
        int u, v, c;
        cin>>u>>v>>c;
        adj[u].pb({c,v});
        adj[v].pb({c,u});
    }
    auto dijk = [&](int a) {
        vi dist(n, INF);
        vi count(n, 0);
        queue<pii> q;
        q.emplace(0, a);
        dist[a]=0; count[a]=1;
        while(!q.empty()) {
            auto [d, u] = q.front(); q.pop();
            if(d > dist[u]) continue;
            for(auto [dd, v] : adj[u]) {
                int nd=d+dd;
                if(nd==dist[v]) {
                    count[v]++;
                } else if(nd < dist[v]) {
                    dist[v]=nd;
                    count[v]=1;
                    q.emplace(nd, v);
                }
            }
        }
        int mx=0, mxc=0;
        f(i, n) {
            if(dist[i]==INF) continue;
            if(dist[i] > mx) {
                mx=dist[i];
                mxc=1;
            } else if(dist[i]==mx) {
                mxc++;
            }
        }
        cout<<mx<<" "<<mxc<<en;
    };
    f(i, qq) {
        int a; cin>>a;
        dijk(a);
    }
}