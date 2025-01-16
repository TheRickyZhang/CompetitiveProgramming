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

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);

    ll a,b,c,d; cin>>a>>b>>c>>d;
    ll n; cin>>n;
    string s; cin>>s;

    vector<ll> px(n), py(n);
    for(int i=0; i<n; i++){
        if(i>0){ px[i]=px[i-1]; py[i]=py[i-1]; }
        if(s[i]=='U') py[i]++;
        if(s[i]=='D') py[i]--;
        if(s[i]=='R') px[i]++;
        if(s[i]=='L') px[i]--;
    }

    auto check = [&](ll m){
        ll windX = m/n*px[n-1] + (m%n>0 ? px[m%n-1] : 0);
        ll windY = m/n*py[n-1] + (m%n>0 ? py[m%n-1] : 0);
        ll fx = a + windX, fy = b + windY;
        ll dist = llabs(c-fx) + llabs(d-fy);
        return dist <= m;
    };

    ll l=0, r=2e14;
    while(l<=r){
        ll m = (l+r)/2;
        if(check(m)) r=m-1;
        else l=m+1;
    }
    if(l>=2e14)cout<<-1<<en;
    else cout<<l<<en;
    return 0;
}

// int main() {
//     ios::sync_with_stdio(false); cin.tie(nullptr);
//     // ll t; cin>>t; f(i, n) solve();
//     ll a, b, c, d; cin>>a>>b>>c>>d;
//     ll dx=c-a, dy=d-b;
//
//     cin>>n;
//     string s; cin>>s;
//     map<char, ll> pos = {{'U', 0}, {'D', 1}, {'L', 2}, {'R', 3}};
//     vll lr(n, 0);
//     vll ud(n, 0);
//     f(i, n) {
//         if(i > 0) lr[i]=lr[i-1]; ud[i]=ud[i-1];
//         if(s[i]=='U') ud[i]--;
//         else if(s[i]=='D') ud[i]++;
//         else if(s[i]=='R') lr[i]--;
//         else if(s[i]=='L') lr[i]++;
//     }
//     auto check = [&](ll m) { // i is number of moves (index)
//         ll netlr = (m / n) * lr.back() + lr[m % n] + dx;
//         ll netud = (m / n) * ud.back() + ud[m % n] + dy;
//         cout<<"moves "<<m<<sp<<(abs(netlr) + abs(netud) <= m ? "pass" : "fail")<<en;
//         return abs(netlr) + abs(netud) <= m;
//     };
//     ll l=0, r=1e10;
//     while(l<r) {
//         ll m=l+(r-l)/2;
//         if(!check(m)) l=m+1;
//         else r=m;
//     }
//     cout<<l<<en;
// }
