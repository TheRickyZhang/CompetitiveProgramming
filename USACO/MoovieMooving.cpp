#include <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define repr(i, a, b) for (int i = (a); i >= (b); --i)
#define str string
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");
tpl_<tn_ T>        using v = vector<T>;  using ll=long long;  using pii=pair<int,int>;  using pll=pair<ll,ll>;  using t3=tuple<int,int,int>;       using t4=tuple<int,int,int,int>;
using vi=v<int>;   using vb=v<bool>;     using vvb=v<vb>;     using vs=v<string>;       using vvi=v<vi>;        using vll=v<ll>;using vvll=v<vll>; using vpii=v<pii>; using vvpii=v<vpii>; using vpll=v<pll>; using vvpll=v<vpll>;
tpl_<tn_ K,tn_ T>  using ump=unordered_map<K, T>;  tpl_<tn_ T>using ust=unordered_set<T>;  tpl_<tn_ K,tn_ T>    using rmap=map<K,T,greater<K>>; tpl_<tn_ T> using rset=set<T,greater<T>>; tpl_<tn_ T> using mset=multiset<T>; tpl_<tn_ T>using rmset=multiset<T,greater<T>>;
tpl_<tn_ T>        using pq=priority_queue<T>;     tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;
tpl_<class It, class T>     auto leq_bound  (It first, It last, T val) { auto it = upper_bound(first, last, val); return it != first ? prev(it) : last;} tpl_<class C, class T>auto leq_bound(C& c, T val) {auto it = c.upper_bound(val);return it != c.begin() ? prev(it) : c.end();}
tpl_<class It, class T>     auto less_bound (It first, It last, T val) {auto it = lower_bound(first, last, val);return it != first ? prev(it) : last; }tpl_<class C, class T>auto less_bound(C& c, T val) {auto it = c.lower_bound(val);return it != c.begin() ? prev(it) : c.end();}
tpl_<class C, class T>      auto lower_bound(C& c, T val) {return c.lower_bound(val);} tpl_<class C, class T>auto upper_bound(C& c, T val) {return c.upper_bound(val);}
tpl_<tn_ A, tn_ B> ostream& operator<<(ostream& os, const pair<A, B>& p){ return os<<"("<<p.ff<<", "<<p.ss<<")";}
tpl_<tn_ A> ostream&        operator<<(ostream& os, const v<v<A>>& v)   { for (const auto& row : v) { os << "{ "; for (const auto& elem : row) {os<<elem<<" ";}os<<"}"; } return os;}
tpl_<tn_ K, tn_ T> ostream& operator<<(ostream& os, const map<K, T>& m) { os << "{"; str sep; for (const auto& kv : m) os << sep << kv.ff << ": " << kv.ss, sep = ", "; return os << "}"; }
tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, str>, typename C::value_type>> ostream& operator<<(ostream& os, const C& v) { os<<"{"; str sep; for(const T& x : v) os<<sep<<x, sep=", "; return os<<"}";}
vector<pii> dirs={{1,0},{0,-1},{0,1},{-1,0}}; map<char, int> dirMap={{'E',0},{'S',1},{'N',2},{'W',3}}; auto check=[](auto y,auto x,auto m,auto n){return y>=0&&y<m&&x>=0&&x<n;};
struct pairHash{tpl_<class T1,class T2>size_t operator()(const pair<T1,T2>&p)const{return hash<T1>{}(p.first)^ (hash<T2>{}(p.second)<<1);}}; struct vectorHash{tpl_<class T>size_t operator()(const vector<T>&v)const{size_t hashTalue=0;for(const T&i:v)hashTalue^=hash<T>{}(i)+0x9e3779b9+(hashTalue<<6)+(hashTalue>>2);return hashTalue;}};
struct DSU{ vi p,sz; explicit
         DSU(const int n){p.resize(n),sz.resize(n,1),iota(all(p),0);}
    int  par(int x){return x==p[x]?x:p[x]=par(p[x]);}
    void merge(int x,int y){x=par(x),y=par(y);if(x!=y){if(sz[x]<sz[y])swap(x,y);p[y]=x,sz[x]+=sz[y];}}
};
template <typename T> struct Segtree { ll n; v<T> t; T z; function<T(T, T)> c;
         Segtree(ll sz, T zero, function<T(T, T)> combine) : n(sz), t(4 * sz, zero), z(zero), c(move(combine)) {}
    void update(ll i, ll a, ll b, ll p, T x) { if (a == b) { t[i] = x; return; } ll m = (a + b) / 2; (p <= m ? update(2 * i, a, m, p, x) : update(2 * i + 1, m + 1, b, p, x)); t[i] = c(t[2 * i], t[2 * i + 1]); } void update(ll p, T x) { update(1, 0, n - 1, p, x); }
    T    query(ll i, ll a, ll b, ll l, ll r) { if (l > r) return z; if (a == l && b == r) return t[i]; ll m = (a + b) / 2; return c(query(2 * i, a, m, l, min(r, m)), query(2 * i + 1, m + 1, b, max(l, m + 1), r)); } T query(ll l, ll r) { return query(1, 0, n - 1, l, r); }
};
template <typename T> struct BIT { ll n; v<T> t; T z; function<T(T, T)> c;
         BIT(ll sz, T zero, function<T(T, T)> combine) : n(sz), t(sz + 1, zero), z(zero), c(move(combine)) {}
    void update(ll i, T x) {for (; i<=n; i+=(i & -i)) {t[i] = c(t[i], x);}} T query(ll i) {T res = z; for (; i > 0; i -= (i & -i)) { res = c(res, t[i]); }return res;}
    T    query(ll l, ll r) {return c(query(r), l>1 ? query(l - 1) : z);}
};
template<class T, class U> T fstTrue(T l, T r, U ff) { while (l<r) { T m = (l + r)/2; ff(m) ? r=m : l = m+1; } return ff(l) ? l : r+1; }
template<class T, class U> T lstTrue(T l, T r, U ff) { while (l<r) { T m = (l+r+1)/2; ff(m) ? l=m : r = m-1; } return ff(l) ? l : r+1; }
template<class T> bool       ckmn(T& a, const T& b) {return b < a ? a = b, 1 : 0;}  template<class T> bool ckmx(T& a, const T& b) {return a < b ? a = b, 1 : 0;}
    ll N = 5000; ll MOD=1e9+7; constexpr int INF=1e9; constexpr ll INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";
