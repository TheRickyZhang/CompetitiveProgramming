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
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-96; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

const int N = 1000;
char grid[N][N];
pii par[N][N];
char dir[N][N];
bool vis[N][N];
int n, m;

int main() {
    cin>>n>>m;
    pii s, e;
    f(i, n) f(j, m) {
        cin>>grid[i][j];
        if(grid[i][j] == 'A') s = {i, j};
        if(grid[i][j] == 'B') e = {i, j};
    }

    queue<pii> q;
    q.push(s);
    vis[s.first][s.second] = true;

    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if(x == e.first && y == e.second) {
            str path;
            while(make_pair(x, y) != s) {
                path += dir[x][y];
                tie(x, y) = par[x][y];
            }
            reverse(all(path));
            cout<<"YES\n"<<path.size()<<en<<path<<en;
            return 0;
        }

        f(i, 4) {
            int nx = x + dirs[i].first, ny = y + dirs[i].second;
            if(check(nx, ny, n, m) && !vis[nx][ny] && grid[nx][ny] != '#') {
                vis[nx][ny] = true;
                par[nx][ny] = {x, y};
                dir[nx][ny] = "DLRU"[i];
                q.push({nx, ny});
            }
        }
    }

    cout<<"NO\n";
    return 0;
}
