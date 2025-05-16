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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k;
    cin >> n >> k;
    vll c(n);
    FOR(i, n) cin >> c[i];

    rep(i, 1, n) c[i] = min(c[i], 2*c[i-1]);

    ll res = LLONG_MAX;
    ll cost = 0;

    for(int i = n-1; i >= 0; --i) {
        ll vol = 1<<i;
        ll maxTake = k / vol;
        cost += maxTake*c[i];
        k -= maxTake * vol;
        res = min(res, cost + (k>0 ? c[i] : 0));
    }
    cout << res << en;
    return 0;
}
