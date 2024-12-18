#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

void query(int start, vector<int> &succ) {
    int slow = succ[start], fast = succ[succ[start]];
    while (slow != fast) {
        slow = succ[slow], fast = succ[succ[fast]];
    }
    slow = start;
    while (slow != fast) {
        slow = succ[slow], fast = succ[fast];
    }

    cout << slow << " ";

    return;
}

void solve() {
    int n;
    cin >> n;
    vector<int> v(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 1; i <= n; i++) {
        query(i, v);
    }
}

int main() {
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
