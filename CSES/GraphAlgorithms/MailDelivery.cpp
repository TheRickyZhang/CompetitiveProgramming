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

#define int long long
tpl_<tn_ T>       using v = vector<T>; using ll=long long; using pii=pair<int,int>; using pll=pair<ll,ll>; using iii=array<int, 3>;  using i4=array<int, 4>;
tpl_<tn_ T>       using vv = v<v<T>>;  using vi=v<int>;    using vb=v<bool>; using vvb=v<vb>; using vs=v<string>;  using vvi=v<vi>; using vll=v<ll>;using vvll=v<vll>; using vpii=v<pii>; using vvpii=v<vpii>;
tpl_<tn_ K,tn_ T> using ump=unordered_map<K, T>;  tpl_<tn_ T>using ust=unordered_set<T>;  tpl_<tn_ K,tn_ T>    using rmap=map<K,T,greater<K>>; tpl_<tn_ T> using rset=set<T,greater<T>>; tpl_<tn_ T> using mset=multiset<T>; tpl_<tn_ T>using rmset=multiset<T,greater<T>>;
tpl_<tn_ T>       using pq=priority_queue<T>;     tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;      using str = string;
tpl_<class It, class T>     auto leq_bound  (It first, It last, T val) { auto it = upper_bound(first, last, val); return it != first ? prev(it) : last;} tpl_<class C, class T>auto leq_bound(C& c, T val) {auto it = c.upper_bound(val);return it != c.begin() ? prev(it) : c.end();}
tpl_<class It, class T>     auto less_bound (It first, It last, T val) {auto it = lower_bound(first, last, val);return it != first ? prev(it) : last; }tpl_<class C, class T>auto less_bound(C& c, T val) {auto it = c.lower_bound(val);return it != c.begin() ? prev(it) : c.end();}

void setIO(const string &name = "") {ios_base::sync_with_stdio(false); cin.tie(nullptr); if (!name.empty()) { freopen((name + ".in").c_str(), "r", stdin); freopen((name + ".out").c_str(), "w", stdout); }}
tpl_<tn_ A, tn_ B> ostream& operator<<(ostream& os, const pair<A, B>& p){ return os<<"("<<p.ff<<", "<<p.ss<<")";}
tpl_<tn_ A> ostream&        operator<<(ostream& os, const v<v<A>>& v)   { for (const auto& row : v) { os << "{ "; for (const auto& elem : row) {os<<elem<<" ";}os<<"}"; os<<"\n";} return os;}
tpl_<tn_ K, tn_ T> ostream& operator<<(ostream& os, const map<K, T>& m) { os << "{"; string sep; for (const auto& kv : m) os << sep << kv.ff << ": " << kv.ss, sep = ", "; return os << "}"; }
tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, string>, typename C::value_type>> ostream& operator<<(ostream& os, const C& v) { os<<"{"; string sep; for(const T& x : v) os<<sep<<x, sep=", "; return os<<"}";}
struct cind{template<typename T> cind& operator>>(T &x){cin>>x;--x;return *this;}} cind;
struct bout{tpl_<tn_ T> bout& operator<<(T x){if constexpr(is_integral_v<T>){int y=x;if(y==0){cout<<'0';return *this;}if(y<0){cout<<'-';y=-y;}string s;while(y){s.pb('0'+(y&1));y>>=1;}reverse(all(s));cout<<s;}else cout<<x;return *this;}} bout;
void read(vi &v){for(auto &x:v)cin>>x;} void read(vpii &v){for(auto &p:v)cin>>p.first>>p.second;} void read(vvi &mat){for(auto &r:mat)for(auto &x:r)cin>>x;}
void read(vvi &g, int m, bool dec=true, bool dir=false){f(i, m){int u,v;cin>>u>>v;if(dec){u--;v--;}g[u].pb(v);if(!dir)g[v].pb(u);}}
void read(vvpii &g, int m, bool dec=true, bool dir=false){f(i, m){int u,v,w;cin>>u>>v>>w;if(dec){u--;v--;}g[u].pb({v,w});if(!dir)g[v].pb({u,w});}}

