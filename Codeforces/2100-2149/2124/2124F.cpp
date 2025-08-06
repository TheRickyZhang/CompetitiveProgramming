#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--){
        int n, m;
        cin >> n >> m;

        // for each position j, bans[j] = all x such that a[j] != x
        vector<vector<int>> bans(n);
        for(int i = 0; i < m; i++){
            int pos, x;
            cin >> pos >> x;
            bans[pos-1].push_back(x);
        }

        vector<int> dp(n+1);
        dp[0] = 1;
        for(int i = 0; i < n; i++){
            for(int j = i; j >= 0; j--){
                int cnt = i - j + 1;
                vector<bool> vis(cnt, false);
                // mark forbidden rotations
                for(int t = 0; t < cnt; t++){
                    for(int x : bans[j + t]){
                        if (x >= 1 && x <= cnt){
                            int r = (x - 1 - t) % cnt;
                            if (r < 0) r += cnt;
                            vis[r] = true;
                        }
                    }
                }
                int free_shifts = cnt - count(vis.begin(), vis.end(), true);
                if (free_shifts > 0){
                    dp[i+1] = (dp[i+1] + dp[j] * free_shifts) % MOD;
                }
            }
        }

        cout << dp[n] << "\n";
    }
    return 0;
}
