#include <bits/stdc++.h>
using namespace std;

#define f(i, n) for (int i = 0; i < (n); i++)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define fe(i, n) for (int i = 1; i <= (n); i++)
#define all(x) (x).begin(), (x).end()
#define en "\n"

using ll = long long;
using vi = vector<int>;

const int MOD = 1e9 + 7;
const int MX_HUNGER = 1000;

int n;

ll ways_offset(int shift, const vi &h, vector<ll> &dp, vector<ll> &diff) {
    // Initially, one way to set the first element (i.e. no operations yet)
    rep(i, 0, MX_HUNGER + 1) dp[i] = 1;

    // Process cows 2..n
    rep(i, 1, n) {
        int limPrev = h[i - 1] - shift; // allowed maximum for previous difference
        int limCur = h[i] - shift;      // available for current cow
        int j = 0;
        while(j <= limPrev && (limCur - j + 1) >= 0) {
            int rb = (h[i] - shift) - j + 1;  // right boundary for diff update
            diff[0] = (diff[0] + dp[j]) % MOD;
            diff[rb] = (((diff[rb] - dp[j]) % MOD) + MOD) % MOD;
            j++;
        }
        dp[0] = diff[0] % MOD;
        rep(j, 1, MX_HUNGER + 1) {
            dp[j] = dp[j - 1] + diff[j];
            dp[j] %= MOD;
        }
        rep(j, 0, MX_HUNGER + 1) diff[j] = 0;
    }

    return dp[0] % MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vi h(n);
    int mn = MX_HUNGER;
    f(i, n) {
        cin >> h[i];
        mn = min(mn, h[i]);
    }

    ll ans = 0;
    vector<ll> dp(MX_HUNGER + 1, 0), diff(MX_HUNGER + 2, 0);

    if(n % 2 == 1) {
        // For odd n, sum over all possible final hunger levels (shift)
        rep(shift, 0, mn + 1)
            ans = (ans + ways_offset(shift, h, dp, diff)) % MOD;
    } else {
        ans = ways_offset(0, h, dp, diff) % MOD;
    }

    cout << ans << en;
    return 0;
}
