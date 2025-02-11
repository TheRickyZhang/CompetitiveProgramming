#include <bits/stdc++.h>
using namespace std;
#define vi vector<long long>
int MOD = 998244353;
void solve() {
    int n; cin >> n;
    vi a(n+1, 0); for (int i = 1; i <= n; i++) cin >> a[i];
    vi dp(n+1, 0);

    dp[0] = 1;
    if (n >= 1) dp[1] = (a[1] == 0);
    if (n >= 2) dp[2] = (a[2] == a[1]) * dp[1] + (a[2] == 1) * dp[0];

    for (int i = 3; i <= n; i++)
        dp[i] = ((a[i] == a[i-1]) * dp[i-1] + (a[i] == a[i-2] + 1) * dp[i-2]) % MOD;

    cout << (dp[n] + dp[n-1]) % MOD << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
}
