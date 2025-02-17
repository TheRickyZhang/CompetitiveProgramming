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
constexpr int MOD = 1000000007;
constexpr char en = '\n';
const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

constexpr ll N = 2e5+1;
vll nums(N, 0);

int main() {
    ios::sync_with_stdio();
    cin.tie(NULL);

    ll t; cin >> t;
    ll n;
    while(t--) {
        deque<pll> s; // {val, freq}
        cin >> n;
        FOR(i, n) {
            cin >> nums[i];
        }

        FOR(i, n) {
            ll sum = nums[i];
            ll count = 1;
            while(!s.empty() && s.back().first >= sum / count) {
                auto [val, freq] = s.back();
                s.pop_back();
                sum += val*freq;
                count += freq;
            }
            // Break the sum up into its most equal pieces
            s.emplace_back(sum / count, count - sum%count);
            if(sum % count != 0) s.emplace_back(sum/count + 1, sum%count); // Always push the larger one last
        }
        cout << s.back().first - s.front().first << en;
    }
    return 0;
}