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

int n;
double l, w;

struct sprinkler {
    double x, dx;
    sprinkler(double x, double r) {
        this->x = x;
        this->dx = sqrt(r * r - w * w / 4.0);  // Horizontal dr
    }
    bool operator< (const sprinkler &a) const {
        return (x - dx) < (a.x - a.dx);
    }
};

// WHY does infinite loop when not do this :(
void run() {
    vector<sprinkler> v;
    double x, r;
    FOR(i, n) {
        cin >> x >> r;
        if (r*2 >= w) {
            v.pb(sprinkler(x, r));
        }
    }
    int sz = v.size();
    sort(all(v));
    double lim = 0;
    int idx=0, res=0;
    while (idx < sz) {
        double nlim = lim;
        while (idx < sz && (v[idx].x - v[idx].dx) <= lim) {
            nlim = max(nlim, v[idx].x + v[idx].dx);
            idx++;
        }
        if (nlim == lim) {
            cout << -1 << en;
            return;
        }
        lim = nlim;
        res++;
        if (lim >= l) {
            cout << res << en;
            return;
        }
    }
    cout << -1 << en;
}

int main() {
    while (cin>>n>>l>>w) {
        run();
    }
    return 0;
}