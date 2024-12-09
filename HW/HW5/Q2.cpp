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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int z;
    cin >> z;
    while(z--) {
        int n, p, k;
        cin >> n >> p >> k;
        string lvl;
        cin >> lvl;
        int x, y;
        cin >> x >> y;

        // prefix missing platforms
        vll dp(n + 2, 0); // 1-based indexing, buffer

        for(ll i = n; i >=1; --i){
            if(i + k > n) dp[i] = (lvl[i-1] == '0') ? 1 : 0;
            else dp[i] = dp[i + k] + ((lvl[i-1] == '0') ? 1 : 0);
        }

        ll res = INF;
        for(int s =0; s <= (n - p); ++s){
            ll cost = s*y + dp[s + p]*x;
            res = min(res, cost);
        }
        cout << res << en;
    }
    return 0;
}