// #include <bits/stdc++.h>
// using namespace std;
//
// #define tpl_ template
// #define tn_ typename
// #define f(i, to) for (int i = 0; i < (to); ++i)
// #define fe(i, to) for (int i = 1; i <= (to); ++i)
// #define rep(i, a, b) for (int i = (a); i <= (b); ++i)
// #define repr(i, a, b) for (int i = (a); i >= (b); --i)
// #define ff first
// #define ss second
// #define pb push_back
// #define trav(a, x) for (auto &a : x)
// #define all(x) begin(x), end(x)
// #define rall(x) rbegin(x), rend(x)
// #define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");
//
// #define int long long
// tpl_<tn_ T>        using v = vector<T>;  using ll=long long;  using pii=pair<int,int>;  using pll=pair<ll,ll>;  using iii=tuple<int,int,int>;       using t4=tuple<int,int,int,int>;
// using vi=v<int>;   using vb=v<bool>;     using vvb=v<vb>;     using vs=v<string>;       using vvi=v<vi>;        using vll=v<ll>;using vvll=v<vll>; using vpii=v<pii>; using vvpii=v<vpii>; using vpll=v<pll>; using vvpll=v<vpll>;
// tpl_<tn_ K,tn_ T>  using ump=unordered_map<K, T>;  tpl_<tn_ T>using ust=unordered_set<T>;  tpl_<tn_ K,tn_ T>    using rmap=map<K,T,greater<K>>; tpl_<tn_ T> using rset=set<T,greater<T>>; tpl_<tn_ T> using mset=multiset<T>; tpl_<tn_ T>using rmset=multiset<T,greater<T>>;
// tpl_<tn_ T>        using pq=priority_queue<T>;     tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;
// tpl_<class It, class T>     auto leq_bound  (It first, It last, T val) { auto it = upper_bound(first, last, val); return it != first ? prev(it) : last;} tpl_<class C, class T>auto leq_bound(C& c, T val) {auto it = c.upper_bound(val);return it != c.begin() ? prev(it) : c.end();}
// tpl_<class It, class T>     auto less_bound (It first, It last, T val) {auto it = lower_bound(first, last, val);return it != first ? prev(it) : last; }tpl_<class C, class T>auto less_bound(C& c, T val) {auto it = c.lower_bound(val);return it != c.begin() ? prev(it) : c.end();}
// tpl_<class C, class T>      auto lower_bound(C& c, T val) {return c.lower_bound(val);} tpl_<class C, class T>auto upper_bound(C& c, T val) {return c.upper_bound(val);}
// tpl_<tn_ A, tn_ B> ostream& operator<<(ostream& os, const pair<A, B>& p){ return os<<"("<<p.ff<<", "<<p.ss<<")";}
// tpl_<tn_ A> ostream&        operator<<(ostream& os, const v<v<A>>& v)   { for (const auto& row : v) { os << "{ "; for (const auto& elem : row) {os<<elem<<" ";}os<<"}"; os<<"\n";} return os;}
// tpl_<tn_ K, tn_ T> ostream& operator<<(ostream& os, const map<K, T>& m) { os << "{"; string sep; for (const auto& kv : m) os << sep << kv.ff << ": " << kv.ss, sep = ", "; return os << "}"; }
// tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, string>, typename C::value_type>> ostream& operator<<(ostream& os, const C& v) { os<<"{"; string sep; for(const T& x : v) os<<sep<<x, sep=", "; return os<<"}";}
// vpii dirs={{1,0},{0,-1},{0,1},{-1,0}}; map<char, int> dirMap={{'E',0},{'S',1},{'N',2},{'W',3}}; auto check=[](auto y,auto x,auto m,auto n){return y>=0&&y<m&&x>=0&&x<n;};
// struct pairHash{tpl_<class T1,class T2>size_t operator()(const pair<T1,T2>&p)const{return hash<T1>{}(p.first)^ (hash<T2>{}(p.second)<<1);}}; struct vectorHash{tpl_<class T>size_t operator()(const v<T>&v)const{size_t hashTalue=0;for(const T&i:v)hashTalue^=hash<T>{}(i)+0x9e3779b9+(hashTalue<<6)+(hashTalue>>2);return hashTalue;}};
// auto ad = [](int a, int b) {return a+b;}; auto sub = [](int a, int b) {return a-b;}; auto sortinv = [](const pii& a,const pii& b) {if(a.ff == b.ff) return a.ss > b.ss; return a.ff < b.ff;};
// struct DSU{ vi p,sz; explicit
//          DSU(const int n){p.resize(n),sz.resize(n,1),iota(all(p),0);}
//     int  par(int x){return x==p[x]?x:p[x]=par(p[x]);}
//     void merge(int x,int y){x=par(x),y=par(y);if(x!=y){if(sz[x]<sz[y])swap(x,y);p[y]=x,sz[x]+=sz[y];}}
// };
// tpl_<tn_ T> struct Segtree { int n; v<T> t, nums; T z; function<T(T, T)> c;
//     Segtree() : n(0), z(0), c([](T a, T b) { return a + b; }) {}
//     Segtree(int sz, T zero, function<T(T, T)> combine, const v<T>& init = {}) : n(sz), t(4 * sz, zero), nums(sz, zero), z(zero), c(move(combine)) { if (!init.empty()) { nums = init; build(1, 0, n-1); } }
//     void build (int i, int a, int b) { if (a == b) { t[i] = nums[a]; return; } int m = (a + b) / 2; build(2 * i, a, m); build(2 * i + 1, m + 1, b); t[i] = c(t[2 * i], t[2 * i + 1]); }
//     void add   (int i, int a, int b, int p, T x) { if(a==b) { t[i] = c(t[i], x); return; } int m = (a + b) / 2; (p <= m ? add(2 * i, a, m, p, x) : add(2 * i + 1, m + 1, b, p, x)); t[i] = c(t[2 * i], t[2 * i + 1]); }
//     void update(int i, int a, int b, int p, T x) { if(a==b) { t[i] = x;          return; } int m = (a + b) / 2; (p <= m ? update(2 * i, a, m, p, x) : update(2 * i + 1, m + 1, b, p, x)); t[i] = c(t[2 * i], t[2 * i + 1]); }
//     void updateWithDiff(int i, int a, int b, int p, T x, function<T(T, T)> minus) { T diff = minus(x, nums[p]); nums[p] = x; add(i, a, b, p, diff); }
//     T query(int i, int a, int b, int l, int r) { if (l > r) return z; if (a == l && b == r) return t[i]; int m = (a + b) / 2; return c(query(2 * i, a, m, l, min(r, m)), query(2 * i + 1, m + 1, b, max(l, m + 1), r)); }
//     void add(int p, T x) { add(1, 0, n-1, p, x); }
//     void update(int p, T x) { update(1,0,n-1,p,x); }
//     void updateWithDiff(int p, T x, function<T(T, T)> minus = sub) { updateWithDiff(1, 0, n-1, p, x, minus); }
//     T query(int l, int r) { return query(1, 0, n-1, l, r); }
// };
// tpl_<tn_ T> struct BIT     { int n; v<T> t, nums; T z; function<T(T, T)> c;   // All 0-indexed
//     BIT() : n(0), z(0), c([](T a, T b) { return a+b; }) {}
//     BIT(int sz, T zero, function<T(T, T)> combine, const v<T>& init = {}) : n(sz), t(sz+1, zero), nums(sz, zero), z(zero), c(std::move(combine)) { if (!init.empty()) { nums = init; f(i, n) add(i, nums[i]); } }
//     void add(int i, T x) { nums[i] += x; for (i += 1; i <= n; i += (i & -i)) t[i] = c(t[i], x); }
//     void update(int i, T x) { T diff = x-nums[i]; nums[i] = x; for (i += 1; i <= n; i += (i & -i)) t[i] = c(t[i], diff); }
//     T query(int i) { T res = z; for (i += 1; i > 0; i -= (i & -i)) res = c(res, t[i]); return res; }
//     T query(int l, int r) { return query(r)-query(l-1); }
// };
// typedef function<void(int, int)> autotree;
// tpl_<tn_ T> ostream& operator<<(ostream& os, const Segtree<T>& seg) {
//     int maxRows=20, rowCount=0, maxDepth=4; function<void(int,int,int,int)> pt; pt=[maxRows, maxDepth, &rowCount, &os, &seg, &pt](int i,int a,int b,int d){ if(a>b||rowCount>=maxRows||d>maxDepth)return;
//     os<<string(d*2,' ')<<"["<<a<<","<<b<<"]: "<<seg.t[i]<<"\n"; rowCount++; if(a!=b){ int m=(a+b)/2; pt(2*i,a,m,d+1); pt(2*i+1,m+1,b,d+1); } }; os<<"Segtree:\n"; pt(1,0,seg.n-1,0); return os;
// }
// tpl_<tn_ T> ostream& operator<<(ostream& os, const BIT<T>& bit) {
//     os<<"BIT:\n"; int maxCol = 16, lvls = 0; while ((1<<lvls) <= min(bit.n, maxCol)) lvls++; int cols = min(bit.n, maxCol); v<vs> grid(lvls, vs(cols, string(4, ' ')));
//     fe(i, cols) { int row = __builtin_ctz(i); if (row<lvls) {ostringstream oss; oss<<setw(4)<<bit.t[i]; grid[row][i-1] = oss.str(); } } f(r, lvls) { f(c, cols) os<<grid[r][c]; os<<"\n"; } return os;
// }
// tpl_<class T, class U> T fstTrue(T l, T r, U ff) { for(++r; l < r;) { T m = l+(r-l) / 2; if(ff(m)) r = m; else l = m+1; } return l; }
// tpl_<class T, class U> T lstTrue(T l, T r, U ff) { for(++r; l < r;) { T m = l+(r-l) / 2; if(ff(m)) l = m+1; else r = m; } return l-1; }
// tpl_<class T> bool       ckmn(T& a, const T& b) {return b < a ? a = b, 1 : 0;}  tpl_<class T> bool ckmx(T& a, const T& b) {return a < b ? a = b, 1 : 0;}
// #define str string
//     int N = 200000; int MOD=1e9+7; constexpr int INF=1e9; constexpr int INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";
// int ceil(int num, int den) { return (num+den-1) / den; } int fastPow(int a, int b, int mod = MOD) { int res = 1; a %= mod; while (b > 0) { if (b & 1) res = res * a % mod; a = a * a % mod; b >>= 1; } return res; } int fastLog(int a, int b) {int res = 0; int p = 1; while (p <= b / a) { p *= a; res++;} return res; }
// vb sieve(const int n){vb p(n+1,true);p[0]=p[1]=false;for(int i=2;i*i<=n;++i)if(p[i])for(int j=i*i;j<=n;j+=i)p[j]=false;return p;} vi sieveList(int n){vb p=sieve(n);vi primes;for(int i=2;i<=n;++i)if(p[i])primes.pb(i);return primes;}
// inline int mult(int a, int b, int m = MOD) {return (a % m * b % m) % m;} inline int add(int a, int b, int m = MOD) {return (a % m+b % m) % m;}
// class Matrix {public: vvi v; explicit Matrix(int n): v(n, vi(n, 0)){}
//     Matrix operator*(const Matrix &m) const {int n=v.size(); Matrix r(n); f(i,n) f(k,n) f(j,n) r.v[i][j]=(r.v[i][j]+v[i][k]*m.v[k][j])%MOD; return r;}
//     Matrix operator^(int64_t p) const {int n=v.size(); Matrix r(n), b=*this; f(i,n) r.v[i][i]=1; while(p){if(p&1)r=r*b; b=b*b; p>>=1;} return r;}};
// void read(vi &v) { for (auto &x : v) cin >> x; } struct cind { tpl_ <tn_ T> cind& operator>>(T &x) { cin >> x; --x; return *this; }} cind;
//
//
// vi fact(N+1, 1);
// vi invFact(N+1, 1);
// int ncr(int n, int r) {
//     int dem = (invFact[r] * invFact[n-r]) % MOD;
//     return (fact[n] * dem) % MOD;
// }
//
// void solve() {
//     int n; cin>>n;
//     vi a(n); read(a);
//     vi freq(N+1, 0);
//     f(i, n) freq[a[i]]++;
//     int mx = N;
//     repr(i, N, 0) {
//         if(freq[i]!=0) {
//             mx=i;
//             freq.resize(mx+1);
//             break;
//         }
//     }
//     if(mx<0) {cout<<0<<en; return;}
//     // { current number, min freq }
//     vvi dp(mx+1);
//     dp[0].resize(freq[0]+1, 0);
//     rep(i, 1, freq[0]) {
//         dp[0][i] = ncr(freq[0], i);
//     }
//     vvi pre(mx+1);
//     pre[0].resize(dp[0].size()+1, 0);
//     f(i, dp[0].size()) {
//         pre[0][i+1] = (pre[0][i] + dp[0][i]) % MOD;
//     }
//     vvi preCount(N+1);
//     auto queryDP = [&](int i, int l, int r) {
//         return (pre[i][r+1] - pre[i][l] + MOD) % MOD;
//     };
//     auto queryCount = [&](int n, int l, int r) {
//         return (preCount[n][r+1] - preCount[n][l] + MOD) % MOD;
//     };
//     int mn = freq[0];
//     rep(i, 1, mx) {
//         int x = freq[i];
//         ckmn(mn, x);
//         dp[i].resize(mn+1, 0);
//         repr(j, mn-1, 0) {
//             // This is setting the current minimum, so must be exactly j
//             dp[i][j] += (queryDP(i-1, j+1, dp[i-1].size()-1) * ncr(x, j)) % MOD;
//             dp[i][j] %= MOD;
//         }
//         if(preCount[x].empty()) {
//             preCount[x].resize(x+2, 0);
//             f(j, x+1) {
//                 preCount[x][j+1] = (preCount[x][j] + ncr(x, j)) % MOD;
//             }
//         }
//         rep(j, 0, mn) {
//             // Not setting the current minimum - can choose any j >= mn
//             dp[i][j] += (dp[i-1][j] * queryCount(x, j, x)) % MOD;
//             dp[i][j] %= MOD;
//         }
//         pre[i].resize(mn+2, 0);
//         f(j, mn+1) pre[i][j+1] = (pre[i][j] + dp[i][j]) % MOD;
//     }
//     cout<<dp<<en;
//     int tot = n;
//     int res = 0;
//     rep(i, 0, mx) {
//         tot -= freq[i];
//         rep(j, 1, dp[i].size()-1) {
//             res += ((j * dp[i][j]) % MOD * fastPow(2, tot, MOD)) % MOD;
//             res %= MOD;
//         }
//     }
//     cout<<res<<en;
// }
//
// int32_t main() {
//     ios::sync_with_stdio(false); cin.tie(nullptr);
//     rep(i, 2, N) fact[i] = (fact[i-1] * i) % MOD;
//     invFact[N] = fastPow(fact[N], MOD-2, MOD);
//     repr(i, N-1, 0) invFact[i] = (invFact[i+1] * (i+1)) % MOD;
//
//     int t; cin>>t; f(i, t) solve();
// }

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define vi vector<int>
#define vvi vector<vi>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define f(i, to) for (int i = 0; i < (to); i++)
#define pb push_back
#define all(x) begin(x), end(x)

