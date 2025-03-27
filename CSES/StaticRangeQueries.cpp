#include <bits/stdc++.h>
using namespace std;

// Coordinate compression + difference array
using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vvpii = vector<vpii>; using vpll = vector<pll>; using vvpll = vector<vpll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
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
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");
constexpr int MOD = 1000000007; constexpr ll INF = INT_MAX-37; constexpr ll INFL = 0x3f3f3f3f3f3f3f3f; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
constexpr char EN = '\n'; constexpr char SP = ' '; auto en = EN; auto sp = SP;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = enable_if_t<!is_same_v<T_container, string>, typename T_container::value_type>> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin>>n>>q;
    vector<tuple<int, int, int>> updates(n);
    vpii queries(q);
    vi indices;
    f(i, n) {
        int l, r, v; cin>>l>>r>>v;
        updates[i] = {l, r, v};
        indices.pb(l); indices.pb(r);
    }
    f(i, q) {
        int l, r; cin>>l>>r;
        queries[i] = {l, r};
        indices.pb(l); indices.pb(r);
    }
    sort(all(indices));
    indices.erase(unique(all(indices)), indices.end());

    int m=indices.size();
    ump<int, int> mp;
    f(i, m) {
        mp[indices[i]]=i;
    }

    vll diff(m, 0);
    for(auto [l, r, v] : updates) {
        diff[mp[l]] += v;
        diff[mp[r]] -= v;
    }
    f(i, m-1) diff[i+1] += diff[i];

    vll sz(m-1,0);
    f(i, m-1) {
        sz[i]=indices[i+1]-indices[i];
    }
    vll pre(m, 0);
    f(i, m-1) {
        pre[i+1] += pre[i] + diff[i]*sz[i]; // Prefix of the actual lengths;
    }

    // cout<<diff<<en<<sz<<en<<pre<<en;
    for(auto [l, r] : queries) {
        cout<<pre[mp[r]] - pre[mp[l]]<<en;
    }
}