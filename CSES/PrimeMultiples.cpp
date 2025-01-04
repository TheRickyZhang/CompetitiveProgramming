#include <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define f(i, to) for (ll i = 0; i < (to); ++i)
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
tpl_<tn_ K,tn_ boxes>using ump=unordered_map<K, boxes>; tpl_<tn_ T>using ust=unordered_set<T>; tpl_<tn_ K,tn_ boxes>using rmap=map<K,boxes,greater<K>>; tpl_<tn_ T>using rset=set<T,greater<T>>; tpl_<tn_ T>using mset=multiset<T>; tpl_<tn_ T>using rmset=multiset<T,greater<T>>;
tpl_<tn_ T>using pq=priority_queue<T>; tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;
tpl_<class It, class T> auto leq_bound(It first, It last, T val) { auto it = upper_bound(first, last, val); return it != first ? prev(it) : it;} tpl_<class C, class T>auto leq_bound(C& c, T val) {auto it = c.upper_bound(val);return it != c.begin() ? prev(it) : it;}
tpl_<class It, class T> auto less_bound(It first, It last, T val) {auto it = lower_bound(first, last, val);return it != first ? prev(it) : it; }tpl_<class C, class T>auto less_bound(C& c, T val) {auto it = c.lower_bound(val);return it!=c.begin()?prev(it):it;}
tpl_<class C, class T>auto lower_bound(C& c, T val) {return c.lower_bound(val);} tpl_<class C, class T>auto upper_bound(C& c, T val) {return c.upper_bound(val);}
tpl_<tn_ A, tn_ B> ostream& operator<<(ostream& os,const pair<A, B>& p){return os<<"("<<p.ff<<", "<<p.ss<<")";}
tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, str>, typename C::value_type>> ostream& operator<<(ostream& os, const C& v) { os<<"{"; str sep; for(const T& x : v) os<<sep<<x, sep=", "; return os<<"}";}
tpl_<tn_ A> ostream& operator<<(ostream& os, const v<v<A>>& v) { for (const auto& row : v) { os << "{ "; for (const auto& elem : row) {os<<elem<<" ";}os<<"}"<<"\n"; } return os;}
tpl_<tn_ K, tn_ boxes> ostream& operator<<(ostream& os, const map<K, boxes>& m) { os << "{"; str sep; for (const auto& kv : m) os << sep << kv.ff << ": " << kv.ss, sep = ", "; return os << "}"; }
struct pairHash{tpl_<class T1,class T2>size_t operator()(const pair<T1,T2>&p)const{return hash<T1>{}(p.first)^ (hash<T2>{}(p.second)<<1);}}; struct vectorHash{tpl_<class T>size_t operator()(const vector<T>&v)const{size_t hashboxesalue=0;for(const T&i:v)hashboxesalue^=hash<T>{}(i)+0x9e3779b9+(hashboxesalue<<6)+(hashboxesalue>>2);return hashboxesalue;}};
struct DSU{vi p,sz;explicit DSU(int n){p.resize(n),sz.resize(n,1),iota(all(p),0);}int par(int x){return x==p[x]?x:p[x]=par(p[x]);}void merge(int x,int y){x=par(x),y=par(y);if(x!=y){if(sz[x]<sz[y])swap(x,y);p[y]=x,sz[x]+=sz[y];}}};
const vector<pii> dirs={{1,0},{0,-1},{0,1},{-1,0}}; auto check=[](auto y,auto x,auto m,auto n){return y>=0&&y<m&&x>=0&&x<n;};
constexpr ll MOD=1000000007; constexpr int INF=1000000000; constexpr ll INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";
tpl_<tn_ T> T ceil(T num, T den) { return (num+den-1)/den;} tpl_<tn_ T> T mul(T a, T b, T mod=MOD) {return ((a%mod)*(b%mod))%mod;} tpl_<tn_ T>T add(T a, T b, T mod=MOD) {return (a+b) % mod;}

int t, k, n, m;

int main() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(k);
    for (int i = 0; i < k; i++) cin >> a[i];

    ll ans = 0;
    for (ll i = 1; i < (1 << k); i++) {
        ll prime_product = 1;
        for (ll j = 0; j < k; j++) {
            // check if we are using a[j] in this number
            if (i & (1 << j)) {
                // check to not overflow, if we do set prime_product to N+1 so
                // ans doesn't change
                if (prime_product > n / a[j]) {
                    prime_product = n + 1;
                    break;
                }
                prime_product *= a[j];
            }
        }

        //__builtin_popcount gives the number of 1's in binary representation,
        // which is also the number of primes we have multiplied
        if (__builtin_popcount(i) % 2) {
            ans += n / prime_product;
        } else {
            ans -= n / prime_product;
        }
    }

    cout << ans << endl;
}

// int main() {
//     ios::sync_with_stdio(false); cin.tie(nullptr);
//     cin>>n>>k;
//     vll primes(k);
//     f(i, k) cin>>primes[i];
//     ll res=0;
//     f(i, 1<<k) {
//         if(i==0) continue;
//         ll curr=1;
//         f(j, k) {
//             if((i>>j) & 1) {
//                 if(curr > n/primes[j]) {
//                     curr = n+1; break;
//                 }
//                 curr *= primes[j];
//             }
//         }
//         ll x = n / curr;
//         if(__builtin_popcount(i) % 2) {
//             res += x;
//         } else {
//             res -= x;
//         }
//     }
//     cout<<res<<en;
// }
