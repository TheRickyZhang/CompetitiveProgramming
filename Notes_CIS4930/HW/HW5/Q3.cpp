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

vector<vi> dp;
vi nums;

int solve(int l, int r) {
    if(r < l) return 0;
    if(l == r) return 1;
    if(dp[l][r] != -1) return dp[l][r];

    if(r - l == 1) {
        if(nums[l] == nums[r]) return dp[l][r] = 1;
        return dp[l][r] = 2;
    }

    int res = INF;

    if(nums[l] == nums[r]) res = min(res, solve(l + 1, r - 1));
    for(int k = l; k < r; ++k) res = min(res, solve(l, k) + solve(k + 1, r));
    return dp[l][r] = res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    dp = vector(n, vi(n, -1));
    nums = vi(n);
    FOR(i, n) cin >> nums[i];
    int res = solve(0, n-1);
    cout << res << en;
    return 0;
}
