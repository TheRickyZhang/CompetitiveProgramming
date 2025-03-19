#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vvpii = vector<vpii>; using vpll = vector<pll>; using vvpll = vector<vpll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
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
constexpr int MOD = 1000000007; constexpr ll INF = INT_MAX-37; constexpr ll INFL = 0x3f3f3f3f3f3f3f3f; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n'; constexpr char sp = ' ';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = enable_if_t<!is_same_v<T_container, string>, typename T_container::value_type>> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

constexpr int N = 100000;
ll t, n, m, k, a, b;

vi p, sz;
int par(int x) {
    if(x==p[x]) return x;
    return p[x]=par(p[x]);
}
void unite(int x, int y) {
    int a=par(x), b=par(y);
    if(a==b) return;
    if(sz[a]<sz[b]) swap(a, b);
    sz[a]+=sz[b]; p[b]=a;
}
typedef tuple<int, int, int> edge;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ifstream cin("wormsort.in"); ofstream cout("wormsort.out");
    cin>>n>>m;
    vi pos(n);
    f(i, n) {
        cin>>pos[i]; pos[i]--;
    }
    bool early=true;
    f(i, n) if(pos[i]!= i) early=false;
    if(early) { cout<<-1<<en; return 0; }
    vector<edge> edges;
    f(i, m) {
        int u, v, w; cin>>u>>v>>w; u--; v--;
        edges.pb({w, u, v});
    }
    sort(rall(edges));
    int l=1, r=1e9;
    while(l < r) {
        // cout<<l<<" "<<r<<en;
        int mid=l+(r-l)/2;
        p.assign(n, 0); sz.assign(n, 1); f(i, n) p[i]=i;
        bool valid=true;
        for(auto [w, u, v] : edges) {
            // cout<<w<<" "<<u<<" "<<v<<en;
            if(w<mid) break; unite(u, v);
        }
        // f(i, n) cout<<par(i)<<" "<<par(pos[i])<<en;
        // cout<<en;
        f(i, n) {
            if(par(i) != par(pos[i])) {
                valid=false; break;
            }
        }
        if(!valid) {
            r=mid;
        } else {
            l=mid+1;
        }
    }
    cout<<l-1<<en;
}