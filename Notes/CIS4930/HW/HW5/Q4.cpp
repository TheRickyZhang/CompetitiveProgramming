#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>;
using vll = vector<long long>;
using ll = long long;
using pll = pair<ll, ll>;
using vpll = vector<pair<int, int>>;
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
constexpr ll MOD = 1000000007;
constexpr char en = '\n';
const vector<pll> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

// INSANE dp that requires tracking previous states
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll z;
    cin >> z;

    FOR(_, z) {
        int n;
        cin >> n;
        vi nums(n);
        FOR(i, n) cin >> nums[i];

        // Min max height after i steps
        vector<vi> dp(n+1, vi(1001, INF));
        dp[0][0] = 0;

        // parent = {prev h, char choice}, for reconstructing path
        vector<vector<pair<int, char>>> parent(n+1, vector<pair<int, char>>(1001, {-1, ' '}));
        int total = accumulate(nums.begin(), nums.end(), 0);

        FOR(i, n) {
            FOR(h, total+1) {
                if(dp[i][h] == INF) continue;

                // Climb up
                int nh = h+nums[i];
                if(nh <= total) {
                    int nmx = max(dp[i][h], nh);
                    if(nmx < dp[i+1][nh]) {
                        dp[i+1][nh] = nmx;
                        parent[i+1][nh] = {h, 'U'};
                    }
                }

                // Climb down
                nh = h-nums[i];
                if(nh >= 0) {
                    int nmx = max(dp[i][h], h); // Need t account if starting from top again
                    if(nmx < dp[i+1][nh]) {
                        dp[i+1][nh] = nmx;
                        parent[i+1][nh] = {h, 'D'};
                    }
                }
            }
        }
        int mn = INF;
        FOR(h, total+1) {
            if(dp[n][h] < mn) mn = dp[n][h];
        }

        if(mn == INF) {
            cout << "IMPOSSIBLE" << en;
        } else {
            string res;

            int h = 0;
            for(int i = n; i >= 0; --i) {
                auto& [prev, c] = parent[i][h];
                if(prev == -1) break;
                res += c;
                h = prev;
            }
            reverse(all(res));
            if(res.empty()) {  // Not sure why this happend but ok
                cout << "IMPOSSIBLE" << en;
            } else {
                cout << res << en;
            }
        }
    }
    return 0;
}
