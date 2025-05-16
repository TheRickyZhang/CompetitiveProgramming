#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>;
using vll = vector<long long>;
using ll = long long;
using pii = pair<int, int>;
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
const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

using pll = pair<long long, long long>;

int main() {
    int n, coworkers;
    cin >> n >> coworkers;

    auto nextSort = [&](pll a, pll b) {
        return a.first + a.second > b.first + b.second;
    };
    priority_queue<pll, vector<pll>, function<bool(pll, pll)>> pq(nextSort);

    long long start, add;
    FOR(i, coworkers) {
        cin >> start >> add;
        pq.emplace(start, add);
    }

    FOR(i, n) {
        auto [val, add] = pq.top();
        pq.pop();
        pq.emplace(val + add, add);
    }

    long long mx = LLONG_MIN;
    while (!pq.empty()) {
        auto [val, add] = pq.top();
        mx = max(mx, val);
        pq.pop();
    }

    cout << mx << endl;
    return 0;
}
