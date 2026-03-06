
#include <bits/stdc++.h>
using namespace std;
#define f(i, n) for(int i = 0; i < (n); ++i)
#define int long long
using vi = vector<int>;

// ============================================================
// EASY VERSION: O(n)
//
// Greedy: process values max-to-min. At each level v, remove
// elements with value v that are adjacent (in the linked list)
// to an element with value v-1. When an element is removed,
// its same-value neighbors may become newly adjacent to v-1,
// so re-enqueue them. Each element is processed O(1) times.
// ============================================================
int solve_easy(vi& a) {
    int n = a.size();
    if(!n) return 0;

    vi prv(n), nxt(n);
    vector<bool> alive(n, true);
    f(i, n) { prv[i] = i-1; nxt[i] = i+1; }

    // coordinate compress for bucket iteration
    vi sorted_vals(a);
    sort(sorted_vals.begin(), sorted_vals.end());
    sorted_vals.erase(unique(sorted_vals.begin(), sorted_vals.end()), sorted_vals.end());
    int nv = sorted_vals.size();

    vector<vi> bv(nv);
    vi cv(n);
    f(i, n) {
        cv[i] = lower_bound(sorted_vals.begin(), sorted_vals.end(), a[i])
                - sorted_vals.begin();
        bv[cv[i]].push_back(i);
    }

    int removed = 0;
    for(int c = nv - 1; c >= 0; c--) {
        int v = sorted_vals[c];
        deque<int> q(bv[c].begin(), bv[c].end());
        while(!q.empty()) {
            int i = q.front(); q.pop_front();
            if(!alive[i]) continue;
            int li = prv[i], ri = nxt[i];
            bool can = false;
            if(li >= 0 && alive[li] && a[li] == v-1) can = true;
            if(ri < n && alive[ri] && a[ri] == v-1) can = true;
            if(can) {
                alive[i] = false; removed++;
                if(li >= 0) nxt[li] = ri;
                if(ri < n) prv[ri] = li;
                if(li >= 0 && alive[li] && a[li] == v) q.push_back(li);
                if(ri < n && alive[ri] && a[ri] == v) q.push_back(ri);
            }
        }
    }
    return n - removed;
}

// ============================================================
// HARD VERSION: O(n^2) — sum of answers over all subarrays.
//
// For fixed l, run the greedy on a[l..n-1]. For each removed
// element at local position i, compute rd[i]: the minimum
// local index r such that i is removed in [l..l+r].
//
// Key insight: when i is removed by parent j at level a[l+i],
// all original-array elements strictly between i and j must
// have been removed at higher levels first. So:
//
//   rd[i] = max(i, j, max rd of removed elements between i & j)
//
// We maintain edge_rd[i] = max rd of all removed elements
// between linked-list neighbors i and nxt[i], updated as
// edges merge during removals.
//
// Contribution of element i (local) to the all-subarrays sum:
//   - If i survives:  len - i     (survives in [l..r] for all r >= l+i)
//   - If i is removed: rd[i] - i  (survives in [l..r] for r = l+i..l+rd[i]-1)
// Unified: total += rd[i] - i  (where rd[i] = len for survivors)
// ============================================================
int solve_hard(vi& a) {
    int n = a.size();
    if(!n) return 0;

    // Coordinate compress
    vi sorted_vals(a);
    sort(sorted_vals.begin(), sorted_vals.end());
    sorted_vals.erase(unique(sorted_vals.begin(), sorted_vals.end()), sorted_vals.end());
    int nv = sorted_vals.size();

    vi cv(n);
    vector<vi> bv(nv);
    f(i, n) {
        cv[i] = lower_bound(sorted_vals.begin(), sorted_vals.end(), a[i])
                - sorted_vals.begin();
        bv[cv[i]].push_back(i);
    }

    // ptr[c] = first index in bv[c] with position >= current l
    vi ptr(nv, 0);

    // Pre-allocate work arrays
    vi prv(n), nxt(n), edge_rd(n), rd(n);
    vector<bool> alive(n);

    int total = 0;
    for(int l = 0; l < n; l++) {
        int len = n - l;

        // Advance pointer for value at position l-1
        if(l > 0) {
            int c = cv[l - 1];
            if(ptr[c] < (int)bv[c].size() && bv[c][ptr[c]] == l - 1)
                ptr[c]++;
        }

        // Initialize linked list for [l..n-1]
        f(i, len) {
            prv[i] = i - 1;
            nxt[i] = i + 1;
            edge_rd[i] = -1;
            rd[i] = len;
            alive[i] = true;
        }

        // Process values max to min
        for(int c = nv - 1; c >= 0; c--) {
            int v = sorted_vals[c];
            // Enqueue positions with this value in [l, n-1]
            deque<int> q;
            for(int j = ptr[c]; j < (int)bv[c].size(); j++)
                q.push_back(bv[c][j] - l);

            while(!q.empty()) {
                int i = q.front(); q.pop_front();
                if(!alive[i]) continue;

                int li = prv[i], ri = nxt[i], par = -1;
                if(li >= 0 && alive[li] && a[l + li] == v - 1)
                    par = li;
                else if(ri < len && alive[ri] && a[l + ri] == v - 1)
                    par = ri;
                if(par < 0) continue;

                // Compute right_dep
                rd[i] = (par < i) ? max(i, edge_rd[par])
                                  : max(par, edge_rd[i]);

                alive[i] = false;

                // Merge linked-list edges
                if(li >= 0 && ri < len) {
                    edge_rd[li] = max({edge_rd[li], rd[i], edge_rd[i]});
                    nxt[li] = ri;
                    prv[ri] = li;
                } else if(li >= 0) {
                    edge_rd[li] = max(edge_rd[li], rd[i]);
                    nxt[li] = len;
                } else if(ri < len) {
                    prv[ri] = -1;
                }

                // Re-check same-value neighbors
                if(li >= 0 && alive[li] && a[l + li] == v)
                    q.push_back(li);
                if(ri < len && alive[ri] && a[l + ri] == v)
                    q.push_back(ri);
            }
        }

        f(i, len) total += rd[i] - i;
    }
    return total;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vi a(n);
    f(i, n) cin >> a[i];

    cout << solve_easy(a) << "\n";
    cout << solve_hard(a) << "\n";
}
