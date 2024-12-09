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
ll n, q;
vll nums(N);
vll tree(4*N);

void build(ll i, ll a, ll b) {
    if(a==b) {
        tree[i] = nums[a];
        return;
    }
    ll mid = a+(b-a)/2;
    build(2*i, a, mid);
    build(2*i+1, mid+1, b);
    tree[i] = tree[2*i] + tree[2*i+1];
}

void update(ll i, ll a, ll b, ll pos, ll x) {
    if(a==b) tree[i] = x;
    else {
        ll m = a+(b-a)/2;
        if(pos <= m) update(2*i, a, m, pos, x);
        else update(2*i+1, m+1, b, pos, x);
        tree[i] = tree[2*i]+tree[2*i+1];
    }
}

ll query(ll i, ll a, ll b, ll l, ll r) {
    if(l>r) return 0;
    if(a==l && b==r) return tree[i];
    ll m = a+(b-a)/2;
    return query(2*i, a, m, l, min(r, m)) + query(2*i+1, m+1, b, max(l,m+1), r);
}

int main() {
    cin>>n>>q;
    f(i, n) cin>>nums[i];

    build(1, 0, n-1);

    ll t, a, b;
    f(i, q) {
        cin>>t>>a>>b;
        if(t==1) {
            update(1, 0, n-1, a-1, b);
        } else {
            cout<<query(1, 0, n-1, a-1, b-1)<<en;
        }
    }
    return 0;
}