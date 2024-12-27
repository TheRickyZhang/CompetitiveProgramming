#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vvpii = vector<vpii>; using vpll = vector<pll>; using vvpll = vector<vpll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
using vvi = vector<vector<int>>; using vvll = vector<vector<ll>>; using mpq = priority_queue<ll, vector<ll>, greater<>>; using mpqq = priority_queue<pll, vpll, greater<>>;
#define ump unordered_map
#define ust unordered_set
#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
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

constexpr int N = 100000;
ll t, n, m, k, a, b;

// Probably a cleaner solution than provided ones; easiest to visualize sliding window
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>k>>m>>n;
    vpll grass(k);
    f(i, k) cin>>grass[i].ff>>grass[i].ss;
    sort(all(grass));
    set<ll> evil;
    f(i, m) {
        ll x; cin>>x; evil.insert(x);
    }
    pq q;
    ll i=0;
    while(i<k){
        auto[l, val] = grass[i];
        if(evil.count(l)) break;                         // Cannot beat a distance of 0
        ll curr = val;                                   // most taste with 1 cow

        auto it = evil.upper_bound(l);
        ll lower = it==evil.begin() ? -INF : *prev(it);  // Left will not change
        ll upper=-INF;

        while(++i<k) {                                   // Keep updating right
            auto [r, v] = grass[i];
            auto lit = evil.upper_bound(l);
            auto rit = evil.lower_bound(r);
            upper = max(upper, rit==evil.end() ? INF : *rit);

            // ---(lower <=)--l-----r--(upper>=)---
            // If upper-r + l-lower >= r-l, or there is a point between l and r, then cannot cover l and r
            if(upper-lower <= 2*(r-l) || (lit!=evil.end() && *lit <=r)) break;
            curr += v;
        }
        if(curr) q.push(curr);
    }
    ll res=0;
    while(n-- && q.size()) {
        res += q.top(); q.pop();
    }
    cout<<res<<en;
}