const int MX = 200000; // 2e5
const int MOD = 998244353;

ll fact[MX+1];
ll ifact[MX+1];

ll binPow(ll base, ll exp) {
    ll ans = 1;
    while(exp) {
        if(exp % 2)
            ans = (ans * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return ans;
}

int nCk(int N, int K) {
    if(K > N || K < 0)
        return 0;
    return (fact[N] * ((ifact[K] * ifact[N-K]) % MOD)) % MOD;
}

void ICombo() {
    fact[0] = 1;
    rep(i, 1, MX) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    ifact[MX] = binPow(fact[MX], MOD-2);
    for (int i = MX-1; i >= 0; i--) {
        ifact[i] = (ifact[i+1] * (i+1)) % MOD;
    }
}

void solve() {
    int n, ans = 0;
    cin >> n;
    // Create a frequency array "c" of length n.
    vi c(n, 0);
    // This loop reads n numbers and uses each number as an index to increment frequency.
    for (int r : c) {
        int tmp;
        cin >> tmp;
        c[tmp]++;
    }
    // dp[i] will store a vector for group i.
    vvi dp(n, vi(1)); // each dp[i] starts with a single element 0.
    vi ps, co;
    // Base case: for group 0, set dp[0] = {0, nCk(c[0],1), ..., nCk(c[0], c[0])}
    for (int i = 1; i <= c[0]; i++)
        dp[0].pb(nCk(c[0], i));

    // Process groups 1..n-1.
    for (int i = 1; i < n; i++) {
        ps.resize(1);       // start ps with a single 0
        co = ps;            // initialize co similarly
        // Build prefix sum for dp[i-1]
        for (int r : dp[i-1])
            ps.pb((ps.back() + r) % MOD);
        int m = ps.size() - 1;
        // Resize dp[i] to have min(m, c[i]+1) entries.
        dp[i].resize(min(m, c[i] + 1));
        // Build prefix sums for binomials for current group i.
        for (int j = 0; j <= c[i]; j++)
            co.pb((co.back() + nCk(c[i], j)) % MOD);
        // Update dp[i] using the recurrence:
        // For each j from 1 to dp[i].size()-1:
        for (int j = 1; j < dp[i].size(); j++) {
            dp[i][j] = ( nCk(c[i], j) * ((ps[m] - ps[j] + MOD) % MOD) ) % MOD;
            dp[i][j] = ( dp[i][j] + ( ((co.back() - co[j+1] + MOD) % MOD) * dp[i-1][j] ) % MOD ) % MOD;
        }
    }
    // Compute final answer
    int idx = 0;
    for (auto r : dp) {
        n -= c[idx++];
        for (int i = 1; i < r.size(); i++) {
            ans = (ans + i * r[i] % MOD * binPow(2, n)) % MOD;
        }
    }
    cout << ans << "\n";
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ICombo();
    int t;
    cin >> t;
    while(t--)
        solve();
    return 0;
}

