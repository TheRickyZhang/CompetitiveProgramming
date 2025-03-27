#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll NEG_INF = -1e18; // a very small number

// Given n, k, and dp_next vector from minute i+1,
// compute dp[i] for r = 0 ... R, where R = k * floor((n - i)/(k+1)).
vector<ll> compute_dp(int i, int n, int k, const vector<ll> &dp_next) {
    // Compute maximum balance allowed at minute i.
    int max_r = ( (n - i) / (k + 1) ) * k; // floor division * k
    vector<ll> dp_cur(max_r + 1, NEG_INF);

    // dp_next corresponds to minute i+1.
    // Its size is max_r_next + 1, where max_r_next = floor((n - i - 1)/(k+1))*k.
    int size_next = dp_next.size();

    // For each balance r (0 <= r <= max_r) at minute i, we have two options:
    //   - do nothing / eat: if r==0 then option is dp_next[0], else for r>0 we use dp_next[r-1].
    //   - take plate: adds d[i] and increases balance by k, i.e. requires dp_next[r+k] (if available).
    // The recurrence (using monotonicity) becomes:
    //   if r == 0: dp[i][0] = max( dp[i+1][0], d[i] + dp[i+1][k] )
    //   else: dp[i][r] = max( dp[i+1][r-1], d[i] + ( (r+k < size_next) ? dp[i+1][r+k] : NEG_INF) ).
    // We'll fill dp_cur for each r.
    // (Note: d[i] will be added in main loop; here we only compute the dp transition using dp_next.)

    // We'll fill dp_cur for each r later in the main loop; this is a helper to compute one row.
    // (The code below will be inserted inside the main loop.)

    return dp_cur; // placeholder
}

// Main – we combine the DP computation in a loop from i = n down to 0.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<ll> d(n);
        for (int i = 0; i < n; i++){
            cin >> d[i];
        }

        // dp[i] will be stored in a vector; dp[n] is the base: only dp[n][0] = 0.
        vector< vector<ll> > dp(n+1);
        dp[n] = vector<ll>(1, 0); // at minute n, only balance 0 is feasible

        // Process minutes backwards: i = n-1 down to 0.
        for (int i = n - 1; i >= 0; i--){
            // Maximum balance allowed at minute i.
            int max_r = ((n - i) / (k + 1)) * k;
            int sz = max_r + 1;
            vector<ll> cur(sz, NEG_INF);

            // dp_next is dp[i+1] (which has size = nextSz)
            const vector<ll> &next = dp[i+1];
            int nextSz = next.size();

            for (int r = 0; r < sz; r++){
                ll optEatOrDo = NEG_INF, optTake = NEG_INF;
                // Option 1: eat/do nothing.
                if(r == 0) {
                    // when r==0, only option is dp[i+1][0] (if exists)
                    if(0 < nextSz)
                        optEatOrDo = next[0];
                } else {
                    // for r > 0, using monotonicity dp[i+1][r-1] is best among eat/do nothing
                    if(r - 1 < nextSz)
                        optEatOrDo = next[r - 1];
                }

                // Option 2: take the plate at minute i.
                // This adds d[i] and increases balance by k.
                if(r + k < nextSz)
                    optTake = d[i] + next[r + k];

                cur[r] = max(optEatOrDo, optTake);
            }
            dp[i] = move(cur);
        }

        // The answer is dp[0][0]
        cout << dp[0][0] << "\n";
    }
    return 0;
}
