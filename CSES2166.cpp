#include <bits/stdc++.h>
using namespace std;

// Segment tree over prefix sum (want), use total sum+combine
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

const ll NEG_INF = -1e18;

// Node structure with only prefix sum and total sum
struct node {
    ll pre;
    ll sum;
    node() : pre(NEG_INF), sum(0) {}
    explicit node(ll a) : pre(a), sum(a) {}
    node(ll a, ll b) : pre(a), sum(b) {}
};

// Combine function for prefix sum
node combine(const node& a, const node& b) {
    ll newPre = max(a.pre, a.sum + b.pre);
    ll newSum = a.sum + b.sum;
    return node(newPre, newSum);
}

// Segment tree
const int MAXN = 200000;
vector<node> tree_st(4*MAXN);
vll nums;

// Build function
void build(ll i, ll a, ll b) {
    if(a == b){
        tree_st[i] = node(nums[a]);
    }
    else{
        ll m = (a + b) / 2;
        build(2*i, a, m);
        build(2*i+1, m+1, b);
        tree_st[i] = combine(tree_st[2*i], tree_st[2*i+1]);
    }
}

// Update function
void update_st(ll i, ll a, ll b, ll pos, ll val){
    if(a == b){
        tree_st[i] = node(val);
    }
    else{
        ll m = (a + b) / 2;
        if(pos <= m) update_st(2*i, a, m, pos, val);
        else update_st(2*i+1, m+1, b, pos, val);
        tree_st[i] = combine(tree_st[2*i], tree_st[2*i+1]);
    }
}

// Query function
node query_st(ll i, ll a, ll b, ll l, ll r){
    if(l > r) return node(NEG_INF, 0); // Sentinel node with invalid prefix
    if(a == l && b == r) return tree_st[i];
    ll m = (a + b) / 2;
    node x = query_st(2*i, a, m, l, min(r, m));
    node y = query_st(2*i+1, m+1, b, max(l, m+1), r);
    if(x.pre == NEG_INF) return y;
    if(y.pre == NEG_INF) return x;
    return combine(x, y);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, q;
    cin >> n >> q;
    nums.resize(n);
    f(i, n) cin >> nums[i];
    build(1, 0, n-1);
    while(q--){
        int t; ll r, s;
        cin >> t >> r >> s;
        if(t == 1){
            update_st(1, 0, n-1, r-1, s);
        }
        else{
            node res_node = query_st(1, 0, n-1, r-1, s-1);
            ll res = res_node.pre;
            if(res < 0) res = 0;
            cout << res << '\n';
        }
    }
    return 0;
}
