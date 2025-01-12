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
constexpr int INF = 100000000;
constexpr int MOD = 100000007;
constexpr char en = '\n';
const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k;
    cin >> n >> k;

    vll dp(n+1, 0);
    dp[1] = 1;
    dp[2] = 1;
    rep(i, 3, n+1) {
        dp[i] = dp[i-1] + dp[i-2];
        if (dp[i] > k) dp[i] = k; //Only need up to k
    }

    while (n > 2) {
        if (k <= dp[n-2]){
            n-=2;
        } else{
            k-=dp[n-2];
            n-=1;
        }
    }

    if (n == 1) {
        cout << "N" << en;
    } else {
        cout << "A" << en;
    }
    return 0;
}