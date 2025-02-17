// Key insight is first[0] <= first[1] ... <= first[n] -> valid
// Permanent queries -> recount four adj vals each time

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
constexpr int INF = 100000000;
constexpr int MOD = 100000007;
constexpr char en = '\n';
const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while(t--) {
        int n, m, q;
        cin >> n >> m >> q;
        vi a(n, 0), b(m, 0);
        FOR(i, n) cin >> a[i];
        FOR(j, m) cin >> b[j];

        // pos[x] will store the set of positions where x appears in b
        vector<set<int>> pos(n + 1, set<int>());
        vi ra(n + 1, 0); // ra[x] = position of x in a
        FOR(i, n) ra[a[i]] = i;
        vi first(n + 1, m); // first[x] = first occurrence of x in b, initialized to m
        ll nbConflicts = 0;

        // Populate 'first' and 'pos' based on initial 'b'
        FOR(j, m) {
            first[b[j]] = min(first[b[j]], j);
            pos[b[j]].insert(j);
        }

        // Check initial conflicts
        bool ans = (first[a[0]] == 0);
        FOR(i, n - 1) {
            if(first[a[i]] > first[a[i+1]]) {
                ans = false;
                nbConflicts++;
            }
        }

        cout << (ans ? "YA" : "TIDAK") << en;

        // Process each query
        FOR(k, q) {
            int s, u;
            cin >> s >> u;
            s--; // Convert to 0-based index

            // Remove local conflicts related to 'u' before the update
            if(ra[u] > 0 && first[a[ra[u]-1]] > first[u]) nbConflicts--;
            if(ra[u] < n-1 && first[u] > first[a[ra[u]+1]]) nbConflicts--;

            // Handle conflicts related to the old value at position 's'
            int old_val = b[s];
            if(ra[old_val] > 0 && first[a[ra[old_val]-1]] > first[old_val] && a[ra[old_val]-1] != u) nbConflicts--;
            if(ra[old_val] < n-1 && first[old_val] > first[a[ra[old_val]+1]] && a[ra[old_val]+1] != u) nbConflicts--;

            // Update 'pos' and 'first' for the old value
            pos[old_val].erase(s);
            if(!pos[old_val].empty()) first[old_val] = *pos[old_val].begin();
            else first[old_val] = m;

            // Update 'pos' and 'first' for the new value 'u'
            pos[u].insert(s);
            first[u] = min(first[u], s);

            // Recount local conflicts related to 'u' after the update
            if(ra[u] > 0 && first[a[ra[u]-1]] > first[u]) nbConflicts++;
            if(ra[u] < n-1 && first[u] > first[a[ra[u]+1]]) nbConflicts++;

            // Recount local conflicts related to the old value after the update
            if(ra[old_val] > 0 && first[a[ra[old_val]-1]] > first[old_val] && a[ra[old_val]-1] != u) nbConflicts++;
            if(ra[old_val] < n-1 && first[old_val] > first[a[ra[old_val]+1]] && a[ra[old_val]+1] != u) nbConflicts++;

            // Update 'b' with the new value
            b[s] = u;

            // Determine the answer based on current conflicts
            ans = (first[a[0]] == 0) && (nbConflicts == 0);
            cout << (ans ? "YA" : "TIDAK") << en;
        }
    }

    return 0;
}
