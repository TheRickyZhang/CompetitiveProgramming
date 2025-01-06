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
tpl_<tn_ T>        using v=vector<T>;  using ll=long long;  using pii=pair<int,int>; using pll=pair<ll,ll>; using t3=tuple<int,int,int>;               using t4=tuple<int,int,int,int>;
using vi=v<int>;   using vb=v<bool>;   using vs=v<string>;  using vvi=v<vi>;         using vll=v<ll>;       using vvll=v<vll>; using vvb=v<vb>;        using vpll=v<pll>; using vvpll=v<vpll>;   using vpii=v<pii>; using vvpii=v<vpii>;
tpl_<tn_ K,tn_ T>  using ump=unordered_map<K, T>;  tpl_<tn_ T>using ust=unordered_set<T>; tpl_<tn_ K,tn_ T> using rmap=map<K,T,greater<K>>; tpl_<tn_ T>using rset=set<T,greater<T>>; tpl_<tn_ T> using mset=multiset<T>; tpl_<tn_ T>using rmset=multiset<T,greater<T>>;
tpl_<tn_ T>        using pq=priority_queue<T>;     tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;
tpl_<class It, class T>     auto leq_bound  (It first, It last, T val) { auto it = upper_bound(first, last, val); return it != first ? prev(it) : last;} tpl_<class C, class T>auto leq_bound(C& c, T val) {auto it = c.upper_bound(val);return it != c.begin() ? prev(it) : c.end();}
tpl_<class It, class T>     auto less_bound (It first, It last, T val) {auto it = lower_bound(first, last, val);return it != first ? prev(it) : last; }tpl_<class C, class T>auto less_bound(C& c, T val) {auto it = c.lower_bound(val);return it != c.begin() ? prev(it) : c.end();}
tpl_<class C, class T>      auto lower_bound(C& c, T val) {return c.lower_bound(val);} tpl_<class C, class T>auto upper_bound(C& c, T val) {return c.upper_bound(val);}
tpl_<tn_ A, tn_ B> ostream& operator<<(ostream& os, const pair<A, B>& p){ return os<<"("<<p.ff<<", "<<p.ss<<")";}
tpl_<tn_ A> ostream&        operator<<(ostream& os, const v<v<A>>& v)   { for (const auto& row : v) { os << "{ "; for (const auto& elem : row) {os<<elem<<" ";}os<<"}"; } return os;}
tpl_<tn_ K, tn_ T> ostream& operator<<(ostream& os, const map<K, T>& m) { os << "{"; str sep; for (const auto& kv : m) os << sep << kv.ff << ": " << kv.ss, sep = ", "; return os << "}"; }
tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, str>, typename C::value_type>> ostream& operator<<(ostream& os, const C& v) { os<<"{"; str sep; for(const T& x : v) os<<sep<<x, sep=", "; return os<<"}";}
struct pairHash{tpl_<class T1,class T2>size_t operator()(const pair<T1,T2>&p)const{return hash<T1>{}(p.first)^ (hash<T2>{}(p.second)<<1);}}; struct vectorHash{tpl_<class T>size_t operator()(const vector<T>&v)const{size_t hashTalue=0;for(const T&i:v)hashTalue^=hash<T>{}(i)+0x9e3779b9+(hashTalue<<6)+(hashTalue>>2);return hashTalue;}};
struct DSU{ vi p,sz; explicit
        DSU(const int n){p.resize(n),sz.resize(n,1),iota(all(p),0);}
    int par(int x){return x==p[x]?x:p[x]=par(p[x]);}
    void merge(int x,int y){x=par(x),y=par(y);if(x!=y){if(sz[x]<sz[y])swap(x,y);p[y]=x,sz[x]+=sz[y];}}
};
template <typename T> struct Segtree { ll n; v<T> t; T z; function<T(T, T)> c;
    Segtree(ll sz, T zero, function<T(T, T)> combine) : n(sz), t(4 * sz, zero), z(zero), c(move(combine)) {}
    void update(ll i, ll a, ll b, ll p, T x) { if (a == b) { t[i] = x; return; } ll m = (a + b) / 2; (p <= m ? update(2 * i, a, m, p, x) : update(2 * i + 1, m + 1, b, p, x)); t[i] = c(t[2 * i], t[2 * i + 1]); } void update(ll p, T x) { update(1, 0, n - 1, p, x); }
    T query(ll i, ll a, ll b, ll l, ll r) { if (l > r) return z; if (a == l && b == r) return t[i]; ll m = (a + b) / 2; return c(query(2 * i, a, m, l, min(r, m)), query(2 * i + 1, m + 1, b, max(l, m + 1), r)); } T query(ll l, ll r) { return query(1, 0, n - 1, l, r); }
};
const vector<pii> dirs={{1,0},{0,-1},{0,1},{-1,0}}; auto check=[](auto y,auto x,auto m,auto n){return y>=0&&y<m&&x>=0&&x<n;};
constexpr int N = 300001; constexpr ll MOD=1000000007; constexpr int INF=1000000000; constexpr ll INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";
tpl_<tn_ T> T ceil(T num, T den) { return (num+den-1)/den;} tpl_<tn_ T> T mult(T a, T b, T mod=MOD) {return ((a%mod)*(b%mod))%mod;} tpl_<tn_ T>T add(T a, T b, T mod=MOD) {return (a+b) % mod;}
vb sieve(const int n){vb p(n+1,true);p[0]=p[1]=false;for(int i=2;i*i<=n;++i)if(p[i])for(int j=i*i;j<=n;j+=i)p[j]=false;return p;} vi sieveList(int n){vb p=sieve(n);vi primes;for(int i=2;i<=n;++i)if(p[i])primes.pb(i);return primes;}

