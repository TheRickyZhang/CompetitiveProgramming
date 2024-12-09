#include <bits/stdc++.h>
using namespace std;

// Greedy DSU on two graphs simultaneously. Don't forget x = getParent(a), not p[a]
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

int n, m1, m2;
int p[2][1000];
int sz[2][1000];
int getp(int id, int x) {
    if(p[id][x] == x) return x;
    return p[id][x] = getp(id, p[id][x]);
}
// merges both
void merge(int id, int a, int b) {
    int x = getp(id, a);
    int y = getp(id, b);
    if(x == y) return;
    if(sz[id][x] < sz[id][y]) swap(x, y);
    p[id][y] = x;
    sz[id][x] += sz[id][y];
}

int main() {
    cin>>n>>m1>>m2;
    f(i, n) {
        sz[0][i] = 1; sz[1][i] = 1;
    }
    f(i, n) {
        p[0][i] = i; p[1][i] = i;
    }

    vector<vb> edges(n, vb(n, true));
    f(i, m1) {
        int u,v;
        cin>>u>>v; u--; v--;
        merge(0, u, v);
        edges[u][v] = true;
    }
    f(i, m2) {
        int u,v;
        cin>>u>>v; u--; v--;
        merge(1, u, v);
        edges[u][v] = true;
    }
    vpii res;
    f(i, n) {
        f(j, n) {
            if(i >= j || !edges[i][j]) continue;
            if(getp(0, i) != getp(0, j) && getp(1, i) != getp(1, j)) {
                merge(0, i, j); merge(1, i, j);
                res.pb({i,j});
            }
        }
    }
    cout<<res.size()<<en;
    for(auto [i,j] : res) {
        cout<<i+1<<" "<<j+1<<en;
    }
    return 0;
}