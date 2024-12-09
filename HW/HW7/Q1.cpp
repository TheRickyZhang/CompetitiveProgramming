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
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define trav(a, x) for (auto &a : x)
constexpr int MOD = 100000007; const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int p, c;
    while(cin >> p >> c){
        if(p == 0 && c == 0) break;

        vvi adj(p);
        f(i, c){
            int a, b; cin >> a >> b;
            adj[a].pb(b);
            adj[b].pb(a);
        }

        // timeFound (dfs from root), lowestNodeCanReach (=n, else through backedges)
        vector<int> found(p, -1), low(p, -1);
        int time = 0;
        bool hasBridge = false;

        // See backedges! Tarjan's algorithm
        function<void(int, int)> dfs = [&](int u, int parent) {
            time++;
            low[u] = found[u] = time; // Initialize first
            for(int v : adj[u]) {
                if(v == parent) continue;
                if(found[v] == -1) {
                    // tree edge - goes forward normally
                    dfs(v, u);
                    low[u] = min(low[u], low[v]); // Min= for any low values from back edges
                    if(low[v] > found[u]) hasBridge = true; // Only need existence of one here
                } else {
                    // back edge - remember this happens FIRST in the DFS so it will propogate in min= calls
                    low[u] = min(low[u], found[v]);
                }
            }
        };

        for(int i = 0; i < p; ++i){
            if(found[i] == -1){
                dfs(i, -1);
                if(hasBridge) break;
            }
        }

        cout << (hasBridge ? "Yes" : "No") << "\n";
    }
}