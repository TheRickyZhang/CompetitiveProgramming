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
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-5; const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };

int main() {
    int n; cin >> n;
    vvi adj(1000);
    vvi cap(1000, vi(1000, 0));
    ump<int, int> mp;
    vi nums(n);
    f(i, n) cin >> nums[i];
    sort(all(nums));
    f(i, n) {
        mp[nums[i]] = i;
        f(j, i) {
            int g = gcd(nums[i], nums[j]);
            if(g > 1) {
                cap[i][j] = g;
                cap[j][i] = g;
                adj[i].pb(j);
                adj[j].pb(i);
            }
        }
    }
    auto bfs = [&](int a, int b, vi& parents) {
        fill(all(parents), -1);
        parents[a] = -2;
        queue<pii> q;
        q.push({a, INF});
        while(!q.empty()) {
            auto[u, flow] = q.front(); q.pop();
            for(int v : adj[u]) {
                if(parents[v] != -1 || cap[u][v] == 0) continue;
                parents[v] = u;
                int nflow = min(flow, cap[u][v]);
                if(v == b) return nflow;
                q.push({v, nflow});
            }
        }
        return 0;
    };
    auto maxflow = [&](int a, int b) {
        vi parents(n);
        int flow = 0;
        int nflow;
        while(true) {
            nflow = bfs(a, b, parents);
            if(nflow == 0) break;
            flow += nflow;
            int curr = b;
            while(curr != a) {
                int prev = parents[curr];
                cap[prev][curr] -= nflow;
                cap[curr][prev] += nflow;
                curr = prev;
            }
        }
        return flow;
    };
    int res = maxflow(0, n-1);
    cout << res << en;
}