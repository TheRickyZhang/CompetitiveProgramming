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

#define int long long
tpl_<tn_ T>       using v = vector<T>; using ll=long long; using pii=pair<int,int>; using pll=pair<ll,ll>; using iii=array<int, 3>;  using i4=array<int, 4>;
tpl_<tn_ T>       using vv = v<v<T>>;  using vi=v<int>;    using vb=v<bool>; using vvb=v<vb>; using vs=v<string>;  using vvi=v<vi>; using vll=v<ll>;using vvll=v<vll>; using vpii=v<pii>; using vvpii=v<vpii>;
tpl_<tn_ K,tn_ T> using ump=unordered_map<K, T>;  tpl_<tn_ T>using ust=unordered_set<T>;  tpl_<tn_ K,tn_ T>    using rmap=map<K,T,greater<K>>; tpl_<tn_ T> using rset=set<T,greater<T>>; tpl_<tn_ T> using mset=multiset<T>; tpl_<tn_ T>using rmset=multiset<T,greater<T>>;
tpl_<tn_ T>       using pq=priority_queue<T>;     tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;      using str = string;
tpl_<class It, class T>     auto leq_bound  (It first, It last, T val) { auto it = upper_bound(first, last, val); return it != first ? prev(it) : last;} tpl_<class C, class T>auto leq_bound(C& c, T val) {auto it = c.upper_bound(val);return it != c.begin() ? prev(it) : c.end();}
tpl_<class It, class T>     auto less_bound (It first, It last, T val) {auto it = lower_bound(first, last, val);return it != first ? prev(it) : last; }tpl_<class C, class T>auto less_bound(C& c, T val) {auto it = c.lower_bound(val);return it != c.begin() ? prev(it) : c.end();}


int t, k, n, m;
void solve(){
    ll l, r;
    cin>>l>>r;
    vi ll, rr;
    if(l == 0) l = 1;
    while(l>0){ ll.push_back(l%10); l/=10; }
    while(r>0){ rr.push_back(r%10); r/=10; }
    f(i, rr.size() - ll.size()) ll.push_back(0);
    reverse(all(ll)); reverse(all(rr));
    int n = rr.size();
    int MAX_SUM = 9*n + 1;

    // dp[pos][sum][lb][rb] = # ways to build prefix of length pos (NOT the sum - that is index 1);
    int dp[20][200][2][2] = {};

    rep(d, ll[0], rr[0]){
        int lb = (d > ll[0]);
        int rb = (d < rr[0]);
        dp[0][d][lb][rb] = 1;
    }

    // build up to pos = n-1
    int dpp[20][200][2][2] = {};
    for(int pos = 1; pos < n; ++pos){
        memset(dpp, 0, sizeof dpp);
        f(sum, MAX_SUM) f(lb, 2) f(rb, 2){
            int ways = dp[pos-1][sum][lb][rb];
            if(!ways) continue;
            int l = lb? 0 : ll[pos];
            int r   = rb? 9 : rr[pos];
            rep(d, l, r){
                int nlb = lb || (d> l);
                int nrb = rb || (d< r);
                dpp[pos][sum + d][nlb][nrb] += ways;
            }
        }
        swap(dp, dpp);
    }

    int res = 0;
    f(sum, MAX_SUM) f(lb,2) f(rb,2){
        res += dp[n-1][sum][lb][rb] * sum;
    }
    cout<<res<<"\n";
}

int32_t main() {
    // setIO();
    int t; cin>>t; f(i, t) solve();
}
