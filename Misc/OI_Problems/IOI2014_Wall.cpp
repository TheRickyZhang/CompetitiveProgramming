#include <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define cx_ constexpr
#define fn function
#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define repr(i, a, b) for (int i = (a); i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define fora(a, x) for (auto &a : x)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define quit(s) do{ cout<<(s)<<en; return; }while(false)

#define int long long
tpl_<tn_ T>       using v = vector<T>; using ll=long long; using pii=pair<int,int>; using pll=pair<ll,ll>; using iii=array<int, 3>;  using i4=array<int, 4>;
tpl_<tn_ T>       using vv = v<v<T>>;  using vi=v<int>;    using vb=v<bool>; using vvb=v<vb>; using vs=v<string>;  using vvi=v<vi>; using vll=v<ll>; using vpii=v<pii>; using vvpii=v<vpii>;
tpl_<tn_ K,tn_ T> using ump=unordered_map<K, T>;  tpl_<tn_ T>using ust=unordered_set<T>; tpl_<tn_ T> using rset=set<T,greater<T>>; tpl_<tn_ T> using mset=multiset<T>;
tpl_<tn_ T>       using pq=priority_queue<T>;     tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;
tpl_<class It, class T>     auto leq_bound  (It first, It last, T val) { auto it = upper_bound(first, last, val); return it != first ? prev(it) : last;}
tpl_<class It, class T>     auto less_bound (It first, It last, T val) {auto it = lower_bound(first, last, val);return it != first ? prev(it) : last; }
using str = string; typedef fn<void(int, int, int)> fviii;  typedef fn<void(int, int)> fvii; typedef fn<void(int)> fvi;
auto ad = [](int a, int b) {return a+b;}; auto sub = [](int a, int b) {return a-b;}; auto sortinv = [](const pii& a,const pii& b) {if(a.ff == b.ff) return a.ss > b.ss; return a.ff < b.ff;};

void setIO(const str &name = "") {ios_base::sync_with_stdio(false); cin.tie(nullptr); if (!name.empty()) { freopen((name + ".in").c_str(), "r", stdin); freopen((name + ".out").c_str(), "w", stdout); }}
tpl_<tn_ A, tn_ B> ostream& operator<<(ostream& os, const pair<A, B>& p){ return os<<"("<<p.ff<<", "<<p.ss<<")";}
tpl_<tn_ A> ostream&        operator<<(ostream& os, const v<v<A>>& v)   { for (const auto& row : v) { os << "{ "; for (const auto& elem : row) {os<<elem<<" ";}os<<"}"; os<<"\n";} return os;}
tpl_<tn_ K, tn_ T> ostream& operator<<(ostream& os, const map<K, T>& m) { os << "{"; str sep; for (const auto& kv : m) os << sep << kv.ff << ": " << kv.ss, sep = ", "; return os << "}"; }
tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, str>, typename C::value_type>> ostream& operator<<(ostream& os, const C& v) { os<<"{"; str sep; for(const T& x : v) os<<sep<<x, sep=", "; return os<<"}";}
struct cind{template<typename T> cind& operator>>(T &x){cin>>x;--x;return *this;}} cind;
struct bout{tpl_<tn_ T> bout& operator<<(T x){if cx_(is_integral_v<T>){int y=x;if(y==0){cout<<'0';return *this;}if(y<0){cout<<'-';y=-y;}str s;while(y){s.pb('0'+(y&1));y>>=1;}reverse(all(s));cout<<s;}else cout<<x;return *this;}} bout;
void read(vi &v){for(auto &x:v)cin>>x;} void read(vpii &v){for(auto &p:v)cin>>p.first>>p.second;} void read(vvi &mat){for(auto &r:mat)for(auto &x:r)cin>>x;}
void read(vvi &g, int m, bool dec=true, bool dir=false){f(i, m){int u,v;cin>>u>>v;if(dec){u--;v--;}g[u].pb(v);if(!dir)g[v].pb(u);}}
void read(vvpii &g, int m, bool dec=true, bool dir=false){f(i, m){int u,v,w;cin>>u>>v>>w;if(dec){u--;v--;}g[u].pb({v,w});if(!dir)g[v].pb({u,w});}}

