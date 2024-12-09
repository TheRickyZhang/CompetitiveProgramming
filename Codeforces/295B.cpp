// Floyd-Warshall

#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using pii = pair<int, int>;
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
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-97; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y,auto x,auto m,auto n) {return y >= 0 && y < m && x >= 0 && x < n; };

// NOTE - to not TLE need to add nodes up, use dp to reuse calculations
int main() {
#define int long long
    int n;
    cin >> n;
    vvi adj(n, vi(n, INF));

    // Read the initial adjacency matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
        }
    }

    // Set the diagonal to zero (distance from any node to itself is 0)
    for (int i = 0; i < n; ++i) {
        adj[i][i] = 0;
    }

    // Read nodes to be "deleted" in the forward direction
    vi add(n);
    for (int i = 0; i < n; ++i) {
        cin >> add[i];
    }
    reverse(add.begin(), add.end()); // Reverse to re-add nodes in reverse deletion order

    vector<int> results;

    // Set of nodes that are "active" in the current graph state
    unordered_set<int> active;

    // Incrementally add nodes and recompute shortest paths for each configuration
    for (int k = 0; k < n; ++k) {
        int x = add[k] - 1; // 0-based index
        active.insert(x);    // Add node back into the graph

        // Run Floyd-Warshall for the current subset of active nodes
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int m = 0; m < n; ++m) {
                    if (active.count(i) && active.count(j) && active.count(m)) {
                        if (adj[i][m] < INF && adj[m][j] < INF) {
                            adj[i][j] = min(adj[i][j], adj[i][m] + adj[m][j]);
                        }
                    }
                }
            }
        }


        // Sum the shortest paths between all pairs in the active set
        int res = 0;
        for (int i : active) {
            for (int j : active) {
                if (adj[i][j] < INF) {
                    res += adj[i][j];
                }
            }
        }

        results.push_back(res); // Store the result for this configuration
    }

    // Output results in reverse order to match original deletion order
    reverse(results.begin(), results.end());
    for(int res : results) cout<<res<<" ";

    return 0;
}