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
#define print(x) (cout<<#x<<"="<<(x)<<endl)
#define quit(s) do{ cout<<(s)<<en; return; }while(false)

#define int long long
tpl_<tn_ T> using v = vector<T>; using vi = v<int>; tpl_<tn_ T> using vv = v<v<T>>;
using ll=long long; using pii=pair<int,int>;
using vb=v<bool>; using vvb=v<vb>; using vs=v<string>; using iii=array<int, 3>; using i4=array<int, 4>;
using vvi=v<vi>; using vll=v<ll>; using vpii=v<pii>; using vvpii=v<vpii>;
tpl_<tn_ K,tn_ T>using ump=unordered_map<K,T>; tpl_<tn_ T>using ust=unordered_set<T>; tpl_<tn_ T>using mset=multiset<T>;
tpl_<tn_ T> using pq=priority_queue<T>; tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;
tpl_<tn_ It, tn_ T> auto leq_bound(It l,It r,T x){auto it=upper_bound(l,r,x); return it!=l ? prev(it):r;}
tpl_<tn_ It, tn_ T> auto less_bound(It l,It r,T x){auto it=lower_bound(l,r,x);return it!=l ? prev(it):r;}
tpl_<tn_ T, tn_ U> T fstTrue(T l, T r, U ff) { for(++r; l<r;) { T m=l+(r-l)/2; if(ff(m)) r=m; else l=m+1; } return l;}
tpl_<tn_ T, tn_ U> T lstTrue(T l, T r, U ff) { for(++r; l<r;) { T m=l+(r-l)/2; if(ff(m)) l=m+1; else r=m; } return l-1;}
tpl_<tn_ T> bool cmn(T& a, T b) {return b<a ? a=b,1 : 0;} tpl_<tn_ T> bool cmx(T& a, T b) {return a<b ? a=b,1 : 0;}
cx_ auto en="\n"; cx_ auto sp=" "; using str=string; typedef fn<void(int,int)>fvii; typedef fn<void(int,int,int)>fviii;

void setIO(const str&name=""){ios_base::sync_with_stdio(false);cin.tie(nullptr); if(!name.empty())
    {freopen((name+".in").c_str(),"r",stdin);freopen((name+".out").c_str(),"w",stdout);}}

cx_ int INF=1e9; cx_ int INFL=0x3f3f3f3f3f3f3f3f; cx_ int B=31;

void read(vi &v){for(auto&x:v)cin>>x;} void read(vpii&v){for(auto&[x,y]:v)cin>>x>>y;}

int k, n, m;
void solve() {
  cin >> n;
  vi a(n); read(a);
  int tot = 0;
  set<int> before, after;
  f(i, n) after.insert(a[i]);
  f(i, n) {
    tot += before.count_less(a[i]) * after.count_more(a[i]);
    after.erase(a[i]);
    before.insert(a[i]);
  };
  int delta = 0;
  f(i, n) {
    set<int> before, middle, after;
    f(ii, i) before.insert(a[ii]);
    rep(jj, i+1, n-1) after.insert(a[jj]);
    rep(j, i+1, n) {
      if(a[i] < a[j]) continue; // Optimization for 123 case
      int mn = a[j];
      int mx = a[i];
      int b = before.lower_bound(mn) - before.begin();
      int m = middle.lower_bound(mx) - middle.lower_bound(mn);
      int u = after.lower_bound(mx);
      cmx(delta, b + m + u);
      after.erase(a[j]);
      middle.insert(a[j]);
    }
  }
  cout << tot + delta << en;
}

int32_t main() {
    setIO();
    solve();
}