ll ceil(ll num, ll den) { return (num + den - 1) / den; } ll fastPow(ll a, ll b, ll mod = MOD) { ll res = 1; a %= mod; while (b > 0) { if (b & 1) res = res * a % mod; a = a * a % mod; b >>= 1; } return res; }
vb sieve(const int n){vb p(n+1,true);p[0]=p[1]=false;for(int i=2;i*i<=n;++i)if(p[i])for(int j=i*i;j<=n;j+=i)p[j]=false;return p;} vll sieveList(int n){vb p=sieve(n);vll primes;for(int i=2;i<=n;++i)if(p[i])primes.pb(i);return primes;}
struct mint { ll val; // Avg 2x slowdown over raw % operations
    mint(ll v=0) : val((v%MOD+MOD)%MOD) {} // NOLINT(google-explicit-constructor) (We want mint = 5 to be treated like int)
    mint operator+(const mint& o) const { return mint(val + o.val >= MOD ? val + o.val - MOD : val + o.val); } mint operator-(const mint& o) const { return mint(val - o.val < 0 ? val - o.val + MOD : val - o.val); }
    mint operator*() const { return mint(val); } mint operator*(const mint& o) const { return mint(val * o.val % MOD); } mint operator/(const mint& o) const { return *this * fastPow(o.val, MOD-2); }
    friend ostream& operator<<(ostream& os, const mint& m) { return os << m.val; } bool operator<(const mint& o) const { return val < o.val; } bool operator<=(const mint& o) const { return val <= o.val; }
    mint& operator+=(const mint& o) { val = (val + o.val >= MOD ? val + o.val - MOD : val + o.val); return *this; } mint& operator-=(const mint& o) { val = (val - o.val < 0 ? val - o.val + MOD : val - o.val); return *this; }
};

