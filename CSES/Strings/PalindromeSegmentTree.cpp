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
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-37; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

constexpr int N = 100000;
ll t, n, m, a, b;
string s;

struct Node {
    ll fhash;
    ll bhash;
    int len;
};
vector<Node> tree;
vll power;

Node merge(Node l, Node r) {
    Node res;
    res.len = l.len+r.len;
    res.fhash = (l.fhash + r.fhash*power[l.len]) % MOD;
    res.bhash = (r.bhash + l.bhash*power[r.len]) % MOD;
    return res;
}

int h(char c) {
    return c-'a'+1;
}
void build(int i, int a, int b) {
    if(a==b) tree[i] = {h(s[a]), h(s[a]), 1};
    else {
        int m = (a+b)/2;
        build(2*i, a, m);
        build(2*i+1, m+1, b);
        tree[i] = merge(tree[2*i], tree[2*i+1]);
    }
}

void update(int i, int a, int b, int pos, char val) {
    if(a==b) tree[i] = {h(val), h(val), 1};
    else {
        int m = (a+b)/2;
        if(pos <= m) update(2*i, a, m, pos, val);
        else update(2*i+1, m+1, b, pos, val);
        tree[i] = merge(tree[2*i], tree[2*i+1]);
    }
}

Node query(int i, int a, int b, int l, int r) {
    if(r<a || b<l) return {0, 0, 0};
    if(l<=a && b<=r) return tree[i];
    int m = (a+b)/2;
    Node left = query(2*i, a, m, l, r);
    Node right = query(2*i+1, m+1, b, l, r);
    return merge(left, right);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    cin>>s;
    tree.resize(4*n);
    power.resize(n+1, 1);
    for(int i = 1; i<=n; ++i) {
        power[i]=(power[i-1]*31) % MOD;
    }

    build(1, 0, n-1);
    f(i, m) {
        int t; cin>>t;
        if(t==1) {
            int k; char x; cin>>k>>x;
            update(1, 0, n-1, k-1, x);
        } else {
            int a, b; cin>>a>>b;
            auto res = query(1, 0, n-1, a-1, b-1);
            if(res.fhash == res.bhash) {
                cout<<"YES"<<en;
            } else {
                cout<<"NO"<<en;
            }
        }
    }
    return 0;
}
