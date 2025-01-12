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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int h;
    int b;
    cin >> h;
    vi hd(h);
    FOR(i, h) cin >> hd[i];
    cin >> b;
    vi bn(b);
    FOR(i, b) cin >> bn[i];

#define mx 100001
    vi dph(mx, INF);
    vi dpb(mx, INF);
    dph[0] = dpb[0] = 0;
    for(auto x : hd) {
        for(int j = mx-1; j >= x; --j) {
            dph[j] = min(dph[j-x]+1, dph[j]);
        }
    }
    for(auto x : bn) {
        for(int j = mx-1; j >= x; --j) {
            dpb[j] = min(dpb[j-x]+1, dpb[j]);
        }
    }
    int res = INF;
    rep(i, 1, mx) {
        if(dph[i] != INF && dpb[i] != INF) {
            res = min(res, dph[i] + dpb[i]);
        }
    }
    if(res == INF) cout << "impossible";
    else cout << res;
    return 0;
}