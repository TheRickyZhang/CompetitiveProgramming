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
    ll t; cin >> t;
    FOR(_, t) {
        ll n, k;
        cin >> n >> k;
        vll nums(n);
        ump<int, int> freqs;
        FOR(i, n) {
            cin >> nums[i];
        }
        ll mx = nums[0];
        FOR(i, n) {
            freqs[nums[i]]++;
            if(nums[i] > mx) mx = nums[i];
        }
        int uniqueCount = 0;
        int diff = 0;
        for(auto [num, freq] : freqs) {
            uniqueCount++;
            diff += mx-freq;
        }
        if(mx == 0) {
            cerr << "huh" << en;
            continue;
        }
        ll maxPossible;
        if(k > diff) {
            maxPossible = mx + (k-diff +n+k-1) / mx;
        } else {
            maxPossible = (n+k + mx-1) / mx; // Floor of (n+k)/mx
        }
        cout << maxPossible << en;
    }
    return 0;
}