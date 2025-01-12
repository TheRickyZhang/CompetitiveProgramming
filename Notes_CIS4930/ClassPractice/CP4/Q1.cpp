#include <bits/stdc++.h>
using namespace std;

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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vi nums(n);
    vi dpf(n, 1);
    vi dpb(n, 1);
    FOR(i, n) cin >> nums[i];
    int res = 0;
    for (int i = n-1; i >= 0; i--) {
        dpf[i] = dpb[i] = 1;
        for (int j = n-1; j > i; j--) {
            if (nums[i] > nums[j])
                dpf[i] = max(dpf[i], dpf[j] + 1);
            else
                dpb[i] = max(dpb[i], dpb[j] + 1);
        }
        res = max(res, dpf[i] + dpb[i] - 1);
    }
    cout << res << en;
    return 0;
}