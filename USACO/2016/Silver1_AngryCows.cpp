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
constexpr int MOD=1000000007; constexpr int INF=INT_MAX-5; constexpr ll INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";

int t, k, n, m;
void solve() {
    
}


int main() {
    setIO("angry");
    ios::sync_with_stdio(false); cin.tie(nullptr);
    // int t; cin>>t; f(i, n) solve();
    cin>>n>>k;
    vi nums(n);
    f(i, n) cin>>nums[i];
    sort(all(nums));
    auto good = [&](int x) {
        int cnt=0;
        auto it = nums.begin();
        while(it != nums.end()) {
            it = upper_bound(all(nums), *it+2*x);
            cnt++;
        }
        return cnt>k;
    };
    int l=0, r=1e9;
    while(l<r) {
        int m=l+(r-l)/2;
        if(good(m)) l=m+1;
        else r=m;
    }
    cout<<l<<en;
}