struct DSU{ vi p,sz; explicit
         DSU(const int n){p.resize(n),sz.resize(n,1),iota(all(p),0);}
    int  par(int x){return x==p[x]?x:p[x]=par(p[x]);}
    void merge(int x,int y){x=par(x),y=par(y);if(x!=y){if(sz[x]<sz[y])swap(x,y);p[y]=x,sz[x]+=sz[y];}}
    bool same(int x, int y){ return par(x) == par(y); }
};
tpl_<tn_ T> struct Segtree      { int n; v<T> t, nums; fn<T(T, T)> c;
    Segtree() : n(0), c([](T a, T b) { return a + b; }) {}
    Segtree(int sz, T zero, fn<T(T, T)> combine, const v<T>& init = {}) : n(sz), t(4 * sz, zero), nums(sz, zero), c(move(combine)) { if (!init.empty()) { nums = init; build(1, 0, n-1); } }
    void build (int i, int a, int b) { if (a == b) { t[i] = nums[a]; return; } int m = (a + b) / 2; build(2 * i, a, m); build(2 * i + 1, m + 1, b); t[i] = c(t[2 * i], t[2 * i + 1]); }
    void add   (int i, int a, int b, int p, T x) { if (a == b) { t[i] = c(t[i], x); return; } int m = (a + b) / 2; (p <= m ? add(2 * i, a, m, p, x) : add(2 * i + 1, m + 1, b, p, x)); t[i] = c(t[2 * i], t[2 * i + 1]); }
    void update(int i, int a, int b, int p, T x) { if (a == b) { t[i] = x; return; } int m = (a + b) / 2; (p <= m ? update(2 * i, a, m, p, x) : update(2 * i + 1, m + 1, b, p, x)); t[i] = c(t[2 * i], t[2 * i + 1]); }
    T query  (int i, int a, int b, int l, int r) { if (r < a || b < l) return T(); if (l <= a && b <= r) return t[i]; int m = (a + b) / 2; return c(query(2 * i, a, m, l, r), query(2 * i + 1, m + 1, b, l, r)); }
    friend ostream& operator<<(ostream& os, const Segtree<T>& seg) {
    int maxRows=20, rowCount=0, maxDepth=4; fn<void(int,int,int,int)> pt; pt=[maxRows, maxDepth, &rowCount, &os, &seg, &pt](int i,int a,int b,int d){ if(a>b||rowCount>=maxRows||d>maxDepth)return;
        os<<str(d*2,' ')<<"["<<a<<","<<b<<"]: "<<seg.t[i]<<"\n"; rowCount++; if(a!=b){ int m=(a+b)/2; pt(2*i,a,m,d+1); pt(2*i+1,m+1,b,d+1); } }; os<<"Segtree:\n"; pt(1,0,seg.n-1,0); return os;}
    void add(int p, T x) { add(1, 0, n-1, p, x); }
    void update(int p, T x) { update(1,0,n-1,p,x); }
    T query(int l, int r) { return query(1, 0, n-1, l, r); }
};
tpl_<tn_ T, tn_ U>
struct LazySegtree {            // NOTE this "apply" passes in [l, r] by default! ap and cmp use {old, new op ... }
    int n; v<T> t, nums; v<U> ops; fn<T(T,T)> c; fn<T(T, U, int,int)> ap; fn<U(U,U)> cmp;
    LazySegtree(int sz, fn<T(T,T)> cmb, fn<T(T, U, int, int)> _ap, fn<U(U,U)> _cmp, const v<T>& init={}) :
    n(sz), t(4*sz), nums(sz), ops(4*sz), c(move(cmb)), ap(move(_ap)), cmp(move(_cmp)) { if(!init.empty()){ nums=init; build(1,0,n-1); } }
    void build(int i,int a,int b){
        if(a==b){ t[i]=nums[a]; return; } int m=(a+b)/2; build(2*i,a,m); build(2*i+1,m+1,b); t[i]=c(t[2*i],t[2*i+1]); }
    void applyNode(int i, const U& u,int a,int b){   t[i]=ap(t[i], u, a,b); ops[i]=cmp(ops[i], u); }
    void push(int i,int a,int b){
        int m=(a+b)/2; applyNode(2*i, ops[i], a,m); applyNode(2*i+1, ops[i], m+1, b); ops[i]=U(); }
    void add(int i,int a,int b,int l,int r,const U& u){
        if(r<a||b<l) return; if(l<=a && b<=r){ applyNode(i,u,a,b); return; } push(i,a,b); int m=(a+b)/2;
        add(2*i,   a,   m, l, r, u); add(2*i+1, m+1, b, l, r, u); t[i]=c(t[2*i],t[2*i+1]); }
    T query(int i,int a,int b,int l,int r){
        if(r<a||b<l) return T(); if(l<=a&&b<=r) return t[i]; push(i,a,b); int m=(a+b)/2;
        T L=query(2*i, a,m, l, r), R=query(2*i+1, m+1, b, l, r); return c(L,R); }
    void add(int l,int r,U u){ add(1,0,n-1,l,r,u); }
    T    query(int l, int r){ return query(1,0,n-1,l,r); }
};
tpl_<tn_ T> struct BIT     { int n; v<T> t, nums; fn<T(T, T)> c;
    BIT() : n(0), c([](T a, T b) { return a+b; }) {}
    BIT(int sz, fn<T(T, T)> combine, const v<T>& init = {}, T zero = T()) : n(sz), t(sz+1, zero), nums(sz, zero), c(std::move(combine)) { if (!init.empty()) { f(i, n) add(i, init[i]); } }
    friend ostream& operator<<(ostream& os, const BIT<T>& bit) {
        os<<"BIT:\n"; int maxCol = 16, lvls = 0; while ((1<<lvls) <= min(bit.n, maxCol)) lvls++; int cols = min(bit.n, maxCol); v<vs> grid(lvls, vs(cols, string(4, ' ')));
        fe(i, cols) { int row = __builtin_ctz(i); if (row<lvls) {ostringstream oss; oss<<setw(4)<<bit.t[i]; grid[row][i-1] = oss.str(); } } f(r, lvls) { f(c, cols) os<<grid[r][c]; os<<"\n"; } return os;}
    void add(int i, T x) { nums[i] += x; for (i += 1; i <= n; i += (i & -i)) t[i] = c(t[i], x); }
    void update(int i, T x) { T diff = x-nums[i]; nums[i] = x; for (i += 1; i <= n; i += (i & -i)) t[i] = c(t[i], diff); }
    T query(int i) { T res = T(); for (i += 1; i > 0; i -= (i & -i)) res = c(res, t[i]); return res; }
    T query(int l, int r) { return query(r)-query(l-1); }
};
    cx_ int N = 100000; cx_ int MOD=1e9+7; cx_ int INF=1e9; cx_ ll INFL=0x3f3f3f3f3f3f3f3f; cx_ auto en = "\n"; cx_ auto sp = " ";
