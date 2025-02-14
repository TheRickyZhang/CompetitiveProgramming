#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

const int lim = 1000001;

struct SegTree {
    struct info {
        int sum, mx;
    };
    int n;
    std::vector<info> t;
    SegTree(int n) : n(n), t(4 * n) {}
    void pull(int x) {
        t[x].sum = t[2 * x].sum + t[2 * x + 1].sum;
        // NOTE: This prefix on a difference array is going from right->left,
        // Which is unintuitive, but easiest to implement for given goal
        t[x].mx = max(t[2 * x + 1].mx, t[2 * x + 1].sum + t[2 * x].mx);
    }
    void modify(int x, int l, int r, int p, int v) {
        if (l == r) {
            t[x].sum += v;
            t[x].mx = t[x].sum;
            return;
        }
        int m = (l + r) / 2;
        if (p <= m) modify(2 * x, l, m, p, v);
        else modify(2 * x + 1, m + 1, r, p, v);
        pull(x);
    }
    int query(int x, int l, int r, int suf) {
        if (t[x].mx <= 0) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = (l + r) / 2;
        if (t[2 * x + 1].mx + suf > 0) {
            return query(2 * x + 1, m + 1, r, suf);
        } else {
            return query(2 * x, l, m, suf + t[2 * x + 1].sum);
        }
    }
    void modify(int p, int v) {
        modify(1, 0, n - 1, p, v);
    }
    int query() {
        return query(1, 0, n - 1, 0);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SegTree t(lim);
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        t.modify(a[i], 1);
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        t.modify(b[i], -1);
    }

    int q;
    cin >> q;
    while (q--) {
        int tt, i, x;
        cin >> tt >> i >> x;
        --i;
        if (tt == 1) {
            t.modify(a[i], -1);
            t.modify(a[i] = x, 1);
        } else {
            t.modify(b[i], 1);
            t.modify(b[i] = x, -1);
        }
        cout << t.query() << '\n';
    }
}