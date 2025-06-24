#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
#define f(i, to) for (int i = 0; i < (to); ++i)

struct Oreo {
    long long a, b, c;
};

void solve() {
    int n;
    cin >> n;
    // Read in input
    vector<Oreo> oreos(n);
    for (int i = 0; i < n; i++) {
        cin >> oreos[i].a >> oreos[i].b >> oreos[i].c;
    }

    // Sort all oreos by smallest to largest. An exact ordering must exist due to the well formed condition
    sort(oreos.begin(), oreos.end(), [](const Oreo &x, const Oreo &y) {
        return x.a > y.a;
    });

    // Pre is the sum of all oreos to this point
    ll res = 0, pre = 0;
    f(i, n) {
        pre += oreos[i].b;
        res = max(res, pre + oreos[i].b); // So pre + oreos[i].b = 2*this oreo + sum(all other oreos)
    }
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
