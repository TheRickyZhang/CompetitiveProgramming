#include <bits/stdc++.h>
using namespace std;

// This is basically the same problem as lowest common ancestor!
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

#include<bits/stdc++.h>
using namespace std;
#define SZ 200005

// Note: codeforces code + reversed so take with grain of salt. Use LCA
int n, m, k, x;
int L[SZ]; //level-array
vector<int> adj[SZ];
int jump[21][SZ];

void dfs(int u, int p, int l) {
    jump[0][u] = p;
    L[u] = l;

    for (int v: adj[u])
        if(v != p)
            dfs(v, u, l+1);
}

void preprocess_LCA() {
    dfs(1, -1, 0);

    for (int i = 1; 1<<i <= n ; i++)
        for (int j = 0; j <= n ; j++)
            jump[i][j] = jump[i-1][jump[i-1][j]];
}

int LCA(int p,int q) {
    if(L[p] < L[q])
        swap(p, q);

    int diff = L[p] - L[q];

    for(int i = 20; i >= 0; i--)
        if(diff & (1<<i))
            p = jump[i][p];

    if(p == q) return p;

    for (int i = 20; i >= 0; i--) {
        if (jump[i][p] != jump[i][q]) {
            p = jump[i][p];
            q = jump[i][q];
        }
    }
    return jump[0][p];
}

int main() {
    int u, v, q, a, b;
    cin >> n >> q;
    for(int i = 0; i < n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    preprocess_LCA();

    while(q--) {
        cin >> a >> b;
        int lca = LCA(a,b);
        cout << L[a] + L[b] - 2*L[lca] << endl;  // Key difference
    }
}