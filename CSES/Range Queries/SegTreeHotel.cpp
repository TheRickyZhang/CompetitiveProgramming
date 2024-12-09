#include <bits/stdc++.h>
using namespace std;

// Hotel Queries
// Application of segment tree
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

#define N 200000
vll tree(4*N);
vll nums(N);
ll n, m, x;

void build(ll i, ll l, ll r) {
    if(l==r) tree[i] = nums[l];
    else {
        ll m = l+(r-l)/2;
        build(2*i, l, m);
        build(2*i+1, m+1, r);
        tree[i] = max(tree[2*i], tree[2*i+1]);
    }
}

// val is the amount to be subtraced off
void update(ll i, ll l, ll r, ll pos, ll val) {
    if(l==r) {
        tree[i] = val;
        nums[l] = val;
    } else {
        ll m = (l+r) / 2;
        if(pos <= m) update(2*i, l, m, pos, val);
        else update(2*i+1, m+1, r, pos, val);
        tree[i] = max(tree[2*i], tree[2*i+1]);
    }
}

// returns the pos
ll query(ll i, ll l, ll r, ll val) {
    if(tree[i] < val) return -1;
    if(l==r) return l;
    ll m = (r+l)/2;
    if(tree[2*i] >= val) return query(2*i, l, m, val);
    return query(2*i+1, m+1, r, val);
}

int main() {
    cin>>n>>m;
    f(i, n) cin>>nums[i];
    build(1, 0, n-1);

    vll queries(m);
    f(i, m) cin>>queries[i];
    for(ll x : queries) {
        ll idx = query(1, 0, n-1, x);
        if(idx == -1) {
            cout<<0<<en;
        } else {
            cout<<idx+1<<en;
            ll diff = nums[idx] - x;
            update(1, 0, n-1, idx, diff);
        }
    }
    return 0;
}
