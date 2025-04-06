#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
typedef tuple<ll,ll,ll> ti;

#define fs first
#define sd second

#ifdef DEBUG
#define D(x...) printf(x);
#else
#define D(x...)
#endif

const int MAXN = 405;
const int INF = 1<<30;

int N, K, ed[MAXN][MAXN], pos[MAXN][MAXN];
set<int> dp[MAXN][MAXN];
vector<int> adj[MAXN];

void dfs(int n, int p = 1){
    // Mark sizes of 0 and 1 rooted at n as possible
    pos[n][0] = 1;
    pos[n][1] = 1;

    // Add edge to parents
    if(n != 1) dp[n][1].insert(ed[n][p]);

    for(int e : adj[n]){
        if(e == p) continue;

        // Solve problem for children first (so dp values are filled before we need them in this node)
        dfs(e, n);

        // For each possible size of the state rooted at node n
        for(int sz = K; sz >= 1; sz--){

            // If this size is possible at n, let the default state be ignoring e
            // THIS is the critical step I missed in my implementation!
            if(pos[n][sz]) dp[n][sz].insert(ed[n][e]);

            // Try build it using j from current child e
            for(int j = 1; j < sz; j++){
                // If either contribution is not possible, skip
                if(!pos[e][j] || !pos[n][sz-j]) continue;

                // If this sz is already possible at n and we can't improve it, skip
                if(pos[n][sz] && dp[n][sz].size() <= dp[n][sz-j].size() + dp[e][j].size() - 1) continue;

                // Either this size is not possible at n (yet) or it can be improved - combine the two contributing states...
                // Reset the set, add edge to parent if current node is not root
                dp[n][sz] = set<int>();
                if(n != 1) dp[n][sz].insert(ed[n][p]);

                for(int i : dp[e][j]) dp[n][sz].insert(i);
                for(int i : dp[n][sz-j]) dp[n][sz].insert(i);
                dp[n][sz].erase(ed[e][n]);
                pos[n][sz] = 1;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for(int i = 0; i < N-1; i++){
        int ai, bi;
        cin >> ai >> bi;
        adj[ai].push_back(bi);
        adj[bi].push_back(ai);
        ed[ai][bi] = ed[bi][ai] = i+1;
    }

    dfs(1);

    int ans = INF, best = 0;
    for(int i = 1; i <= N; i++){
        if(!pos[i][K]) continue;
        if(dp[i][K].size() < ans){
            ans = dp[i][K].size();
            best = i;
        }
    }

    cout << (ans == INF ? 0 : ans)  << "\n";
    for(int i : dp[best][K]){
        cout << i << " ";
    }
    cout << "\n";
}