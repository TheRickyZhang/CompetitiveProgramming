#include <bits/stdc++.h>
using namespace std;
#define int int32_t
#define vi vector<int>
#define v4d vector<vector<vector<vector<int>>>>
#define f(i, n) for (int i = 0; i < (n); i++)
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define ckmx(a, b) a = max(a, b)
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");

int n;
vi a;
v4d dp;

int solve(int i, int j, int k, int m) {
    if (k > m) return -(1 << 29);
    if (i > j) return 0;
    int& res = dp[i][j][k][m];
    if (res != -1) return res;

    if (i == j) return res = (a[i] >= k && a[i] <= m ? 1 : 0);
    res = 0;

    // Case 1: swap i and j
    ckmx(res, solve(i + 1, j - 1, k, m));
    if (a[j] >= k) ckmx(res, solve(i + 1, j - 1, a[j], m) + 1);
    if (a[i] <= m) ckmx(res, solve(i + 1, j - 1, k, a[i]) + 1);
    if (k <= a[j] && a[j] <= a[i] && a[i] <= m) ckmx(res, solve(i + 1, j - 1, a[j], a[i]) + 2);

    // Case 2: move i forward
    ckmx(res, solve(i + 1, j, k, m));
    if (a[i] >= k) ckmx(res, solve(i + 1, j, a[i], m) + 1);

    // Case 3: move j backward
    ckmx(res, solve(i, j - 1, k, m));
    if (a[j] <= m) ckmx(res, solve(i, j - 1, k, a[j]) + 1);

    return res;
}

int32_t main() {
    setIO("subrev");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.resize(n);
    f(i, n) cin >> a[i];
    dp = v4d(n, vector<vector<vector<int>>>(n, vector<vector<int>>(51, vector<int>(51, -1))));
    cout << solve(0, n - 1, 0, 50) << "\n";
    return 0;
}