int t, k, n, m;
void solve() {
    
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>k;
    vll nums(n); f(i, n) cin>>nums[i];
    vpll p(n);
    ll x=0, y=0;
    f(i, n) {
        ll a=0, b=0;
        while(nums[i] % 2 == 0) {
            nums[i] >>=1; a++;
        }
        while(nums[i] % 5 == 0) {
            nums[i] /= 5; b++;
        }
        p[i] = {a, b};
        x+=a, y+=b;
    }
    // cout<<p<<en;

    // [i][j] = how many taken,
    vvll dp(k+1, vll(y+1, -INFL));
    auto dpp = dp;
    dp[0][0] = 0;
    f(ii, n) {
        auto [a, b] = p[ii];
        repr(i, k, 0) {
            repr(j, y, 0) {
                dpp[i][j] = dp[i][j];
                if(i+1 <= k && j+b <= y) dpp[i+1][j+b] = max(dp[i+1][j+b], dp[i][j] + a);
            }
        }
        repr(i, k, 0) {
            repr(j, y, 0) {
                dp[i][j] = dpp[i][j];
                dpp[i][j] = 0;
            }
        }
    }
    // cout<<dp<<en;
    ll res = 0;
    f(i, y+1) {
        // cout<<i<<sp<<dp[k][i]<<en;
        res = max(res, min(1LL * i, dp[k][i]));
    }
    cout<<res<<en;

    // Good logic, but MLE
    // auto dp = v<vvb>(x+1, vvb(y+1, vb(kk+1, false)));
    // auto dpp = dp;
    // dp[0][0][0] = true;
    //
    // int res = 0;
    // for(auto [a, b] : p) {
    //     repr(i, x, 0) {
    //         repr(j, y, 0) {
    //             repr(k, kk, 0) {
    //                 dpp[i][j][k] = dp[i][j][k];
    //                 if(k+1<=kk && dp[i][j][k]) {
    //                     dpp[i+a][j+b][k+1] = true;
    //                     res = max(res, min(i+a, j+b));
    //                 }
    //             }
    //         }
    //     }
    //     f(i, x+1) f(j, y+1) f(k, kk+1) {
    //         dp[i][j][k] = dpp[i][j][k];
    //         dpp[i][j][k] = false;
    //     }
    // }
    // cout<<res<<en;
}
