// Model bit operations independently - unique problem just involving cases
// NOTE: For efficiency, ensure that calculation of i is cumulative through <<=1 instead of (1<<i)

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
#define ust unordered_set
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
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    FOR(_, t) {
        ll b, c, d;
        cin >> b >> c >> d;
        ll mx = max({b, c, d});
        ll res = 0;
        bool isValid = true;
        for(ll i = 1; i <= mx; i<<=1) {
            ll x = b & i;
            ll y = c & i;
            ll z = d & i;
            ll tot = 4*(x>0) + 2*(y>0) + (z>0);
            if(tot == 1 || tot == 6) {
                res += i;
            } else if(tot == 4 || tot == 3) {
                isValid = false;
                break;
            }
        }
        if(isValid) cout << res << en;
        else cout << -1 << en;
    }
    return 0;
}