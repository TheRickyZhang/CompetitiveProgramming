#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>;
using vll = vector<long long>;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pq = priority_queue<ll>;
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

#define mx 30001

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vi last(mx, -1); // last item used to reach sum
    vi costs(n);

    vi dp(mx, 0);
    dp[0] = 1;

    FOR(i, n) cin >> costs[i];
    FOR(i, n) {
        int c = costs[i];
        for(int j = c; j < mx; ++j) {
            if(dp[j - c] != 0) {
                dp[j] += dp[j - c];
                if(dp[j] >= 2) {
                    dp[j] = 2;
                    last[j] = -1;
                }
                else if(dp[j] == 1) {
                    last[j] = i;
                }
            }
        }
    }

    int m;
    cin >> m;
    vi orders(m);
    FOR(i, m) cin >> orders[i];

    FOR(i, m) {
        int query = orders[i];
        if(query >= mx || query < 0) cerr << "AHHHH" << en;
        if(dp[query] == 2) cout << "Ambiguous" << en;
        else if(dp[query] == 0) cout << "Impossible" << en;
        else {
            ostringstream oss;
            vi res;
            while(query > 0) {
                if(last[query] == -1) break;
                res.pb(last[query]+1);
                query -= costs[last[query]];
            }
            sort(all(res));
            for(int x : res) cout << x << " ";
            cout << en;
        }
    }

    return 0;
}
