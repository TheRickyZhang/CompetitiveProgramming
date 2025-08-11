#include  <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define op_ operator
#define cx_ constexpr
#define fn function
#define f(i, to) for (int i = 0; i < to; ++i)
#define fe(i, to) for (int i = 1; i <= to; ++i)
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define repr(i, a, b) for (int i = a; i >= b; --i)
#define ff first
#define ss second
#define pb push_back
#define fora(a, x) for (auto &(a) : (x))
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define quit(s) do{ cout<<(s)<<en; return; }while(false)

#define int long long
tpl_<tn_ T>using v=vector<T>; using vi=v<int>; tpl_<tn_ T>using vv=v<v<T>>; using ll=long long; using pii=pair<int,int>;
using vb=v<bool>; using vvb=v<vb>; using vs=v<string>; using iii=array<int, 3>; using i4=array<int, 4>;
using vvi=v<vi>; using vll=v<ll>; using vpii=v<pii>; using vvpii=v<vpii>;
cx_ auto en="\n"; cx_ auto sp=" "; using str=string; typedef fn<void(int,int)>fvii; typedef fn<void(int,int,int)>fviii;
cx_ int INF=1e9; cx_ ll INFL=0x3f3f3f3f3f3f3f3f; cx_ int B=31;
struct Line { mutable int a, b, p; // =ax+b, last optimal x
    Line(int a, int b, int p=0) : a(a), b(b), p(p) {}
    int at(int x) const { return a*x + b; }
    bool operator<(const Line& o) const { return a < o.a; } bool operator<(int x) const { return p < x;   }
    friend long double intersect(Line x, Line y) { return static_cast<long double>(y.b-x.b) / static_cast<long double>(x.a-y.a); }
};
struct CHT : multiset<Line, less<>> {
    static constexpr int inf=LLONG_MAX; static int floor(int a, int b) { return a/b - ((a^b)<0 && a%b); }
    bool isect(iterator it1, iterator it2) { if (it2 == end()) { it1->p=inf;return false;}
        if (it1->a == it2->a) it1->p=it1->b > it2->b ? inf : -inf; else it1->p=floor(it2->b - it1->b, it1->a - it2->a);
        return it1->p >= it2->p; }
    void add(int a, int b) {
        auto z=insert({a, b, 0}); auto y=z++, x=y; while (isect(y, z)) z=erase(z);
        if (x!=begin() && isect(--x,y)) isect(x,y=erase(y)); while((y=x)!=begin()&&(--x)->p >= y->p) isect(x,erase(y));}
    int query(int x) { assert(!empty()); auto l=*lower_bound(x); return l.a*x+l.b;} // min -> negate inserted a, b, x
};
tpl_<bool upperHull=true> struct MonotonicCHT { deque<Line> h;
    static bool badUpper(const Line& x,const Line& y,const Line& z){
        __int128 lhs=(y.b-x.b)*(y.a-z.a), rhs=(z.b-y.b)*(x.a-y.a); return lhs >= rhs; }
    void add(Line ln){
        if(!upperHull){ ln.a=-ln.a; ln.b=-ln.b; }
        while(h.size()>=2 && badUpper(h[h.size()-2], h.back(), ln)) h.pop_back(); h.pb(ln); }
    int query(int x){
        if(h.empty()) return upperHull ? -INFL : INFL;
        while(h.size()>=2){
            int v0=h[0].at(x), v1=h[1].at(x);
            if(v1 >= v0) h.pop_front(); else break; }
        int res=h.front().at(x); return upperHull ? res : -res; }
};

int k, n, m;
void solve() {

}

int32_t main() {
    // This is the forward dp
    // dp[i] = min dp[j] + (c[i] - c[j]) * (t_i + x*(#segments so far))
    // - the trick is we can do a backwards dp to account for the cumulative +x cost
    // dp[i] = min dp[j+1] + (x + t[j]-t[i-1]) + (c[n] - c[i-1)
    // = t[j] * (c[n]-c[i-1]) + dp[j+1] + (x-t[i-1]) * (c[n]-c[i-1])
    cin>>n;
    int x; cin>>x;
    vi t(n+1, 0), c(n+1, 0);
    fe(i, n) cin>>t[i]>>c[i];
    fe(i, n) t[i] += t[i-1];
    fe(i, n) c[i] += c[i-1];
    MonotonicCHT<false> cht;
    vi res(n+2, 0);
    repr(i, n, 1) {
        int cc = c[n]-c[i-1];
        cht.add(Line(t[i], res[i+1]));
        res[i] = cht.query(cc) + (x-t[i-1]) * cc;
    }
    // cout<<res<<en;
    cout<<res[1]<<en;
}
