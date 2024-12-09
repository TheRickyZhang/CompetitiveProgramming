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

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vll initialVals(n, 0);
    vector<vll> operations(m, vll(3, 0));
    vll operationsDiff(m, 0);

    FOR(i, n) cin >> initialVals[i];

    // Convert to 0-indexed
    FOR(i, m) {
        cin >> operations[i][0] >> operations[i][1] >> operations[i][2];
        operations[i][0]--;
        operations[i][1]--;
    }

    // Populate operations diff
    FOR(i, k) {
        int startOp, endOp;
        cin >> startOp >> endOp;
        startOp--, endOp--;
        operationsDiff[startOp]++;
        if (endOp + 1 < m) operationsDiff[endOp + 1]--;
    }

    // Accumulate total ops from diff and form num diff
    vll changesDiff(n, 0);
    ll cumulativeOps = 0;
    FOR(i, m) {
        cumulativeOps += operationsDiff[i];
        ll l = operations[i][0];
        ll r = operations[i][1];
        ll opDelta = operations[i][2];

        changesDiff[l] += cumulativeOps * opDelta;
        if (r + 1 < n) changesDiff[r + 1] -= cumulativeOps * opDelta;
    }

    // Accumulate total from num diff
    ll delta = 0;
    FOR(i, n) {
        delta += changesDiff[i];
        initialVals[i] += delta;
        if(i!=0) cout << " ";
        cout << initialVals[i];
    }
    cout << en;
    return 0;
}