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
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

#define int long long
tpl_<tn_ T>
using v = vector<T>;
using ll = long long;
using pii = pair<int,int>;
using vi = v<int>;
using vvi = v<vi>;
using vpii=v<pii>;
using vvpii=v<vpii>;
tpl_<class T> bool ckmn(T& a, const T& b) {return b < a ? a = b, 1 : 0;}  tpl_<class T> bool ckmx(T& a, const T& b) {return a < b ? a = b, 1 : 0;}
int MOD=1e9+7; constexpr int INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin>>n;
    // Prefix enjoyment for each node
    vi e(n, 0);
    // best[i][j] -> jth highest difficulty from i->0
    vvi best(n);

    vi par(n), diff(n);
    fe(i, n-1){
        cin>>par[i]>>diff[i]>>e[i]; par[i]--;
        e[i] += e[par[i]];

        // Grr inefficient but works for x <= 11
        vi curr = best[par[i]];
        curr.pb(diff[i]);
        sort(rall(curr));
        if(curr.size() > 11) curr.resize(11);
        best[i] = curr;
    }

    vvpii arr(11);
    f(i, n){
        rep(c, 0, 10){
            arr[c].pb({ best[i].size() > c ? best[i][c] : 0, e[i] });
        }
    }
    
    vvi pre(11);
    rep(c, 0, 10){
        sort(all(arr[c]), [](pii a, pii b){ return a.ff < b.ff; });
        pre[c].resize(arr[c].size());
        pre[c][0] = arr[c][0].ss;
        f(i, arr[c].size()-1){
            pre[c][i+1] = max(pre[c][i], arr[c][i+1].ss);
        }
    }

    int k; 
    cin>>k;
    f(i, k) {
        int s, c; cin>>s>>c;
        ckmn(c, 10LL);
        // Note we should onyl binary search on the sorted arr, not the prefixed pre
        // But retrieve answer from pre
        int idx = (upper_bound(all(arr[c]), make_pair(s, INFL)) - arr[c].begin()) - 1;
        int res = (idx >= 0 ? pre[c][idx] : 0);
        cout<<res<<en;
    }
    return 0;
}