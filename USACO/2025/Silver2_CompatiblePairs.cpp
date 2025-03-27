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
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");

#define int long long
tpl_<tn_ T>
using v = vector<T>;
using ll=long long;
using pii=pair<int,int>;
using vi=v<int>;
using vvi=v<vi>;
int N = 100000;
int MOD=1e9+7;
constexpr int INFL=0x3f3f3f3f3f3f3f3f;
constexpr auto en = "\n"; constexpr auto sp = " ";

int t, k, n, m;
void solve() {

}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    // a, b pair sums must form acyclic graph
    int a, b; cin>>n>>a>>b;
    vvi adj(n); vi cnt(n);
    vi id(n); map<int, int> mp;

    // {id, weight}
    v<pii> nums(n);
    f(i, n) cin>>nums[i].ss>>nums[i].ff;
    sort(all(nums));
    f(i, n) {
        id[i] = nums[i].ff; mp[nums[i].ff] = i;
        cnt[i] = nums[i].ss;
    }
    // cout<<id<<en;
    // cout<<cnt<<en;
    // cout<<mp<<en;
    f(i, n) {
        if(cnt[i] == 0) continue;
        if(a-id[i] != id[i] && mp.count(a-id[i])) {
            adj[i].pb(mp[a-id[i]]);
        }
        if(b-id[i] != id[i] && mp.count(b-id[i])) {
            adj[i].pb(mp[b-id[i]]);
        }
    }
    v<bool> vis(n);
    int res = 0;
    function<void(int, int)> dfs = [&](int u, int p) {
        if(vis[u]) return; vis[u] = true;
        for(int v : adj[u]) {
            if(v==p) continue;
            dfs(v, u);
            int mn = min(cnt[u], cnt[v]);
            res += mn;
            cnt[u] -= mn, cnt[v] -= mn;
        }
    };
    f(i, n) {
        if(!vis[i]) dfs(i, -1);
    }
    if(a % 2 == 0 && mp.count(a/2)) res += cnt[mp[a/2]] / 2;
    if(b != a && b % 2 == 0 && mp.count(b/2)) res += cnt[mp[b/2]] / 2;
    cout<<res<<en;
}
