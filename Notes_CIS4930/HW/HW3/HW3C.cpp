#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>;
using vll = vector<long long>;
using ll = long long;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;
    vpll nums(n);
    FOR(i, n) {
        cin >> nums[i].first >> nums[i].second;
    }

    sort(all(nums));
    // Max quality
    ll mx = nums[0].second;
    bool happy = false;
    rep(i, 1, n) {
        if (nums[i].second < mx) {
            happy = true;
            break;
        }
        mx = max(mx, nums[i].second);
    }

    if (happy) {
        cout << "Happy Alex" << en;
    } else {
        cout << "Poor Alex" << en;
    }

    return 0;
}