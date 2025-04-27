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

int t, k, n, m;
void solve() {
    cin>>n;
    vi a(n); f(i, n) cin>>a[i];
    vi b(n); f(i, n) cin>>b[i];
    int l = *min_element(all(a)), r = *max_element(all(a));
    auto cost = [&](int x) {
        int res = 0;
        f(i, n) {
            res += llabs(x - a[i]) * b[i];
        }
        return res;
    };
    while(r - l > 3) {
        int ml = l + (r-l)/3;
        int mr = r - (r-l)/3;
        if(cost(ml) > cost(mr)) {
            l = ml;
        } else {
            r = mr;
        }
    }
    int res = cost(l);
    rep(i, l+1, r) res = min(res, cost(i));
    cout<<res<<"\n";
}

int32_t main() {
    // setIO();
    int t; cin>>t; f(i, t) solve();
}
