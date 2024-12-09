#include <bits/stdc++.h>
using namespace std;

// Much harder than it seems, with strings and input handling adding much complexity
// Use FLOYD-WARSHALL to find cycles!!!! As adj[i][i] = INF at first
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


ll fastPow(ll x, ll p) {
    ll res = 1;
    ll curr = 1;
    while(p > 0) {
        if(p%2==1) curr *= x;
        curr = (curr*curr) % MOD;
        p >>= 1;
    }
    return res;
}

int solve() {
    int n; cin>>n;
    vvi nums(2, vi(n, 0));
    f(i, n) cin>>nums[0][i];
    f(i, n) cin>>nums[1][i];

    int pow = 0;
    vvi ps(n+1, vi(n+1, 0));
    f(i, n) {
        int a = nums[0][i], b=nums[1][i];
        ps[a][b]++; ps[b][a]++;
    }
    f(i, n+1) {
        f(j, i) {
            pow += ps[i][j];
        }
    }
    cout<<fastPow(2, pow)<<en;
}
int main() {
    int t; cin>>t;
    f(i, t) {
        solve();
    }
}