#include <bits/stdc++.h>
using namespace std;

#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define repr(i, a, b) for (int i = (a); i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define all(x) begin(x), end(x)
#define vvi vector<vector<int>>
#define vpii vector<pair<int, int>>

#define int long long
#define str string
int N = 10000; int MOD=1e9+7; constexpr int INF=1e9; constexpr int INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";


int t, k, n, m;
void solve() {

}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    vvi adj(n);
    vpii points(n);
    f(i, n) {
        int u, v; cin>>u>>v; u--; v--;
        points[i] = {u, v};
    }
    f(i, n) {
        f(j, i) {
            if(points[i].ff == points[j].ff || points[i].ss == points[j].ss) {
                adj[i].pb(j); adj[j].pb(i);
            }
        }
    }
    int cnt = 0;
    vector<bool> vis(n, false);
    function<void(int)> dfs = [&](int u) {
        if(vis[u]) return;
        vis[u] = true;
        for(int v : adj[u]) {
            dfs(v);
        }
    };
    f(i, n) {
        if(!vis[i]) {
            cnt++;
            dfs(i);
        }
    }
    cout<<cnt-1<<en;
}
