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
    f(i, n-1) {
        int u, v; cin>>u>>v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }
    double res = 0;
    function<void(int, int, int, double)> dfs = [&](int u, int p, int d, double prob) {
        // cout<<"checking "<<u<<sp<<prob<<en;
        if(adj[u].size()==1) {
            // cout<<"HERE"<<en;
            // cout<<d<<sp<<prob<<en;
            res += d * prob;
            return;
        }
        for(int v : adj[u]) {
            if(v==p) continue;
            dfs(v, u, d+1, prob/static_cast<double>(adj[u].size()-1));
        }
    };
    for(int v : adj[0]) {
        dfs(v, 0, 1, 1.0/adj[0].size());
    }
    cout<<fixed<<setprecision(15)<<res<<en;
}