int t, k, n, m;
#include <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define repr(i, a, b) for (int i = (a); i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
tpl_<tn_ T> using v = vector<T>;
using vi = v<int>;
using vvi = v<vi>;
using pii = pair<int, int>;
using ll = long long;
constexpr int INF = 1e9;
constexpr auto en = "\n";

// Bitmask helpers
inline bool inSubset(int mask, int bit) { return mask & (1 << bit); }
inline int addToSubset(int mask, int bit) { return mask | (1 << bit); }
inline int popCount(int x) { return __builtin_popcount(x); }

// Function to find the next valid show index
int findShowTime(int t, vi &sched, int length) {
    auto it = upper_bound(all(sched), t);
    if (it == sched.begin()) return -1;
    int start = *(--it);
    return (start + length >= t) ? (it - sched.begin()) : -1;
}

void solve() {
    int n, L;
    cin >> n >> L;

    vi len(n); // Movie lengths
    vvi sched(n); // Schedules for each movie
    v<vvi> next(n, vvi(n)); // Precomputed next-show table

    // Input reading
    f(i, n) {
        int f; // Frequency of showtimes
        cin >> len[i] >> f;
        sched[i].resize(f);
        f(j, f) cin >> sched[i][j];
    }

    // Precomputing next-show table
    f(i, n) f(j, n) if (i != j) {
        next[i][j].resize(sched[i].size());
        f(k, sched[i].size()) {
            next[i][j][k] = findShowTime(sched[i][k] + len[i], sched[j], len[j]);
        }
    }

    // DP table: dp[mask] = {last movie, index in schedule}
    v<pii> dp(1 << n, {-1, -1});
    dp[0] = {0, 0};
    int ans = n + 1;

    // DP over subsets
    f(mask, 1 << n) {
        auto [lastMovie, lastIdx] = dp[mask];
        if (lastMovie == -1) continue;

        f(j, n) {
            if (inSubset(mask, j)) continue; // Skip already-watched movies
            int newMask = addToSubset(mask, j);

            int showIdx = (mask == 0) ? (sched[j][0] == 0 ? 0 : -1)
                                      : next[lastMovie][j][lastIdx];

            if (showIdx == -1) continue;

            // Update dp[newMask] if we extend coverage
            auto &[curMovie, curIdx] = dp[newMask];
            int newEnd = sched[j][showIdx] + len[j];
            if (curMovie == -1 || sched[curMovie][curIdx] + len[curMovie] < newEnd) {
                dp[newMask] = {j, showIdx};
            }

            // Check if this subset covers at least L time
            if (sched[dp[newMask].ff][dp[newMask].ss] + len[dp[newMask].ff] >= L) {
                ans = min(ans, popCount(newMask));
            }
        }
    }

    cout << (ans == n + 1 ? -1 : ans) << en;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}

//
// int main() {
//     ios::sync_with_stdio(false); cin.tie(nullptr);
//     cin>>n>>k;
//     vi len(n);
//     vvi sched(n); // # showings
//     v<vvi> next(n, vvi(n)); // # showings
//     f(i, n) {
//         int l, f; cin>>l>>f;
//         len[i]=l;
//         f(j, f) {
//             int x; cin>>x;
//             sched[i].pb(x);
//         }
//     }
//     auto findShow = [&](int end, int pos) {
//         vi begins = sched[pos];
//         return fstTrue(0, static_cast<int>(begins.size()-1), [&](int i) {
//            return begins[i] <= end && begins[i] + len[pos] >= end;
//         });
//     };
//     f(i, n) {
//         f(j, n) {
//             if(i==j) continue;
//             f(ii, sched[i].size()) {
//                 next[i][j].pb(findShow(sched[i][ii] + len[i], j));
//             }
//         }
//     }
//
//     // dp[x] = {last movie, idx}
//     vpii dp(1<<n, {-1, -1});
//     int res = n+1;
//     dp[0] = {0, 0};
//
//     f(i, 1<<n) {
//         auto [mov, pos] = dp[i];
//         if(mov == -1) continue;
//         f(j, n) {
//             if(i & (1<<j)) continue;
//             // Not in subset;
//
//             int x = next[mov][j][pos];
//         }
//     }
// }