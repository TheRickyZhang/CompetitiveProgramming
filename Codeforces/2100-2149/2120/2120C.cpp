#include <iostream>
#include <cstdint>
#include <cassert>
#include <vector>

using namespace std;

#define i64 int64_t

void solve() {
    i64 n, sum;
    cin >> n >> sum;

    if(sum < n || sum > n * (n + 1) / 2) {
        cout << "-1\n";
        return;
    }

    i64 k = sum - n;

    vector<i64> ans;
    i64 curr = 0, nsum = 0;

    for(i64 i = n - 1; i >= 0; --i) {
        if(curr == k) break;
        if(curr + i <= k) {
            curr += i;
            ans.push_back(i + 1);
            nsum += i + 1;
        }
    }

    i64 ct = ans.size();
    for(i64 i = 0; i < n - ct; ++i) ans.push_back(1);

    nsum += (n - ct);

    assert(nsum == sum);

    if(n == sum) {
        cout << "1\n";
        for(i64 i = 1; i < n; i++) cout << i << ' ' << i + 1 << '\n';
        return;
    }

    vector<bool> vis(n + 1, 1);
    cout << ans[0] << '\n';
    vis[ans[0]] = 0;

    for(i64 i = 1; i <= n; i++) {
        cout << ans[i - 1] << ' ' << ans[i] << '\n';
        vis[ans[i - 1]] = 0, vis[ans[i]] = 0;

        if(ans[i] == 1) {
            i64 prev = 1;
            for(i64 j = 2; j <= n; ++j) {
                if(vis[j]) {
                    cout << prev << ' ' << j << '\n';
                    prev = j;
                }
            }
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    i64 t;
    cin >> t;

    while(t--) solve();
    return 0;
}