struct DSU{ vi p,sz; explicit
         DSU(const int n){p.resize(n),sz.resize(n,1),iota(all(p),0);}
    int  par(int x){return x==p[x]?x:p[x]=par(p[x]);}
    void merge(int x,int y){x=par(x),y=par(y);if(x!=y){if(sz[x]<sz[y])swap(x,y);p[y]=x,sz[x]+=sz[y];}}
    bool same(int x, int y){ return par(x) == par(y); }
};
tpl_<tn_ T> struct Segtree { int n; v<T> t, nums; T z; function<T(T, T)> c;
    Segtree() : n(0), z(0), c([](T a, T b) { return a + b; }) {}
    Segtree(int sz, T zero, function<T(T, T)> combine, const v<T>& init = {}) : n(sz), t(4 * sz, zero), nums(sz, zero), z(zero), c(move(combine)) { if (!init.empty()) { nums = init; build(1, 0, n-1); } }
    void build (int i, int a, int b) { if (a == b) { t[i] = nums[a]; return; } int m = (a + b) / 2; build(2 * i, a, m); build(2 * i + 1, m + 1, b); t[i] = c(t[2 * i], t[2 * i + 1]); }
    void add   (int i, int a, int b, int p, T x) { if(a==b) { t[i] = c(t[i], x); return; } int m = (a + b) / 2; (p <= m ? add(2 * i, a, m, p, x) : add(2 * i + 1, m + 1, b, p, x)); t[i] = c(t[2 * i], t[2 * i + 1]); }
    void update(int i, int a, int b, int p, T x) { if(a==b) { t[i] = x;          return; } int m = (a + b) / 2; (p <= m ? update(2 * i, a, m, p, x) : update(2 * i + 1, m + 1, b, p, x)); t[i] = c(t[2 * i], t[2 * i + 1]); }
    T query(int i, int a, int b, int l, int r) { if (l > r) return z; if (a == l && b == r) return t[i]; int m = (a + b) / 2; return c(query(2 * i, a, m, l, min(r, m)), query(2 * i + 1, m + 1, b, max(l, m + 1), r)); }
    friend ostream& operator<<(ostream& os, const Segtree<T>& seg) {
    int maxRows=20, rowCount=0, maxDepth=4; function<void(int,int,int,int)> pt; pt=[maxRows, maxDepth, &rowCount, &os, &seg, &pt](int i,int a,int b,int d){ if(a>b||rowCount>=maxRows||d>maxDepth)return;
        os<<string(d*2,' ')<<"["<<a<<","<<b<<"]: "<<seg.t[i]<<"\n"; rowCount++; if(a!=b){ int m=(a+b)/2; pt(2*i,a,m,d+1); pt(2*i+1,m+1,b,d+1); } }; os<<"Segtree:\n"; pt(1,0,seg.n-1,0); return os;}
    void add(int p, T x) { add(1, 0, n-1, p, x); }
    void update(int p, T x) { update(1,0,n-1,p,x); }
    T query(int l, int r) { return query(1, 0, n-1, l, r); }
};
tpl_<tn_ T> struct BIT     { int n; v<T> t, nums; T z; function<T(T, T)> c;   // All 0-indexed
    BIT() : n(0), z(0), c([](T a, T b) { return a+b; }) {}
    BIT(int sz, T zero, function<T(T, T)> combine, const v<T>& init = {}) : n(sz), t(sz+1, zero), nums(sz, zero), z(zero), c(std::move(combine)) { if (!init.empty()) { nums = init; f(i, n) add(i, nums[i]); } }
    friend ostream& operator<<(ostream& os, const BIT<T>& bit) {
        os<<"BIT:\n"; int maxCol = 16, lvls = 0; while ((1<<lvls) <= min(bit.n, maxCol)) lvls++; int cols = min(bit.n, maxCol); v<vs> grid(lvls, vs(cols, string(4, ' ')));
        fe(i, cols) { int row = __builtin_ctz(i); if (row<lvls) {ostringstream oss; oss<<setw(4)<<bit.t[i]; grid[row][i-1] = oss.str(); } } f(r, lvls) { f(c, cols) os<<grid[r][c]; os<<"\n"; } return os;}
    void add(int i, T x) { nums[i] += x; for (i += 1; i <= n; i += (i & -i)) t[i] = c(t[i], x); }
    void update(int i, T x) { T diff = x-nums[i]; nums[i] = x; for (i += 1; i <= n; i += (i & -i)) t[i] = c(t[i], diff); }
    T query(int i) { T res = z; for (i += 1; i > 0; i -= (i & -i)) res = c(res, t[i]); return res; }
    T query(int l, int r) { return query(r)-query(l-1); }
};

