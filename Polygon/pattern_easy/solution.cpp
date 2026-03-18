#include <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define op_ operator
#define cx_ constexpr
#define fn function
#define F_GET(_1, _2, _3, NAME, ...) NAME
#define f(...) F_GET(__VA_ARGS__, f3, f2)(__VA_ARGS__)
#define f2(i, to) for (int i = 0; i < (to); ++i)
#define f3(i, from, to) for (int i = (from); i < (to); ++i)
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define repr(i, a, b) for (int i = a; i >= b; --i)
#define ff first
#define ss second
#define pb push_back
#define fora(a, x) for (auto &(a) : (x))
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define print(x) (cout<<#x<<"="<<(x)<<endl)
#define quit(s) do{ cout<<(s)<<en; return; }while(false)

#include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
tpl_<tn_ T> using oset = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<>, __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;
tpl_<tn_ K, tn_ V> using omap = __gnu_pbds::tree<K, V, less<>, __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;

// Aliases
#define int long long
using str=string; using ll=long long; using pii=pair<int, int>; using iii=array<int, 3>; using i4=array<int, 4>;
tpl_<tn_ T> struct v : vector<T> {
  using vector<T>::vector; v(const vector<T>& a) : vector<T>(a) {}
  v(vector<T>&& a) : vector<T>(std::move(a)) {}
  friend istream& operator>>(istream& in, v& a) { for(auto& x : a) in>>x; return in; }
  pair<map<T,int>, v<T>> compress() {
    v<T> vals = *this; sort(vals.begin(), vals.end()); vals.erase(unique(vals.begin(), vals.end()), vals.end());
    map<T,int> mp; f(i, vals.size()) mp[vals[i]] = i; for(auto& x : *this) x = mp[x];
    return {mp, vals}; }
};
tpl_<tn_ T> struct vv : v<v<T>> {
  using v<v<T>>::v; vv(const v<v<T>>& a) : v<v<T>>(a) {} vv(v<v<T>>&& a) : v<v<T>>(std::move(a)) {}
  vv(int n, int m, T val=T()) : v<v<T>>(n, v<T>(m, val)) {}
  tpl_<tn_ Self, tn_ P> requires requires { typename tuple_size<P>::type; } && (tuple_size_v<P> == 2)
  auto&& operator[](this Self&& self, const P& p) { auto& [x,y] = p; return forward<Self>(self).v<v<T>>::operator[](x)[y]; }
  using v<v<T>>::operator[];
  void prefix() { int n=this->size(), m=n?(*this)[0].size():0; f(i,n) f(j,m) {
      if(i) (*this)[i][j]+=(*this)[i-1][j]; if(j) (*this)[i][j]+=(*this)[i][j-1];
      if(i&&j) (*this)[i][j]-=(*this)[i-1][j-1]; } }
  void row_prefix() { int n=this->size(), m=n?(*this)[0].size():0; f(i,n) f(j,m-1) (*this)[i][j+1]+=(*this)[i][j]; }
  void col_prefix() { int n=this->size(), m=n?(*this)[0].size():0; f(i,n-1) f(j,m) (*this)[i+1][j]+=(*this)[i][j]; }
  friend istream& operator>>(istream& in, vv& g) { for(auto& row : g) for(auto& x : row) in>>x; return in; }
};
using vi = v<int>; using vb=v<bool>; using vs=v<string>; using vvi = vv<int>; 
tpl_<tn_ K,tn_ T>using ump=unordered_map<K,T>; tpl_<tn_ T>using ust=unordered_set<T>; tpl_<tn_ T>using mset=multiset<T>;
tpl_<tn_ T> using pq=priority_queue<T>; tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;
typedef fn<void(int,int)>fvii; typedef fn<void(int,int,int)>fviii;

// Constants
cx_ ll INF=1e18; cx_ int B=62; cx_ int N=100000; cx_ int MOD=1e9+7; // 998244353;
cx_ auto en="\n"; cx_ auto sp=" ";
auto _max=[](int a, int b) {return max(a, b);}; auto _min=[](int a, int b) {return min(a, b);};
auto _sortinv=[](const pii& a,const pii& b) {if(a.ff==b.ff) return a.ss > b.ss; return a.ff<b.ff;};
cx_ ll msb(ll x) { return x ? 63 - __builtin_clzll(x) : -1; } cx_ ll lsb(ll x) { return x ? __builtin_ctzll(x) : -1; }

// Input/Output
void setIO(const str&name=""){ios_base::sync_with_stdio(false);cin.tie(nullptr); if(!name.empty())
    {freopen((name+".in").c_str(),"r",stdin);freopen((name+".out").c_str(),"w",stdout);}}
tpl_<tn_ A,tn_ B>ostream& op_<<(ostream& os,const pair<A,B>& p){return os<<"("<<p.ff<<", "<<p.ss<<")";}
tpl_<tn_ A>ostream& op_<<(ostream& o,const v<v<A>>& m){for(auto& r:m){o<<"{";for(auto& e:r)o<<e<<" ";o<<"}\n";}return o;}
tpl_<tn_ K,tn_ T>ostream& op_<<(ostream& o,const map<K,T>& m){o<<"{";for(auto& p:m)o<<p.ff<<":"<<p.ss<<", ";return o<<"}";}
template<typename T> concept StringLike = convertible_to<T, string_view>;
template<typename C> concept PrintableRange = !StringLike<C> &&
  requires(const C& c) { begin(c); end(c); } &&
  requires(ostream& os, const C& c) { os << *begin(c); };
tpl_<tn_ C> requires PrintableRange<C>
ostream& op_<<(ostream& os, const C& v) { for(const auto& x : v) os << x << " "; return os; }
struct cind{tpl_<tn_ T> cind& op_>>(T &x){cin>>x;--x;return *this;}} cind;
struct bout{tpl_<tn_ T> bout& op_<<(T x){if cx_(is_integral_v<T>){int y=x;if(y==0){cout<<'0';return *this;} if(y<0)
    {cout<<'-';y=-y;}str s;while(y){s.pb('0'+(y&1));y>>=1;}reverse(all(s));cout<<s;}else cout<<x;return *this;}} bout;

// Modular arithmetic
tpl_<tn_... T> requires(integral<T> && ...)
inline int add(T... x) { int res = 0; ((res += x, res -= (res >= MOD ? MOD : 0)), ...); return res; }
tpl_<tn_ T, tn_... U> requires(integral<T> && (integral<U> && ...))
inline int sub(T x, U... y) { int res = x; ((res -= y, res += (res < 0 ? MOD : 0)), ...); return res; }
tpl_<tn_... T> inline int mult(T... x) { int res = 1; ((res = (res * x) % MOD), ...); return res; }
inline int ceil(int a, int b) { return a >= 0 ? (a + b - 1) / b : a / b; }
inline int fpow(int a, int b){int res=1; a%=MOD; while(b>0){if(b&1) res=res*a % MOD; a=mult(a,a); b>>=1;} return res; }
inline int inv(int x) { return fpow(x, MOD-2); }
struct mint { ll v; mint(ll x=0): v((x % MOD+MOD) % MOD) {}
    mint op_+(mint o) const{ return mint(add(v, o.v)); } mint op_-(mint o) const{ return mint(sub(v, o.v)); }
    mint op_*(mint o) const{ return mint(mult(v, o.v)); } mint op_/(mint o) const{ return mint(mult(v, inv(o.v))); }
    mint& op_+=(mint o)    { return *this=*this+o; } mint& op_-=(mint o)    { return *this=*this-o; }
    mint& op_*=(mint o)    { return *this=*this*o; } mint& op_/=(mint o)    { return *this=*this/o; }
    friend ostream& op_<<(ostream& os, const mint& x) { return os<<x.v; } };

// Math
vb sieve(int n){vb p(n+1,true);p[0]=p[1]=false;for(int i=2;i*i<=n;++i)if(p[i])for(int j=i*i;j<=n;j+=i)p[j]=false;return p;}
vi sieveList(int n){vb p=sieve(n);vi primes; rep(i, 2, n) if(p[i]) primes.pb(i); return primes;}
vi sieveSPF(int n) {vi spf(n+1); rep(i, 1, n) spf[i]=i; for(int i=2; i*i<=n; ++i) { if(spf[i] != i) continue;
    for(int j=i*i; j <= n; j += i) {if(spf[j]==j) spf[j]=i;}}return spf;}
pair<vi, vi> initFact(int n) { vi fa(n+1), ifa(n+1); fa[0]=1; rep(i, 1, n) fa[i]=mult(fa[i-1], i); ifa[n]=inv(fa[n]);
    repr(i, n-1, 0) ifa[i]=mult(ifa[i+1], i+1); return {fa, ifa}; }
class Matrix {public: vvi v; explicit Matrix(int n): v(n, vi(n, 0)){}
    Matrix op_*(const Matrix &m) const {int n=v.size(); Matrix r(n);
        f(i,n) f(k,n) f(j,n) r.v[i][j]=(r.v[i][j]+v[i][k]*m.v[k][j])%MOD; return r;}
    Matrix op_^(ll p) const {int n=v.size(); Matrix r(n), b=*this; f(i,n) r.v[i][i]=1;
        while(p){if(p&1)r=r*b; b=b*b; p>>=1;} return r;}};
struct Hash { tpl_<tn_ T> size_t operator()(const T& x) const {
  if cx_(requires { typename tuple_size<T>::type; }) {
    size_t h = 0; apply([&](const auto&... args) { ((h ^= Hash{}(args) + 0x9e3779b9 + (h<<6)+(h>>2)), ...);}, x); return h;
  } else if cx_(requires { begin(x); }) {
    size_t h = 0; for(auto& i : x) h ^= Hash{}(i) + 0x9e3779b9 + (h<<6) + (h>>2); return h;
  } else { return hash<T>{}(x); } } };

// Simple helpers
tpl_<tn_ It, tn_ T> auto leq_bound(It l,It r,T x){auto it=upper_bound(l,r,x); return it!=l ? prev(it):r;}
tpl_<tn_ It, tn_ T> auto less_bound(It l,It r,T x){auto it=lower_bound(l,r,x);return it!=l ? prev(it):r;}
tpl_<tn_ T, tn_ U> T fstTrue(T l, T r, U ff) { for(++r; l<r;) { T m=l+(r-l)/2; if(ff(m)) r=m; else l=m+1; } return l;}
tpl_<tn_ T, tn_ U> T lstTrue(T l, T r, U ff) { for(++r; l<r;) { T m=l+(r-l)/2; if(ff(m)) l=m+1; else r=m; } return l-1;}
tpl_<tn_ T> bool cmn(T& a, T b) {return b<a ? a=b,1 : 0;} tpl_<tn_ T> bool cmx(T& a, T b) {return a<b ? a=b,1 : 0;}

// Named tuples
struct point { int x, y;
  point operator+(const point& q) const { return {x + q.x, y + q.y}; }
  point operator-(const point& q) const { return {x - q.x, y - q.y}; }
  point operator-() const { return {-x,-y}; }
  point& operator+=(const point& p) { x+=p.x; y+=p.y; return *this; }
  point& operator-=(const point& p) { x-=p.x; y-=p.y; return *this; }
  auto operator<=>(const point&) const = default;
  friend istream& operator>>(istream& in, point& p) { in >> p.x >> p.y; return in; }
  friend ostream& operator<<(ostream& os, const point& p) { os << "{" << p.x << "," << p.y << "}"; return os; }
  bool in(point bounds) const { return x >= 0 && x < bounds.x && y >= 0 && y < bounds.y; }
  bool in(int n, int m) const { return in({n, m}); }
}; using pos = point; using dpoint = point;
inline const array<point, 4> dirs = {{{1,0}, {0,-1}, {0,1}, {-1,0}}};
inline const map<char, int> dirMap = {{'E',0},{'S',1},{'N',2},{'W',3}};
tpl_<> struct tuple_size<point> : integral_constant<size_t, 2> {};
tpl_<size_t I> struct tuple_element<I, point> { using type = int; };
tpl_<size_t I> auto get(const point& p) { if cx_(I==0) return p.x; else return p.y; }
struct ivl { int l, r;
  ivl merge(const ivl& other) const { return ivl{min(l, other.l), max(r, other.r)}; }
  bool contains(int x) const { return(l <= x && x <= r); }
  friend istream& operator>>(istream& in, ivl& ivl) { in >> ivl.l >> ivl.r; return in; }
  friend ostream& operator<<(ostream& os, const ivl& i) { os << i.l << ", " << i.r; return os; }
};
tpl_<> struct tuple_size<ivl> : integral_constant<size_t, 2> {};
struct edge { int u, v;
  friend istream& operator>>(istream& in, edge& e) { in >> e.u >> e.v; return in; }
  friend ostream& operator<<(ostream& os, const edge& e) { os << e.u << ", " << e.v; return os; }
};
struct edgew { int w, u, v;
  bool operator<(const edgew& e) const { return tie(w, u, v) < tie(e.w, e.u, e.v); }
  friend ostream& operator<<(ostream& os, const edgew& e) { os << e.w << ", " << e.u << ", " << e.v; return os; }
};

// Data structures
struct DSU{ vi p,sz; explicit
    DSU(const int n){p.resize(n),sz.resize(n,1),iota(all(p),0);}
    int  par(int x){return x==p[x]?x:p[x]=par(p[x]);}
    void merge(int x,int y){x=par(x),y=par(y);if(x!=y){if(sz[x]<sz[y])swap(x,y);p[y]=x,sz[x]+=sz[y];}}
    bool same(int x, int y){ return par(x)==par(y); }
};

template<typename Adj>
struct GraphBase { int n, m; bool dir; vector<vector<Adj>> adj;
  GraphBase(int n=0, bool dir=false) : n(n), m(0), dir(dir), adj(n) {}
  auto& operator[](int u) { return adj[u]; }
  const auto& operator[](int u) const { return adj[u]; }
};
template<typename W=void> struct Graph; using graph = Graph<>;
template<typename W=void> class Tree;   using tree = Tree<>;
template<>
struct Graph<void> : GraphBase<int> { using Base = GraphBase<int>; using Base::operator[];
  Graph(int n=0, bool dir=false) : Base(n, dir) {}
  void ae(int u, int v) { this->adj[u].pb(v); if(!this->dir) this->adj[v].pb(u); ++this->m; }
  static Graph read(int n, int m, bool dec=true, bool dir=false) {
    Graph g(n, dir); f(i, m) { int u, v; cin >> u >> v; if(dec) --u, --v; g.ae(u, v); } return g; }
  friend ostream& operator<<(ostream& out, const Graph& g) { f(u, g.n) out << u << ": " << g[u] << en; return out; }
  vi bfs(int s) const { vi d(this->n,-1); queue<int> q;
    d[s]=0; q.push(s);
    while(!q.empty()){int u=q.front(); q.pop();
      for(int v:(*this)[u]) if(d[v]==-1){d[v]=d[u]+1; q.push(v);}
    } return d; }
};
template<typename W>
struct Graph : GraphBase<pair<int,W>> { using arc = pair<int,W>; using weight_t = W; using Base = GraphBase<arc>; using Base::operator[];
  Graph(int n=0, bool dir=false) : Base(n, dir) {}
  void ae(int u, int v, W w) { this->adj[u].pb({v, w}); if(!this->dir) this->adj[v].pb({u, w}); ++this->m; }
  vi dijkstra(int s) const { vi d(this->n, INF); priority_queue<pii,v<pii>,greater<pii>> q;
    d[s]=0; q.push({0,s});
    while(!q.empty()){
      auto [du,u]=q.top(); q.pop(); if(du!=d[u]) continue;
      for(auto [v,w]:(*this)[u]) if(d[v]>du+w){d[v]=du+w; q.push({d[v],v});}
    } return d; }
  static Graph read(int n, int m, bool dec=true, bool dir=false) {
    Graph g(n, dir); f(i, m) { int u, v; W w; cin >> u >> v >> w; if(dec) --u, --v; g.ae(u, v, w); } return g; }
  friend ostream& operator<<(ostream& out, const Graph& g) {
    f(u, g.n) { out << u << ": "; for(auto [v, w] : g[u]) out << "{" << v << ", " << w << "} "; out << en; } return out; }
};
template<>
struct Tree<void> : public GraphBase<int> { using Base = GraphBase<int>; using Base::operator[];
  void ae(int u, int v) { this->adj[u].pb(v); this->adj[v].pb(u); ++this->m; }
  Tree(int n=0) : Base(n, false) {}
  static Tree read(int n, bool dec=true) {
    Tree t(n); f(i, n-1) { int u, v; cin >> u >> v; if(dec) --u, --v; t.ae(u, v); } return t; }
  friend ostream& operator<<(ostream& out, const Tree& t) { f(u, t.n) out << u << ": " << t[u] << en; return out; }
};
template<typename W>
struct Tree : public GraphBase<pair<int,W>> { using arc = pair<int,W>; using Base = GraphBase<arc>; using Base::operator[];
  void ae(int u, int v, W w) { this->adj[u].pb({v, w}); this->adj[v].pb({u, w}); ++this->m; }
  using weight_t = W;
  Tree(int n=0) : Base(n, false) {}
  static Tree read(int n, bool dec=true) {
    Tree t(n); f(i, n-1) { int u, v; W w; cin >> u >> v >> w; if(dec) --u, --v; t.ae(u, v, w); } return t; }
  friend ostream& operator<<(ostream& out, const Tree& t) {
    f(u, t.n) { out << u << ": "; for(auto [v, w] : t[u]) out << "{" << v << ", " << w << "} "; out << en; } return out; }
};
tpl_<tn_ W=void>
struct TreeInfo { const Tree<W>& g; int root; vi sz, dep, par, in, out; vvi up;
  TreeInfo(const Tree<W>& g, int root=0) : g(g), root(root) {}
  static int to(const auto& e) { if cx_(requires{e.first;}) return e.first; else return e; }
  void dfs(bool single=true) {
    if(!sz.empty()) return; int n=g.n, t=0;
    sz.assign(n,1); par.assign(n,-1); dep.assign(n,0); in.assign(n,0); out.assign(n,0);
    auto go=[&](auto& self, int u, int p, int d)->void {
      par[u]=p; dep[u]=d; in[u]=t++;
      for(const auto& e:g[u]){int v=to(e); if(v==p) continue; self(self,v,u,d+1); sz[u]+=sz[v];}
      out[u]=single?in[u]+sz[u]:t++;
    }; if(n) go(go,root,-1,0); }
  void jump() { dfs(); if(!up.empty()) return;
    int n=g.n, ln=__lg(n)+1; up.assign(n,vi(ln,-1));
    f(i,n) up[i][0]=par[i]; rep(j,1,ln-1) f(i,n){int p=up[i][j-1]; up[i][j]=(p==-1?-1:up[p][j-1]);} }
  int lca(int u, int v) { jump(); int ln=up[0].size();
    if(dep[u]<dep[v]) swap(u,v); f(j,ln) if((dep[u]-dep[v])&(1LL<<j)) u=up[u][j]; if(u==v) return u;
    repr(j,ln-1,0) if(up[u][j]!=up[v][j]){u=up[u][j]; v=up[v][j];} return up[u][0]; }
  int dist(int u, int v) { return dep[u]+dep[v]-2*dep[lca(u,v)]; }
  bool anc(int u, int v) { dfs(); return in[u]<=in[v]&&out[v]<=out[u]; }
  int kth(int u, int v, int k) {
    jump(); int l=lca(u,v), du=dep[u]-dep[l], dv=dep[v]-dep[l];
    if(k<=du){f(j,up[0].size()) if(k&(1LL<<j)) u=up[u][j]; return u;}
    k=du+dv-k; f(j,up[0].size()) if(k&(1LL<<j)) v=up[v][j]; return v; }
  vi virtualTree(Graph<>& vg, const vi& nodes, bool dir=true) { jump(); vi lu=nodes;
    auto cmp=[&](int a, int b){return in[a]<in[b];}; int n=lu.size(); lu.reserve(2*n);
    sort(all(lu),cmp); f(i,n-1) lu.pb(lca(lu[i],lu[i+1]));
    sort(all(lu),cmp); lu.erase(unique(all(lu)),lu.end()); for(int u:lu) vg[u].clear();
    f(i,lu.size()-1){int u=lca(lu[i],lu[i+1]); int v=lu[i+1]; vg[u].pb(v); if(!dir) vg[v].pb(u);}
    return lu; }
};

tpl_<tn_ T, tn_ C> struct Segtree{
  int n, N; v<T> t, nums; C c; T z;
  static_assert(is_invocable_r_v<T,C,T,T>,"Combine must be T(T,T)");
  Segtree(int sz, C c, const T& z, const v<T>& init={}) : n(sz), N(1), nums(sz, z), c(std::move(c)), z(z) {
      while(N<n) N<<=1; t.assign(2*N, z);
      if(!init.empty()){ nums=init; for(int i=0;i<n;i++) t[N+i]=nums[i]; }
      for(int i=N-1;i;i--) t[i]=c(t[i<<1], t[i<<1|1]); }
  void add(int p, T x){
      int i=p+N; t[i]=c(t[i], x); for(i>>=1;i;i>>=1) t[i]=c(t[i<<1], t[i<<1|1]); }
  void update(int p, T x){
      int i=p+N; t[i]=x; for(i>>=1;i;i>>=1) t[i]=c(t[i<<1], t[i<<1|1]); }
  T query(int l, int r){
      if(r<l) return z; l+=N; r+=N; T L=z, R=z;
      while(l<=r){ if(l&1) L=c(L, t[l++]); if(!(r&1)) R=c(t[r--], R); l>>=1; r>>=1; }
      return c(L, R); }
  friend ostream& operator<<(ostream& os, const Segtree& st) { os << "Segtree\n"; if(st.n == 0) return os;
      vector<array<int,4>> q{{1, 0, st.N - 1, 0}};
      while(!q.empty()) {
          auto [i, l, r, d] = q.back(); q.pop_back(); if(l >= st.n) continue;
          os << str(2*d, ' ') << "[" << l << "," << min<int>(r, st.n - 1) << "]: " << st.t[i] << en;
          if(l == r) continue; int m = (l + r) / 2;
          q.pb({2*i+1, m+1, r, d+1}); q.pb({2*i,   l,   m, d+1}); } return os;
  }
};
tpl_<tn_ T, tn_ U, tn_ C, tn_ Ap, tn_ Cmp>
struct LazySegtree {            // NOTE this "apply" passes in [l, r] by default! ap and cmp use {old, new op ... }
    static_assert(is_invocable_r_v<T,C,T,T>,"Combine T(T,T)");
    static_assert(is_invocable_r_v<T,Ap,T,U,int,int>,"Apply T(T,U,int,int)");
    static_assert(is_invocable_r_v<U,Cmp,U,U>,"Compose U(U,U)");
    int n; v<T> t, nums; v<U> ops; C c; Ap ap; Cmp cmp; T z;
    LazySegtree(int sz, C cmb, Ap ap, Cmp cmp, const T& z, const v<T>& i={})
        : n(sz), z(z), t(4*sz, z), nums(sz, z), ops(4*sz), c(move(cmb)), ap(move(ap)), cmp(move(cmp)) {
        if(!i.empty()) { nums = i; build(1, 0, n-1); }
    }
    void add(int l,int r,U u){ add(1,0,n-1,l,r,u); }
    T query(int l, int r){ return query(1,0,n-1,l,r); }
private:
    void build(int i,int a,int b){
        if(a==b){ t[i]=nums[a]; return; } int m=(a+b)/2; build(2*i,a,m); build(2*i+1,m+1,b); t[i]=c(t[2*i],t[2*i+1]); }
    void applyNode(int i,const U& u,int a,int b){ t[i]=ap(t[i], u, a,b); ops[i]=cmp(ops[i], u); }
    void push(int i,int a,int b){int m=(a+b)/2; applyNode(2*i,ops[i],a,m); applyNode(2*i+1,ops[i],m+1,b); ops[i]=U();}
    void add(int i,int a,int b,int l,int r,const U& u){
        if(r<a||b<l) return; if(l<=a && b<=r){ applyNode(i,u,a,b); return; } push(i,a,b); int m=(a+b)/2;
        add(2*i, a, m, l, r, u); add(2*i+1, m+1, b, l, r, u); t[i]=c(t[2*i],t[2*i+1]); }
    T query(int i,int a,int b,int l,int r){
        if(r<a||b<l) return z; if(l<=a && b<=r) return t[i]; push(i,a,b); int m=(a+b)/2;
        T L=query(2*i, a,m, l, r), R=query(2*i+1, m+1, b, l, r); return c(L,R); }
};

tpl_<tn_ T=int, tn_ C=plus<T>, tn_ Inv=conditional_t<is_arithmetic_v<T>, negate<T>, void>> struct BIT;
tpl_<tn_ T, tn_ C> struct BITBase { int n; v<T> t, nums; [[no_unique_address]] C c; T z;
  static_assert(is_invocable_r_v<T, C, T, T>, "Combine must be T(T,T)");
  BITBase(int sz, C c=C(), T z=T(), const v<T>& init={}) : n(sz), t(sz+1, z), nums(sz, z), c(std::move(c)), z(z) {
    if(!init.empty()) f(i, n) add(i, init[i]);
  }
  void add(int i, T x) { nums[i] = c(nums[i], x); for(++i; i <= n; i += i & -i) t[i] = c(t[i], x); }
  T pref(int i) const { T res = z; for(++i; i > 0; i -= i & -i) res = c(res, t[i]); return res; }
  friend ostream& operator<<(ostream& out, const BITBase& b) {
    out << "BIT:\n"; int c = b.n, lv = __lg(c) + 1;
    v<vs> g(lv, vs(c, str(4, ' ')));
    for(int i = 1; i <= c; i++) { int r = __builtin_ctzll(i); if(r < lv) g[r][i-1] = format("{:4}", b.t[i]); }
    f(r, lv) { f(j, c) out<<g[r][j]; out<<en; } return out; }
};
tpl_<tn_ T, tn_ C>
struct BIT<T, C, void> : BITBase<T, C> { using BITBase<T, C>::BITBase; };
tpl_<tn_ T, tn_ C, tn_ Inv>
struct BIT : BITBase<T, C> {
  [[no_unique_address]] Inv inv; static_assert(is_invocable_r_v<T, Inv, T>, "Inverse must be T(T)");
  BIT(int sz, C c=C(), T z=T(), const v<T>& init={}, Inv inv=Inv())
    : BITBase<T, C>(sz, std::move(c), z, init), inv(std::move(inv)) {}
  using BITBase<T, C>::c; using BITBase<T, C>::nums; using BITBase<T, C>::pref; using BITBase<T, C>::add;
  T query(int l, int r) const { return l ? c(pref(r), inv(pref(l-1))) : pref(r); }
  void update(int i, T x) { add(i, c(x, inv(nums[i]))); nums[i] = x; }
};

struct Line { mutable int a, b, p; // =ax+b, last optimal x
    Line(int a, int b, int p=0) : a(a), b(b), p(p) {}
    int at(int x) const { return a*x + b; }
    bool operator<(const Line& o) const { return a < o.a; } bool operator<(int x) const { return p < x;   }
    friend long double intersect(Line x, Line y) { return static_cast<long double>(y.b-x.b) / static_cast<long double>(x.a-y.a); }
};
// For all CHT, default is upper hull / query max. For query min, negate line a, b, and query result.
struct CHT : multiset<Line, less<>> {
    static constexpr int inf=LLONG_MAX; static int floor(int a, int b) { return a/b - ((a^b)<0 && a%b); }
    bool isect(iterator it1, iterator it2) { if (it2 == end()) { it1->p=inf;return false;}
        if (it1->a == it2->a) it1->p=it1->b > it2->b ? inf : -inf; else it1->p=floor(it2->b - it1->b, it1->a - it2->a);
        return it1->p >= it2->p; }
    void add(int a, int b) {
        auto z=insert({a, b, 0}); auto y=z++,
        x=y; while (isect(y, z)) z=erase(z);
        if (x!=begin() && isect(--x,y)) isect(x,y=erase(y));
        while((y=x)!=begin()&&(--x)->p >= y->p) isect(x,erase(y));}
    int query(int x) { assert(!empty()); auto l=*lower_bound(x); return l.a*x+l.b;}
};
tpl_<bool upperHull=true> struct MonotonicCHT { deque<Line> h;
    static bool badUpper(const Line& x,const Line& y,const Line& z){
        ll lhs=(y.b-x.b)*(y.a-z.a), rhs=(z.b-y.b)*(x.a-y.a); return lhs >= rhs; }
    void add(const Line& ln){
        if(!upperHull){ ln.a=-ln.a; ln.b=-ln.b; }
        while(h.size()>=2 && badUpper(h[h.size()-2], h.back(), ln)) h.pop_back(); h.pb(ln); }
    int query(int x){
        if(h.empty()) return upperHull ? -INF : INF;
        while(h.size()>=2){
            int v0=h[0].at(x), v1=h[1].at(x);
            if(v1 >= v0) h.pop_front(); else break; }
        int res=h.front().at(x); return upperHull ? res : -res; }
};


int k, n, m;

void solve() {
  cin >> n;
  vi a(n); read(a);
  str s; cin >> s;
  // Only solve for canonical forms: starts with 1
  bool rev = false;
  if(s == "231" || s == "213") {
    rev = true;
    reverse(all(a));
    reverse(all(s));
  }
  if(s[0] == '3') {
    f(i, n) a[i] = n+1 - a[i];
    f(i, 3) {
      if(s[i] == '1') s[i] = '3';
      else if(s[i] == '3') s[i] = '1';
    }
  }
  assert(s == "123" || s == "321");
  
  int best = 0;
  int l = 0, r = 0;
  // find initial cnt
  {
    BIT x(n+1, _add, {}, 0), y(n+1, _add, {}, 0);
    fora(x, a) {
      best += y.query(0, )
    }
  }
  if(s == "123") {
    BIT left(n, _add, {}, 0);
    f(i, n) {
      
      f(j, i+1, n) {
        
      }
    }
  }
}

int32_t main() {
  int t; cin >> t; f(_, t) { solve(); };
}
