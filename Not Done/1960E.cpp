#include <bits/stdc++.h>
using namespace std;

// Basic DFS but only left/up, don't mess up!
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
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-97; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y,auto x,auto m,auto n) {return y >= 0 && y < m && x >= 0 && x < n; };

int n;
vector<string> g;
string temp;

void solve() {
    cin>>n;
    g.resize(n);
    f(i, n) {
        cin>>g[i];
    }
    vvi visited(n, vi(n, 0));
    queue<pii> q;

    int cnt = 0;
    f(i, n) {
        if(g[n-1][i]=='1') {
            q.push({n-1, i});
            visited[n-1][i] = 1;
            cnt++;
        }
    }
    f(i, n-1)  {
        if(g[i][n-1]=='1') {
            q.push({i, n-1});
            visited[i][n-1] = 1;
            cnt++;
        }
    }
    vpii newDirs = {{-1, 0}, {0, -1}}; // Note only check up and left
    while(!q.empty()) {
        auto [y, x] = q.front(); q.pop();
        for(auto [dy, dx] : newDirs) {
            int ny=dy+y, nx=dx+x;
            if(check(ny, nx, n, n) && !visited[ny][nx] && g[ny][nx]=='1') {
                visited[ny][nx] = 1;
                q.push({ny, nx});
                cnt++;
            }
        }
    }
    f(i, n) f(j, n) if(g[i][j] == '1') cnt--;
    if(cnt < 0) {
        cout<<"NO"<<en;
    } else {
        cout<<"YES"<<en;
    }
}

int main() {
    int t; cin>>t;
    f(i, t) solve();
}