tpl_<class T> bool       ckmn(T& a, const T& b) {return b < a ? a = b, 1 : 0;}  tpl_<class T> bool ckmx(T& a, const T& b) {return a < b ? a = b, 1 : 0;}


int t, k, n, m;


struct op {
    int mx = INFL;
    int mn = -INFL;
};

void buildWall(int n, int k, int ops[], int left[], int right[], int height[], int finalHeight[]) {
    LazySegtree<int, op> tree(n,
        ad, // Since only point queries this doesn't mater
        [&](int x, op o, int l, int r) {
            ckmn(x, o.mx);
            ckmx(x, o.mn);
            return x;
        },
        [&](op o, op p) {
            ckmx(o.mn, p.mn);
            ckmn(o.mx, p.mx);
            if(o.mx < o.mn){
              if(p.mx < o.mn) return op{p.mx,p.mx};
              else             return op{p.mn,p.mn};
            }
            return o;
        });
    f(i, k) {
        int t = ops[i], l = left[i], r = right[i], x = height[i];
        if(t == 1) {
            tree.add(l, r, op{-INFL, x});
        } else {
            tree.add(l, r, op{x, INFL});
        }
    }
    f(i, n) finalHeight[i] = tree.query(i, i);
}
//
// #include "wall.h"
// #include <bits/stdc++.h>
// using namespace std;
//
// typedef long long ll;
// #define FOR(i,N) for(ll i = 0; i < N; i++)
// #define all(x) (x).begin(), (x).end()
// #define F first
// #define S second
//
// const int INF = 1e8;
//
// int N;
// vector<pair<int,int>> tree;
//
// pair<int,int> merge(pair<int,int> &a, pair<int,int> b) {
//     if (b.F > a.S) return a = {b.F, b.F};
//     if (b.S < a.F) return a = {b.S, b.S};
//     return a = {max(a.F, b.F), min(a.S, b.S)};
// }
//
// void pushdown(int tl, int tr, int i) {
//     if (tl != tr) {
//         merge(tree[i*2], tree[i]);
//         merge(tree[i*2+1], tree[i]);
//         tree[i] = {0, INF};
//     }
// }
//
// void update(pair<int,int> v, int l, int r, int tl = 0, int tr = N-1, int i = 1) {
//     pushdown(tl, tr, i);
//     if (l > r) return;
//     if (tl == l && tr == r) {
//         merge(tree[i], v);
//         pushdown(tl, tr, i);
//         return;
//     }
//     int tm = (tl + tr) / 2;
//     update(v, l, min(r, tm), tl, tm, i * 2);
//     update(v, max(l, tm + 1), r, tm + 1, tr, i * 2 + 1);
// }
//
// int query(int p, int tl = 0, int tr = N-1, int i = 1) {
//     pushdown(tl, tr, i);
//     if (tl == tr) return tree[i].F;
//     int tm = (tl + tr) / 2;
//     if (p <= tm) return query(p, tl, tm, i * 2);
//     else return query(p, tm + 1, tr, i * 2 + 1);
// }
//
//
// void buildWall(int N, int K, int op[], int left[], int right[], int height[], int finalHeight[]) {
//     ::N = N;
//     tree.resize(4*N, {0, INF});
//     for(int i = 0; i < K; i++) {
//         if (op[i] == 1) update({height[i], INF}, left[i], right[i]);
//         if (op[i] == 2) update({0, height[i]}, left[i], right[i]);
//
//     }
//     for(int i = 0; i < N; i++) {
//         finalHeight[i] = query(i);
//     }
// }