#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>;
using vll = vector<long long>;
using ll = long long;
using pii = pair<int, int>;
using pq = priority_queue<int>;
using mpq = priority_queue<int, vector<int>, greater<>>;
#define ump unordered_map
#define FOR(i, to) for (int i = 0; i < (to); ++i)
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define repr(i, a, b) for (int i = a-1; i >= b; --i)
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
constexpr int INF = 1000000000;
constexpr int MOD = 1000000007;
constexpr char en = '\n';
const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    while(cin>>n>>k) {
        if(n == 0 && k == 0) break;
        vector<vi> r(n, vi(2, 0));
        int tot = 0;
        FOR(i, n) {
            cin >> r[i][0] >> r[i][1];
            tot += r[i][0] + r[i][1];
        }

        // row, rooms closed, state (0->none, 1->left, 2->right)
        int dp[n][k+1][3];
        fill_n(&dp[0][0][0], n*(k+1)*3, INF);

        // Minimize amount subracted
        dp[0][0][0] = 0;
        dp[0][1][1] = r[0][0];
        dp[0][1][2] = r[0][1];

        rep(i, 1, n) {  // row
            FOR(j, k+1) {  // rooms
                FOR(s, 3) {  // PREVIOUS state
                    // Terminate impossible # rooms
                    if(dp[i-1][j][s] == INF) continue;

                    // Empty rows
                    dp[i][j][0] = min(dp[i][j][0], dp[i-1][j][s]);

                    // Left blocked - can only empty or left blocked
                    if(s != 2 && j < k) dp[i][j+1][1] = min(dp[i][j+1][1], dp[i-1][j][s] + r[i][0]);

                    // Right blocked - can only empty or right blocked
                    if(s != 1 && j < k) dp[i][j+1][2] = min(dp[i][j+1][2], dp[i-1][j][s] + r[i][1]);
                }
            }
        }

        int res = tot - min({dp[n-1][k][0], dp[n-1][k][1], dp[n-1][k][2]});
        cout << res << en;
    }

    return 0;
}