void dijkstra(vi& d, vvpii& adj, int a = 0) { mpq<pii> q; d[a] = 0, q.push({0, a});
    while(!q.empty()) { auto [w, u] = q.top(); q.pop(); if(w != d[u]) continue;
        for(auto [v, dw] : adj[u]) { if(w + dw < d[v]) { d[v] = w+dw; q.push({d[v], v});} } } }
tpl_<tn_ Graph> tuple<vi,vi,vi> getAdj(Graph &adj,int a=0){int n=adj.size();vi par(n),dep(n),sz(n,0);
    function<void(int,int,int)>dfs=[&](int u,int p,int d){par[u]=p,dep[u]=d,sz[u]=1;
        for(auto &x:adj[u]){ int v=[&](){if constexpr(std::is_same_v<std::decay_t<decltype(x)>,int>)return x;else return x.ff;}();
            if(v!=p){dfs(v,u,d+1);sz[u]+=sz[v];}}};dfs(a,-1,0);return {dep,par,sz};}
vvi binaryJump(const vi& par) {
    int n = par.size(); int ln = log2(n)+1; vvi up(n, vi(ln, 0)); f(i, n) up[i][0] = par[i];
    rep(j, 1, ln-1) { f(i, n) { int p = up[i][j-1]; if(p==-1) up[i][j] = -1; else up[i][j] = up[p][j-1]; } } return up;}
tpl_<tn_ F> pair<vvi,vvi> binaryJumpW(const vi &par,const vi &wt,F merge){int n=par.size(),ln=log2(n)+1; vvi up(n,vi(ln,0)), cost(n,vi(ln,0));
    f(i,n){up[i][0]=par[i]; cost[i][0]=(par[i]==-1?0:wt[i]);} rep(j,1,ln-1){f(i,n){int p=up[i][j-1]; if(p==-1){up[i][j]=-1; cost[i][j]=cost[i][j-1];} else{up[i][j]=up[p][j-1]; cost[i][j]=merge(cost[i][j-1],cost[p][j-1]);}}} return {up,cost};}
int getLCA(const vvi& up,const vi& dep, int u, int v) {
    int ln = log2(up.size()) + 1; if(dep[u] < dep[v]) swap(u, v); int diff = dep[u]-dep[v]; rep(j, 0, ln-1) { if(diff & (1<<j)) u = up[u][j]; }
    if(u==v) return u; repr(j, ln-1, 0) { if(up[u][j] != up[v][j]) { u = up[u][j], v = up[v][j]; }} return up[u][0];}
tpl_<class T, class U> T fstTrue(T l, T r, U ff) { for(++r; l < r;) { T m = l+(r-l) / 2; if(ff(m)) r = m; else l = m+1; } return l; }
tpl_<class T, class U> T lstTrue(T l, T r, U ff) { for(++r; l < r;) { T m = l+(r-l) / 2; if(ff(m)) l = m+1; else r = m; } return l-1; }
tpl_<class T> bool       ckmn(T& a, const T& b) {return b < a ? a = b, 1 : 0;}  tpl_<class T> bool ckmx(T& a, const T& b) {return a < b ? a = b, 1 : 0;}

struct pairHash{tpl_<class T1,class T2>size_t operator()(const pair<T1,T2>&p)const{return hash<T1>{}(p.first)^ (hash<T2>{}(p.second)<<1);}}; struct vectorHash{tpl_<class T>size_t operator()(const v<T>&v)const{size_t hashTalue=0;for(const T&i:v)hashTalue^=hash<T>{}(i)+0x9e3779b9+(hashTalue<<6)+(hashTalue>>2);return hashTalue;}};
typedef function<void(int, int)> autotree; auto ad = [](int a, int b) {return a+b;}; auto sub = [](int a, int b) {return a-b;}; auto sortinv = [](const pii& a,const pii& b) {if(a.ff == b.ff) return a.ss > b.ss; return a.ff < b.ff;};
vpii dirs={{1,0},{0,-1},{0,1},{-1,0}}; map<char, int> dirMap={{'E',0},{'S',1},{'N',2},{'W',3}}; auto check=[](auto y,auto x,auto m,auto n){return y>=0&&y<m&&x>=0&&x<n;};

    int N = 100000; int MOD=1e9+7; constexpr int INF=1e9; constexpr ll INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";
