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
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-97; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y,auto x,auto m,auto n) {return y >= && y < m && x >= 0 && x < n; };

int main() {
    int m, n, k; cin>>m>>n>>k;
    vector<string> g(m);
    f(i, m) cin>>g[i];
    if(k%2==1) {
        cout<<"IMPOSSIBLE"<<en;
        return 0;
    }
    int sy, sx;
    f(i, m) f(j, n) if(g[i][j]=='X') {
        sy=i; sx=j;
    }

    // BFS for dist
    int t = 1;
    vvi dist(m, vi(n, INF));
    queue<pii> q;
    q.push({sy, sx}); dist[sy][sx] = 0;
    while(!q.empty()) {
        int sz = q.size();
        f(i, sz) {
            auto [y, x] = q.front(); q.pop();
            for(auto [dy, dx] : dirs) {
                int ny = y+dy; int nx=x+dx;
                if(check(ny,nx,m,n) && g[ny][nx] != '*' && dist[ny][nx] == INF) {
                    q.push({ny, nx});
                    dist[ny][nx] = t;
                }
            }
        }
        t++;
    }

    string res;
    for(int i = 1; i <= k; ++i) {
        f(j, 4) {
            auto [dy, dx] = dirs[j];
            int ny = sy+dy; int nx=sx+dx;
            if(check(ny,nx,m,n) && g[ny][nx] != '*' && dist[ny][nx] <= k-i) {
                sy=ny; sx=nx;
                if(j==0) res+='D';
                if(j==1) res+='L';
                if(j==2) res+='R';
                if(j==3) res+='U';
                break;
            }
        }
        if(res.size() != i) {
            cout<<"IMPOSSIBLE"<<en;
            return 0;
        }
    }
    cout<<res<<en;
}