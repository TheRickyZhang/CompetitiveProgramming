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
vpii dirs={{1,0},{0,-1},{0,1},{-1,0}}; map<char, int> dirMap={{'E',0},{'S',1},{'N',2},{'W',3}}; auto check=[](auto y,auto x,auto m,auto n){return y>=0&&y<m&&x>=0&&x<n;};
struct pairHash{tpl_<class T1,class T2>size_t operator()(const pair<T1,T2>&p)const{return hash<T1>{}(p.first)^ (hash<T2>{}(p.second)<<1);}}; struct vectorHash{tpl_<class T>size_t operator()(const v<T>&v)const{size_t hashTalue=0;for(const T&i:v)hashTalue^=hash<T>{}(i)+0x9e3779b9+(hashTalue<<6)+(hashTalue>>2);return hashTalue;}};
auto ad = [](int a, int b) {return a+b;}; auto sub = [](int a, int b) {return a-b;}; auto sortinv = [](const pii& a,const pii& b) {if(a.ff == b.ff) return a.ss > b.ss; return a.ff < b.ff;};
tpl_<class T, class U> T fstTrue(T l, T r, U ff) { for(++r; l < r;) { T m = l+(r-l) / 2; if(ff(m)) r = m; else l = m+1; } return l; }
tpl_<class T, class U> T lstTrue(T l, T r, U ff) { for(++r; l < r;) { T m = l+(r-l) / 2; if(ff(m)) l = m+1; else r = m; } return l-1; }
tpl_<class T> bool       ckmn(T& a, const T& b) {return b < a ? a = b, 1 : 0;}  tpl_<class T> bool ckmx(T& a, const T& b) {return a < b ? a = b, 1 : 0;}
#define str string
    int N = 100000; int MOD=1e9+7; constexpr int INF=1e9; constexpr int INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";
int ceil(int num, int den) { return num >= 0 ? (num + den - 1) / den : num / den; } int fastPow(int a, int b, int mod = MOD) { int res = 1; a %= mod; while (b > 0) { if (b & 1) res = res * a % mod; a = a * a % mod; b >>= 1; } return res; } int fastLog(int a, int b) {int res = 0; int p = 1; while (p <= b / a) { p *= a; res++;} return res; }
inline int mult(int a, int b, int m = MOD) {return (a % m * b % m) % m;} inline int add(int a, int b, int m = MOD) {return (a % m+b % m) % m;}
vb sieve(const int n){vb p(n+1,true);p[0]=p[1]=false;for(int i=2;i*i<=n;++i)if(p[i])for(int j=i*i;j<=n;j+=i)p[j]=false;return p;} vi sieveList(int n){vb p=sieve(n);vi primes;for(int i=2;i<=n;++i)if(p[i])primes.pb(i);return primes;}
class Matrix {public: vvi v; explicit Matrix(int n): v(n, vi(n, 0)){}
    Matrix operator*(const Matrix &m) const {int n=v.size(); Matrix r(n); f(i,n) f(k,n) f(j,n) r.v[i][j]=(r.v[i][j]+v[i][k]*m.v[k][j])%MOD; return r;}
    Matrix operator^(int64_t p) const {int n=v.size(); Matrix r(n), b=*this; f(i,n) r.v[i][i]=1; while(p){if(p&1)r=r*b; b=b*b; p>>=1;} return r;}};
void read(vi &v) { for (auto &x : v) cin >> x; } struct cind { tpl_ <tn_ T> cind& operator>>(T &x) { cin >> x; --x; return *this; }} cind;


int t, k, n, m;
void solve() {
    
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>k>>n;
    int cnt = n; // Width of bridges
    vpii nums;
    f(i, n) {
        char a, b; int x, y; cin>>a>>x>>b>>y;
        // No need to consider bridge placement or distance
        if(a==b) cnt += abs(y-x) - 1;
        else nums.pb({min(x, y), max(x, y)});
    }
    if(k==1) {
        vi temp;
        for(auto [x, y] : nums) {
            temp.pb(x); temp.pb(y);
        }
        sort(all(temp));
        int med = temp[temp.size()/2-1];
        int res = 0;
        for(int x : temp) res += abs(x-med);
        cout<<res+cnt<<en;
        return 0;
    }
    // Sort by average distance
    sort(all(nums), [&](pii& a, pii& b) {
        return a.ff + a.ss < b.ff + b.ss;
    });
    n = nums.size();


    // Now all we need to know is the running median to keep track of the running sum
    // Insight: using the two pq approach, we get rsum - lsum + med*(l.size()-r.size())
    int lsum=0, rsum=0;
    pq<int> l; mpq<int> r;
    auto insert = [&](int x) {
        if(l.empty() || x <= l.top()) {
            l.push(x);
            lsum += x;
        }
        else{
            r.push(x);
            rsum += x;
        }
        if(l.size() >= r.size()+2) {
            int y = l.top(); l.pop();
            r.push(y);
            lsum -= y, rsum += y;
        }
        if(r.size() > l.size()) {
            int y = r.top(); r.pop();
            l.push(y);
            rsum -= y, lsum += y;
        }
    };
    auto calculate = [&]() {
        int med = l.empty() ? 0 : l.top();
        return rsum - lsum + med*(l.size()-r.size());
    };
    vi left(n+1, 0); vi right(n+1, 0);
    f(i, n) {
        auto [x, y] = nums[i];
        insert(x); insert(y);
        left[i+1] = calculate();
    }
    lsum = 0, rsum = 0, l=pq<int>(), r = mpq<int>();
    repr(i, n-1, 0) {
        auto [x, y] = nums[i];
        insert(x); insert(y);
        right[i] = calculate();
    }
    int res = INFL;
    // cout<<left<<en<<right<<en;
    // cout<<cnt<<en;
    f(i, n+1) ckmn(res, left[i] + right[i]);
    cout<<res+cnt<<en;
}