int ceil(int num, int den) { return num >= 0 ? (num + den - 1) / den : num / den; } int fastPow(int a, int b, int mod = MOD) { int res = 1; a %= mod; while (b > 0) { if (b & 1) res = res * a % mod; a = a * a % mod; b >>= 1; } return res; } int fastLog(int a, int b) {int res = 0; int p = 1; while (p <= b / a) { p *= a; res++;} return res; }
inline int add(int a, int b, int m = MOD) { return (a+b < m ? a+b : a+b-m); } inline int mult(int a, int b, int m = MOD) { return (a*b < m ? a*b : a*b % m); }
vb sieve(const int n){vb p(n+1,true);p[0]=p[1]=false;for(int i=2;i*i<=n;++i)if(p[i])for(int j=i*i;j<=n;j+=i)p[j]=false;return p;} vi sieveList(int n){vb p=sieve(n);vi primes;for(int i=2;i<=n;++i)if(p[i])primes.pb(i);return primes;}
vi sieveSPF(int n) {vi spf(n+1); fe(i, n) spf[i] = i; for(int i = 2; i*i<=n; ++i) { if(spf[i] != i) continue;for(int j = i*i; j <= n; j += i) {if(spf[j]==j) spf[j]=i;}}return spf;}
pair<vi, vi> initFact(int n) { vi fa(n+1), ifa(n+1); fa[0] = 1; fe(i, n) fa[i] = mult(fa[i-1], i); ifa[n] = fastPow(fa[n], MOD-2, MOD); repr(i, n-1, 0) ifa[i] = mult(ifa[i+1], i+1); return {fa, ifa}; }
class Matrix {public: vvi v; explicit Matrix(int n): v(n, vi(n, 0)){}
    Matrix operator*(const Matrix &m) const {int n=v.size(); Matrix r(n); f(i,n) f(k,n) f(j,n) r.v[i][j]=(r.v[i][j]+v[i][k]*m.v[k][j])%MOD; return r;}
    Matrix operator^(int64_t p) const {int n=v.size(); Matrix r(n), b=*this; f(i,n) r.v[i][i]=1; while(p){if(p&1)r=r*b; b=b*b; p>>=1;} return r;}};


int t, k, n, m;
void solve() {
    
}

// Eulerian cycle - Hierholzer's algorithm
// Remember that an A-B relation is typically not a node (Do NOT say there is edge between A-B, B-C),
// but instead an edge between nodes A, B
int32_t main() {
    setIO();
    cin>>n>>m;
    vvpii adj(n); // Also store the index here
    vi deg(n, 0); vb vis(m, false);
    f(i, m) {
        int u, v; cind>>u>>v;
        adj[u].pb({v, i});
        adj[v].pb({u, i});
        deg[u]++, deg[v]++;
    }
    f(u, n) {
        if(deg[u] % 2 != 0) {
            cout<<"IMPOSSIBLE"<<en; return 0;
        }
    }
    vi path;
    // All this does is follow edges until getting back to root, adding cycles
    function<void(int)> dfs = [&](int u) {
        while(!adj[u].empty()) {
            auto [v, i] = adj[u].back(); // Back for convenience
            adj[u].pop_back();
            if(vis[i]) continue; vis[i] = true; // ENSURE you mark the EDGES as seen, not vertices
            dfs(v);
            // edgeOrder.pb(i)
            // This is where you would push edges if you wanted that order
        }
        path.pb(u);
    };
    dfs(0);
    if(path.size() == m+1) {
        for(int u : path) cout<<u+1<<sp;
    } else {
        cout<<"IMPOSSIBLE"<<en;
        // cout<<path<<en;
    }

    // IF YOU WANT TO TRACK ORDER OF EDGES:
    a
}
