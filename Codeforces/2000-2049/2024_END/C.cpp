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
tpl_<tn_ T>using v=vector<T>; using ll=long long; using pii=pair<int,int>; using pll=pair<ll,ll>; using t3=tuple<int,int,int>; using t4=tuple<int,int,int,int>;
using vi=v<int>; using vb=v<bool>; using vs=v<string>; using vvi=v<vi>; using vll=v<ll>; using vvll=v<vll>; using vpii=v<pii>; using vvpii=v<vpii>; using vpll=v<pll>; using vvpll=v<vpll>;
tpl_<tn_ K,tn_ V>using ump=unordered_map<K, V>; tpl_<tn_ T>using ust=unordered_set<T>; tpl_<tn_ K,tn_ V>using rmap=map<K,V,greater<K>>; tpl_<tn_ T>using rset=set<T,greater<T>>; tpl_<tn_ T>using mset=multiset<T>; tpl_<tn_ T>using rmset=multiset<T,greater<T>>;
tpl_<tn_ T>using pq=priority_queue<T>; tpl_<tn_ T>using mpq=priority_queue<T,vector<T>,greater<T>>;
tpl_<tn_ A, tn_ B> ostream& operator<<(ostream& os, const pair<A, B>& p) { return os << "(" << p.ff << ", " << p.ss << ")"; }
tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, str>, typename C::value_type>> ostream& operator<<(ostream& os, const C& v) { os << "{"; str sep; for (const T& x : v) os << sep << x, sep = ", "; return os << "}"; }
tpl_<tn_ K, tn_ V> ostream& operator<<(ostream& os, const map<K, V>& m) { os << "{"; str sep; for (const auto& kv : m) os << sep << kv.ff << ": " << kv.ss, sep = ", "; return os << "}"; }
struct pairHash{tpl_<class T1,class T2>size_t operator()(const pair<T1,T2>&p)const{return hash<T1>{}(p.first)^ (hash<T2>{}(p.second)<<1);}}; struct vectorHash{tpl_<class T>size_t operator()(const vector<T>&v)const{size_t hashValue=0;for(const T&i:v)hashValue^=hash<T>{}(i)+0x9e3779b9+(hashValue<<6)+(hashValue>>2);return hashValue;}};
const vector<pii> dirs={{1,0},{0,-1},{0,1},{-1,0}}; auto check=[](auto y,auto x,auto m,auto n){return y>=0&&y<m&&x>=0&&x<n;};
constexpr int MOD=1000000007; constexpr int INF=1000000000; constexpr ll INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";
tpl_<tn_ T> T ceil(T num, T den) { return (num+den-1)/den;} tpl_<tn_ T> T mul(T a, T b, T mod=MOD) {return ((a%mod)*(b%mod))%mod;} tpl_<tn_ T>T add(T a, T b, T mod=MOD) {return (a+b) % mod;}

ll t, k, n, m;

// Editorial solution SO MUCH SIMPLER
// Insight: the contributions and splitting process are equivalent with (n+1) * sum / 2, where sum += current power of 2 each odd len
ll len(ll l, ll r) {
    return r-l+1;
}
ll mid(ll l, ll r) {
    return (l+r)/2;
}
void solve(){
    cin >> n >> k;
    ump<ll, pll> offset;
    ump<ll, ll> sum;
    function<void(ll, ll)> search = [&](ll l, ll r) {
        ll x = len(l, r);
        if(x < k){
            offset[x] = {0, 0};
            return;
        }
        ll m = mid(l, r);
        if (offset.count(x)) {
            // auto [a, b] = offset[x];
            // cout<<"returning "<<a*m+b<<" for "<<l<<sp<<r<<en;
            return;
        }

        // Even case
        if(x % 2 == 0) {
            ll llen = len(l, m);
            ll rlen = len(m+1, r);
            search(l, m); search(m+1, r);
            auto [a1, b1] = offset[llen];
            auto [a2, b2] = offset[rlen];
            ll ld = mid(l, m) - m;
            ll rd = mid(m+1, r) - m;
            offset[x] = {a1+a2, a1*ld + a2*rd + (b1 + b2)};
            // auto [a, b] = offset[x];
            // cout<<"returning "<<a*m+b<<" for "<<l<<sp<<r<<en;
            // return a*m+b;
        } else {
            ll llen = len(l, m-1);
            ll rlen = len(m+1, r);
            search(l, m-1); search(m+1, r);
            auto [a1, b1] = offset[llen];
            auto [a2, b2] = offset[rlen];
            ll ld = mid(l, m-1) - m;
            ll rd = mid(m+1, r) - m;
            offset[x] = {1+a1+a2, a1*ld + a2*rd + (b1 + b2)};
            // auto [a, b] = offset[x];
            // cout<<"returning "<<a*m+b<<" for "<<l<<sp<<r<<en;
            // return a*m+b;
        }
    };
    search(1, n);
    // cout<<offset<<en;
    auto [a, b] = offset[len(1, n)];
    // cout<<a<<sp<<mid(1, n)<<sp<<b<<en;
    cout<<a*mid(1, n)+b<<en;

    // cout<<res<<en;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while(t--) solve();
}