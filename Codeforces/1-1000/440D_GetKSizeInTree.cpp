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
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");

#define int long long
tpl_<tn_ T>        using v = vector<T>;  using ll=long long;  using pii=pair<int,int>;  using pll=pair<ll,ll>;  using iii=tuple<int,int,int>;       using t4=tuple<int,int,int,int>;
using vi=v<int>;   using vb=v<bool>;     using vvb=v<vb>;     using vs=v<string>;       using vvi=v<vi>;        using vll=v<ll>;using vvll=v<vll>; using vpii=v<pii>; using vvpii=v<vpii>; using vpll=v<pll>; using vvpll=v<vpll>;
tpl_<tn_ K,tn_ T>  using ump=unordered_map<K, T>;  tpl_<tn_ T>using ust=unordered_set<T>;  tpl_<tn_ K,tn_ T>    using rmap=map<K,T,greater<K>>; tpl_<tn_ T> using rset=set<T,greater<T>>; tpl_<tn_ T> using mset=multiset<T>; tpl_<tn_ T>using rmset=multiset<T,greater<T>>;
tpl_<tn_ T>        using pq=priority_queue<T>;     tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;
tpl_<class It, class T>     auto leq_bound  (It first, It last, T val) { auto it = upper_bound(first, last, val); return it != first ? prev(it) : last;} tpl_<class C, class T>auto leq_bound(C& c, T val) {auto it = c.upper_bound(val);return it != c.begin() ? prev(it) : c.end();}
tpl_<class It, class T>     auto less_bound (It first, It last, T val) {auto it = lower_bound(first, last, val);return it != first ? prev(it) : last; }tpl_<class C, class T>auto less_bound(C& c, T val) {auto it = c.lower_bound(val);return it != c.begin() ? prev(it) : c.end();}
tpl_<class C, class T>      auto lower_bound(C& c, T val) {return c.lower_bound(val);} tpl_<class C, class T>auto upper_bound(C& c, T val) {return c.upper_bound(val);}
tpl_<tn_ A, tn_ B> ostream& operator<<(ostream& os, const pair<A, B>& p){ return os<<"("<<p.ff<<", "<<p.ss<<")";}
tpl_<tn_ A> ostream&        operator<<(ostream& os, const v<v<A>>& v)   { for (const auto& row : v) { os << "{ "; for (const auto& elem : row) {os<<elem<<" ";}os<<"}"; os<<"\n";} return os;}
tpl_<tn_ K, tn_ T> ostream& operator<<(ostream& os, const map<K, T>& m) { os << "{"; string sep; for (const auto& kv : m) os << sep << kv.ff << ": " << kv.ss, sep = ", "; return os << "}"; }
tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, string>, typename C::value_type>> ostream& operator<<(ostream& os, const C& v) { os<<"{"; string sep; for(const T& x : v) os<<sep<<x, sep=", "; return os<<"}";}
vector<pii> dirs={{1,0},{0,-1},{0,1},{-1,0}}; map<char, int> dirMap={{'E',0},{'S',1},{'N',2},{'W',3}}; auto check=[](auto y,auto x,auto m,auto n){return y>=0&&y<m&&x>=0&&x<n;};
struct pairHash{tpl_<class T1,class T2>size_t operator()(const pair<T1,T2>&p)const{return hash<T1>{}(p.first)^ (hash<T2>{}(p.second)<<1);}}; struct vectorHash{tpl_<class T>size_t operator()(const vector<T>&v)const{size_t hashTalue=0;for(const T&i:v)hashTalue^=hash<T>{}(i)+0x9e3779b9+(hashTalue<<6)+(hashTalue>>2);return hashTalue;}};
struct DSU{ vi p,sz; explicit
         DSU(const int n){p.resize(n),sz.resize(n,1),iota(all(p),0);}
    int  par(int x){return x==p[x]?x:p[x]=par(p[x]);}
    void merge(int x,int y){x=par(x),y=par(y);if(x!=y){if(sz[x]<sz[y])swap(x,y);p[y]=x,sz[x]+=sz[y];}}
};
tpl_<tn_ T> struct Segtree { int n; v<T> t, nums; T z; function<T(T, T)> c;
    Segtree() : n(0), z(0), c([](T a, T b) { return a + b; }) {}
    Segtree(int sz, T zero, function<T(T, T)> combine, const v<T>& init = {}) : n(sz), t(4 * sz, zero), nums(sz, zero), z(zero), c(move(combine)) { if (!init.empty()) { nums = init; build(1, 0, n - 1); } }
    void build(int i, int a, int b) { if (a == b) { t[i] = nums[a]; return; } int m = (a + b) / 2; build(2 * i, a, m); build(2 * i + 1, m + 1, b); t[i] = c(t[2 * i], t[2 * i + 1]); }
    void add(int i, int a, int b, int p, T x) { if (a == b) { t[i] += x; return; } int m = (a + b) / 2; (p <= m ? add(2 * i, a, m, p, x) : add(2 * i + 1, m + 1, b, p, x)); t[i] = c(t[2 * i], t[2 * i + 1]); }
    void update(int i, int a, int b, int p, T x) { T diff = x - nums[p]; nums[p] = x; add(1, 0, n - 1, p, diff); }
    T query(int i, int a, int b, int l, int r) { if (l > r) return z; if (a == l && b == r) return t[i]; int m = (a + b) / 2; return c(query(2 * i, a, m, l, min(r, m)), query(2 * i + 1, m + 1, b, max(l, m + 1), r)); }
    void add(int p, T x) { add(1, 0, n - 1, p, x); }
    void update(int p, T x) { update(1, 0, n - 1, p, x); }
    T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
tpl_<tn_ T> struct BIT     { int n; v<T> t, nums; T z; function<T(T, T)> c;   // All 0-indexed
    BIT() : n(0), z(0), c([](T a, T b) { return a + b; }) {}
    BIT(int sz, T zero, function<T(T, T)> combine, const v<T>& init = {}) : n(sz), t(sz + 1, zero), nums(sz, zero), z(zero), c(std::move(combine)) { if (!init.empty()) { nums = init; f(i, n) add(i, nums[i]); } }
    void add(int i, T x) { nums[i] += x; for (i += 1; i <= n; i += (i & -i)) t[i] = c(t[i], x); }
    void update(int i, T x) { T diff = x-nums[i]; nums[i] = x; for (i += 1; i <= n; i += (i & -i)) t[i] = c(t[i], diff); }
    T query(int i) { T res = z; for (i += 1; i > 0; i -= (i & -i)) res = c(res, t[i]); return res; }
    T query(int l, int r) { return query(r) - query(l-1); }
};
auto ad = [](int a, int b) {return a+b;}; auto sub = [](int a, int b) {return a-b;}; auto sortinv = [](const pii& a,const pii& b) {if(a.ff == b.ff) return a.ss > b.ss; return a.ff < b.ff;};
typedef function<void(int, int)> autotree;
tpl_<tn_ T> ostream& operator<<(ostream& os, const Segtree<T>& seg) { int maxRows=20, rowCount=0, maxDepth=4; function<void(int,int,int,int)> pt=[&](int i,int a,int b,int d){ if(a>b||rowCount>=maxRows||d>maxDepth)return; os<<string(d*2,' ')<<"["<<a<<","<<b<<"]: "<<seg.t[i]<<"\n"; rowCount++; if(a!=b){ int m=(a+b)/2; pt(2*i,a,m,d+1); pt(2*i+1,m+1,b,d+1); } }; os<<"Segtree:\n"; pt(1,0,seg.n-1,0); return os; }
tpl_<tn_ T> ostream& operator<<(ostream& os, const BIT<T>& bit) { os << "BIT:\n"; int levels = 0; while ((1 << levels) <= bit.n) levels++; v<vs> grid(levels, vs(bit.n, string(4, ' ')));
    for(int i = 1; i <= bit.n; ++i) {int row = __builtin_ctz(i);if(row < levels) {ostringstream oss;oss << setw(4) << bit.t[i];grid[row][i - 1] = oss.str();}} for(int r = 0; r < levels; ++r) {for(int c = 0; c < bit.n; ++c) {os << grid[r][c];}os << "\n";}return os;}
template<class T, class U> T fstTrue(T l, T r, U ff) { while (l<r) { T m = (l + r)/2; ff(m) ? r=m : l = m+1; } return ff(l) ? l : r+1; }
template<class T, class U> T lstTrue(T l, T r, U ff) { while (l<r) { T m = (l+r+1)/2; ff(m) ? l=m : r = m-1; } return ff(l) ? l : r+1; }
template<class T> bool       ckmn(T& a, const T& b) {return b < a ? a = b, 1 : 0;}  template<class T> bool ckmx(T& a, const T& b) {return a < b ? a = b, 1 : 0;}
    int N = 10000; int MOD=1e9+7; constexpr int INF=1e9; constexpr int INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";
int ceil(int num, int den) { return (num + den - 1) / den; } int fastPow(int a, int b, int mod = MOD) { int res = 1; a %= mod; while (b > 0) { if (b & 1) res = res * a % mod; a = a * a % mod; b >>= 1; } return res; }
vb sieve(const int n){vb p(n+1,true);p[0]=p[1]=false;for(int i=2;i*i<=n;++i)if(p[i])for(int j=i*i;j<=n;j+=i)p[j]=false;return p;} vi sieveList(int n){vb p=sieve(n);vi primes;for(int i=2;i<=n;++i)if(p[i])primes.pb(i);return primes;}
inline int mult(int a, int b, int m = MOD) {return (a % m * b % m) % m;} inline int add(int a, int b, int m = MOD) {return (a % m + b % m) % m;}
struct mint { int val; // Avg 2x slowdown over raw % operations
    mint(int v=0) : val((v%MOD+MOD)%MOD) {} // NOLINT(google-explicit-constructor) (We want mint = 5 to be treated like int)
    mint operator+(const mint& o) const { return mint(val + o.val >= MOD ? val + o.val - MOD : val + o.val); } mint operator-(const mint& o) const { return mint(val - o.val < 0 ? val - o.val + MOD : val - o.val); }
    mint operator*() const { return mint(val); } mint operator*(const mint& o) const { return mint(val * o.val % MOD); } mint operator/(const mint& o) const { return *this * fastPow(o.val, MOD-2); }
    friend ostream& operator<<(ostream& os, const mint& m) { return os << m.val; } bool operator<(const mint& o) const { return val < o.val; } bool operator<=(const mint& o) const { return val <= o.val; }
    mint& operator+=(const mint& o) { val = (val + o.val >= MOD ? val + o.val - MOD : val + o.val); return *this; } mint& operator-=(const mint& o) { val = (val - o.val < 0 ? val - o.val + MOD : val - o.val); return *this; }
};

int t, k, n, m;
void solve() {
    
}

// Intuition is correct that one needs to iterate over all combinations of size contributions from children
// But to do it efficiently, only track up to k, update by each edge [1->k] at a time
// Practically, use vv<set> with uid edges for efficient add/remove operations
int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>k;
    vvi adj(n), id(n, vi(n, 0)); // Map edges to 1-based index
    f(i, n) {
        int u, v; cin>>u>>v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
        id[u][v] = id[v][u] = i+1;
    }
    // [node, sz] -> nodes (and validity check)
    vvb good(n, vb(n, false));
    vector<vector<set<int>>> dp(n, v<set<int>>(n));
    f(i, n) good[n][0] = good[n][1] = true; // Sizes of 0, 1 everywhere

    autotree dfs = [&](int u, int p) {
        if(u != 0) dp[u][1].insert(p);
        for(int v : adj[u]) {
            if(v==p) continue;
            dfs(v, u);
            repr(sz, k, 1) {
                if(good[n][sz]) dp[n][sz].insert(id[n][u]); // Obviously can't connect own vertex

                // Try to build it using j from current child e
                for(int j = 1; j < sz; ++j) {
                    if(!good[])
                }
            }
        }
    }



    // vi sz(n, 1);
    // autotree findsz = [&](int u, int p) {
    //     for(int v : adj[u]) {
    //         if(v==p) continue;
    //         findsz(v, u);
    //         sz[u] += sz[v];
    //     }
    // };
    // findsz(0, 0);

    // {u, size with u} -> min edges removed
    // vvi dp(n, vi(k, INF));
    // f(i, n) if(adj[i].size()==1) dp[i][0] = 0; // Base case is leaf edges
    // autotree dfs = [&](int u, int p) {
    //     // Removing 0-k immediate edges, keeping all subtrees
    //     dp[u][sz[u]] = 0;
    //     int csz = 0, cdp = 0;
    //     f(i, adj[u].size()) {
    //         int v = adj[u][i];
    //         csz += sz[v], cdp += dp[v][0];
    //         if(sz[u] - csz <= k) ckmn(dp[u][sz[u] - csz], dp[v][])
    //     }
    //     for(int v : adj[u]) {
    //         if(v==p) continue;
    //         dfs(v, u);
    //
    //         // Iterate over paris of children (would only be for trees)
    //         int m = adj[u].size();
    //         f(i, m) {
    //             f(j, i) {
    //                 int v1 = adj[u][i], v2 = adj[u][j];
    //                 f(a, k) {
    //                     f(b, k-a-1) {
    //                         if(dp[v1][a] != -1 && dp[v2][b] != -1) ckmn(dp[u][a+b+1], dp[v1][a] + dp[v2][b]);
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // };
    // dfs(0, 0);
    int res = INF;
    f(i, n) ckmn(res, dp[i][k]);
    if(res==INF) cout<<0<<en;
    else cout<<res<<en;
}
