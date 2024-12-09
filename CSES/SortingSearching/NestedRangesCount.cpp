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
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-37; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n'; constexpr char sp = ' ';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

vi t; // This is a DIFFERENCE ARRAY for availalble r
int n;
int m; // NUmber of unique r. <= n
void update(int i, int x) {
    while(i<=m) {
        t[i]+=x;
        i+=(i&-i);
    }
}
int sum(int i) {
    int res=0;
    while(i>0) {
        res+=t[i];
        i-=(i&-i);
    }
    return res;
}
struct node {
    int l;
    int r;
    int i;
};
bool compare(node& a, node& b) {
    if(a.l==b.l) return a.r>b.r; // NOTE: DESCENDING here to preserve well-ordering
    return a.l<b.l;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vector<node> v(n);
    t.assign(n+1, 0);
    set<int> ends;
    map<int, int> mp; // Maps from r -> normalized rank (among r's)
    f(i, n) {
        int a, b; cin>>a>>b;
        v[i] = {a, b, i};
        ends.insert(b);
    }
    m=0;
    for(auto x : ends) {
        mp[x] = ++m; // 1-indexed here
    }
    sort(all(v), compare);

    // Start from the back because HIGH L = more restrictive of ranges it can contain
    vi res(n, 0);
    for(int i=n-1; i>=0; --i) {
        int rank = mp[v[i].r];
        res[v[i].i] += sum(rank); // Want to add everything <= current rank
        update(rank, 1);      // Only add current rank afterward because it is available based on left bounds
    }
    f(i, n) cout<<(res[i]>0 ? 1 : 0)<<" ";
    cout<<en;

    res.assign(n, 0);
    t.assign(n+1, 0);
    // Note that 1 is arbitrarily used here because any end < r is guaranteed to be valid. lmp[v[i].l  may be more accurate but this is simple
    for(int i=0; i<n; ++i) {
        int rank=mp[v[i].r];
        res[v[i].i] += sum(rank);
        update(1, 1); update(rank+1, -1); // This works because it is a difference array!
    }
    f(i, n) cout<<(res[i]>0 ? 1 : 0)<<" ";
    cout<<en;
}
