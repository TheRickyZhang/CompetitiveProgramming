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
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-5; const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };
// Define N based on problem constraints
#define N 10000

int n, e, q, b;

struct Edge {
    int to;
    int base;      // t0
    int interval;  // p
    int dur;  // d
};
vector<vector<Edge>> adj;
int early[N]; // earliest arrivals

void solve() {
    adj.assign(n, vector<Edge>());
    int u,v,t,p,d;
    f(i, e) {
        cin>>u>>v>>t>>p>> d;
        adj[u].pb(Edge{v, t, p, d});
    }
    f(i, q) {
        int a;
        cin >> a;
        priority_queue<pii, vpii, greater<>> pq;
        pq.push({0, b});
        fill_n(early, n, INF);
        early[b] = 0;

        bool isValid = true;
        while (!pq.empty() && isValid) {
            auto [time, from] = pq.top(); pq.pop();
            if (from == a) {
                cout << time << en;
                isValid = false;
                continue;
            }
            if (time > early[from]) continue; // Use time as visited
            for (const auto& edge : adj[from]) {
                int to = edge.to;
                int base = edge.base;
                int interval = edge.interval;
                int dur = edge.dur;

                int leaveTime;
                // need separate case for 0
                if(interval == 0){
                    if(time <= base) { leaveTime = base; }
                    else continue;
                }
                else{
                    if(time <= base) leaveTime = base;
                    else{
                        // interval * floor(time-base) + base
                        leaveTime = base + (time - base + interval-1) / interval * interval;
                    }
                }

                // use curr + dur strategy for pq-ing rather than just curr
                int arriveTime = leaveTime + dur;
                if(arriveTime < early[to]){
                    early[to] = arriveTime; // update arrival time
                    pq.push({arriveTime, to});
                }
            }
        }
        if (isValid) cout << "Impossible" << en;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> e >> q >> b) {
        if (n == 0) break;
        solve();
    }
    return 0;
}