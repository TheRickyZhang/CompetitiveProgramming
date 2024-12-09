#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vpll = vector<pll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
using vvi = vector<vector<int>>; using vvll = vector<vector<ll>>; using mpq = priority_queue<ll, vector<ll>, greater<>>; using mpqq = priority_queue<pll, vpll, greater<>>;
#define ump unordered_map
#define ust unordered_set
#define f(i, to) for (int i = 0; i < (to); ++i)
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
constexpr int MOD = 1000000007; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n'; constexpr char sp = ' ';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

const int INF = 1e9;
const int MAXK = 12; // Max number of key points (T + W + C)
const int MAXC = 10; // Maximum number of chocolates

int m, n, k;
vector<string> grid;
vector<pii> keyp; // Key points: T (start), W (end), and Cs (chocolates)
int dist_matrix[MAXK][MAXK]; // Shortest distances between key points
int dp_table[1 << MAXC][MAXK]; // DP table: [bitmask][current point]

// Check if the coordinates are within grid bounds
bool in_bounds(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

// BFS to compute shortest distances from keyp[id] to all other key points
void bfs(int id) {
    vector<vector<int>> cost(m, vector<int>(n, INF));
    queue<pii> q;
    int sx = keyp[id].first, sy = keyp[id].second;
    q.push({sx, sy});
    cost[sx][sy] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (auto &[dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (in_bounds(nx, ny) && grid[nx][ny] != '#' && cost[nx][ny] == INF) {
                cost[nx][ny] = cost[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    // Populate the distance matrix for keyp[id] to all other key points
    for (int i = 0; i < k; ++i) {
        int tx = keyp[i].first, ty = keyp[i].second;
        dist_matrix[id][i] = cost[tx][ty];
    }
}

// Bitmask DP to find the shortest path to collect all chocolates and reach W
int solve() {
    int num_c = k - 2; // Number of chocolates
    int all_mask = (1 << num_c) - 1;

    // Initialize DP table with INF
    for (int mask = 0; mask <= all_mask; ++mask)
        fill(dp_table[mask], dp_table[mask] + k, INF);

    dp_table[0][0] = 0; // Start at T with no chocolates collected

    for (int mask = 0; mask <= all_mask; ++mask) {
        for (int u = 0; u < k; ++u) {
            if (dp_table[mask][u] == INF) continue;

            // Try moving to any uncollected chocolate
            for (int c = 0; c < num_c; ++c) {
                if (!(mask & (1 << c))) {
                    int v = 2 + c; // Index of the c-th chocolate
                    if (dist_matrix[u][v] == INF) continue; // Skip if unreachable
                    int new_mask = mask | (1 << c);
                    dp_table[new_mask][v] = min(dp_table[new_mask][v], dp_table[mask][u] + dist_matrix[u][v]);
                }
            }

            // If all chocolates are collected, try moving to W
            if (mask == all_mask) {
                int w = 1; // Index of W
                if (dist_matrix[u][w] != INF) {
                    dp_table[mask][w] = min(dp_table[mask][w], dp_table[mask][u] + dist_matrix[u][w]);
                }
            }
        }
    }

    return dp_table[all_mask][1]; // Minimum cost to collect all chocolates and reach W
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        cin >> m >> n;
        grid.assign(m, "");
        keyp.clear();

        // Read the grid
        for (int i = 0; i < m; ++i) {
            cin >> grid[i];
        }

        // Locate T and W first
        bool foundT = false, foundW = false;
        for (int i = 0; i < m && (!foundT || !foundW); ++i) {
            for (int j = 0; j < n && (!foundT || !foundW); ++j) {
                if (grid[i][j] == 'T') {
                    keyp.emplace_back(i, j);
                    foundT = true;
                }
                else if (grid[i][j] == 'W') {
                    keyp.emplace_back(i, j);
                    foundW = true;
                }
            }
        }

        // Locate all chocolates
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == 'C')
                    keyp.emplace_back(i, j);

        k = keyp.size();

        // Check if T and W are present
        if (k < 2) {
            cout << "Mission Failed!\n";
            continue;
        }

        // Compute all pair shortest paths between key points
        bool possible = true;
        for (int i = 0; i < k && possible; ++i) {
            bfs(i);
            for (int j = 0; j < k && possible; ++j) {
                if (i != j && dist_matrix[i][j] == INF) {
                    // If any key point is unreachable from another, mission fails
                    possible = false;
                }
            }
        }

        if (!possible) {
            cout << "Mission Failed!\n";
            continue;
        }

        // Solve the problem using DP
        int result = solve();

        // Output the result
        if (result == INF) {
            cout << "Mission Failed!\n";
        }
        else {
            cout << result << '\n';
        }
    }

    return 0;
}