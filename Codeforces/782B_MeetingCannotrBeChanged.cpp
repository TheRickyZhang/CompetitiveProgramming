#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<double> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    auto calc = [&](double x) {
        double res = 0;
        for (int i = 0; i < n; i++) {
            res = max(res, fabs(x - a[i]) / b[i]);
        }
        return res;
    };

    double l = 0, r = *max_element(a.begin(), a.end());
    for (int iter = 0; iter < 100; iter++) {
        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;
        double f1 = calc(m1), f2 = calc(m2);
        if (f1 < f2)
            r = m2;
        else
            l = m1;
    }
    cout << fixed << setprecision(9) << calc(l) << "\n";
    return 0;
}
