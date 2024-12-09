#include <bits/stdc++.h>
using namespace std;

// Segment tree over subarray sum (want), use subarray, prefix, suffix, and sum
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

struct node {
    ll any{};
    ll pre{};
    ll post{};
    ll cumSum{};
    node() : any(0), pre(0), post(0), cumSum(0) {}
    explicit node(ll a) : any(a), pre(a), post(a), cumSum(a) {}
    node(ll a, ll b, ll c, ll d) : any(a), pre(b), post(c), cumSum(d) {}
};

node combine(const node& a, const node& b) {
    ll newAny = max({a.any, b.any, a.post + b.pre});
    ll newPre = max(a.pre, a.cumSum + b.pre);
    ll newPost = max(b.post, b.cumSum + a.post);
    ll cumSum = a.cumSum + b.cumSum;
    return {newAny, newPre, newPost, cumSum};
}

const ll NINF = -1e18;
const ll N = 200000;
vector<node> tree(4*N);
vll nums(N);

void build(ll i, ll a, ll b) {
    if(a==b) tree[i] = node(nums[a]);
    else {
        ll m = (a+b)/2;
        build(2*i, a, m);
        build(2*i+1, m+1, b);
        tree[i] = combine(tree[2*i], tree[2*i+1]);
    }
}

void update(ll i, ll a, ll b, ll pos, ll val) {
    if(a==b) tree[i] = node(val);
    else {
        ll m = (a+b)/2;
        if(pos<=m) update(2*i, a, m, pos, val);
        else update(2*i+1, m+1, b, pos, val);
        tree[i] = combine(tree[2*i], tree[2*i+1]);
    }
}

node query(ll i, ll a, ll b, ll l, ll r) {
    if(l>r) return node(NINF); // Hopefully this is the same as a sentinel node
    if(a==l&&b==r) return tree[i];
    ll m = (a+b)/2;
    node x = query(2*i, a, m, l, min(r, m));
    node y = query(2*i+1, m+1, b, max(l, m+1), r);
    if(x.any == NINF) return y; if(y.any==NINF) return x;
    return combine(x, y);
}

int n, q;
int main() {
    cin>>n>>q;
    f(i, n) cin>>nums[i];
    build(1, 0, n-1);
    int t, r, s;
    f(i, q) {
        cin>>t>>r>>s;
        if(t==1) {
            update(1, 0, n-1, r-1, s);
        } else {
            ll res = query(1, 0, n-1, r-1, s-1).any;
            if(res < 0) res = 0;
            cout<<res<<en;
        }
    }
    return 0;
}