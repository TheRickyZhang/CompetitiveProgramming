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
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vi s, e; // starts, end
    int l, r;

    int t; cin >> t;
    FOR(_, t) {
        int n, d, k;
        cin >> n >> d >> k;

        s.assign(n+1, 0);
        e.assign(n+1, 0);
        FOR(i, k) {
            cin >> l >> r;
            s[l]++;
            e[r]++;
        }
        FOR(i, n) {
            s[i+1] += s[i];
            e[i+1] += e[i];
        }

        int mx = INT_MIN;
        int mn = INT_MAX;
        int mxIdx = 0;
        int mnIdx = 0;

        for(int i = d; i <= n; ++i) {
            int curr = s[i] - e[i-d];
            if(curr > mx) {
                mx = curr;
                mxIdx = i-d+1;
            }
            if(curr < mn) {
                mn = curr;
                mnIdx = i-d+1;
            }
        }
        // Output the 1-indexed start days for max and min jobs
        cout << mxIdx << " " << mnIdx << en;
    }
    return 0;
}
