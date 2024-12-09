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
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
constexpr int MOD = 1000000007; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n'; constexpr char sp = ' ';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

constexpr int N = 100000;
ll t, n, m, k, a, b;
vll tree;
vll lazy;
vll nums;
constexpr ll INF = LLONG_MAX;

void build(ll i, ll a, ll b) {
    if(a==b) tree[i]=nums[a];
    else {
        int m=a+(b-a)/2;
        build(2*i, a, m);
        build(2*i+1, m+1, b);
        tree[i] = min(tree[2*i], tree[2*i+1]);
    }
}
ll query(ll i, ll a, ll b, ll l, ll r) {
    if(lazy[i]!=0) {
        tree[i]+=lazy[i];
        if(a!=b) {
            lazy[2*i] += lazy[i];
            lazy[2*i+1] += lazy[i];
        }
        lazy[i]=0;
    }
    if(a > r || b < l || r<l) return INF;
    if(l<=a && b<=r) return tree[i];
    ll m=a+(b-a)/2;
    return min(query(2*i, a, m, l, r), query(2*i+1, m+1, b, l, r));
}
void update(ll i, ll a, ll b, ll l, ll r, ll val) {
    if(lazy[i] != 0) {
        tree[i] += lazy[i];  // NOTE: Because is a min seg tree can do this, otherwise would need to add (b-a+1 * lazy[i])
        if(a!=b) {
            lazy[2*i] += lazy[i];
            lazy[2*i+1] += lazy[i];
        }
        lazy[i]=0;
    }
    if(a>r||b<l||r<l) return;
    if(l<=a && b<=r) {
        tree[i]+=val;
        if(l!=r) {
            lazy[2*i] += val;
            lazy[2*i+1] += val;
        }
        return;
    }
    ll m= a+(b-a)/2;
    update(2*i, a, m, l, r, val);
    update(2*i+1, m+1, b, l, r, val);
    tree[i]=min(tree[2*i], tree[2*i+1]);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    nums.resize(n);
    f(i, n) cin >> nums[i];

    // Increase the size of tree and lazy arrays
    tree.assign(4*n, 0);
    lazy.assign(4*n, 0);
    build(1, 0, n-1);

    cin >> m; cin.ignore();
    f(i, m) {
        string s; getline(cin, s);
        if(s.empty()) continue;
        vll v;
        istringstream iss(s);
        ll var;
        while (iss >> var) v.push_back(var);
        ll l=v[0], r=v[1];
        if(v.size()==3) {
            if(l>r) {
                update(1, 0, n-1, l, n-1, v[2]);
                update(1, 0, n-1, 0, r, v[2]);
            } else {
                update(1, 0, n-1, l, r, v[2]);
            }
        } else if(v.size()==2) {
            if(l>r) cout << min(query(1, 0, n-1, l, n-1), query(1, 0, n-1, 0, r)) << en;
            else cout << query(1, 0, n-1, l, r) << en;
        } else {
            cout << "HUH" << en;
        }
    }
}
