#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using pii = pair<int, int>;
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
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define trav(a, x) for (auto &a : x)
constexpr int MOD = 1000000007; const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };

int h, w;

void solve() {
    vvi grid(h, vi(w));
    string row;
    f(i, h) {
        cin >> row;
        f(j, w) {
            grid[i][j] = (row[j] == '#' ? 0 : 1);
        }
    }
    int res = 0;
    // use -1 as visited;
    f(i, h) {
        f(j, w) {
            if(grid[i][j] != 1) continue;

            res++;
            stack<pii> s;
            s.emplace(i, j);
            while(!s.empty()) {
                auto [y, x] = s.top();
                s.pop();
                for(auto [dy, dx] : dirs) {
                    int ny = y+dy;
                    int nx = x+dx;
                    if(ny >= 0 && ny < h && nx >= 0 && nx < w && grid[ny][nx] == 1) {
                        s.emplace(ny, nx);
                        grid[ny][nx] = -1;
                    }
                }
            }
        }
    }
    cout << res << en;
}
int main() {
    ios::sync_with_stdio();
    cin.tie(NULL);
    int q = 1;
    while(cin >> h >> w) {
        cout << "Case " << q << ": ";
        solve();
        q++;
    }
    return 0;
}