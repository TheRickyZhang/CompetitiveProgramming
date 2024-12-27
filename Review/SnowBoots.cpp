#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vvpii = vector<vpii>; using vpll = vector<pll>; using vvpll = vector<vpll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
using vvi = vector<vector<int>>; using vvll = vector<vector<ll>>; using mpq = priority_queue<ll, vector<ll>, greater<>>; using mpqq = priority_queue<pll, vpll, greater<>>;
#define ump unordered_map
#define ust unordered_set
#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");
constexpr int MOD = 1000000007; constexpr ll INF = INT_MAX-37; constexpr ll INFL = 0x3f3f3f3f3f3f3f3f; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
constexpr char EN = '\n'; constexpr char SP = ' '; auto en = EN; auto sp = SP;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = enable_if_t<!is_same_v<T_container, string>, typename T_container::value_type>> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

constexpr int N = 100000;
ll t, n, m, k, a, b;

// Key insight: We can iteratively remove valid tiles by first attempting the largest boot size
struct boot {
    int d, s, i; // depth, steps, index
};

int main() {
    cin>>n>>m;
    vi tiles(n); f(i, n) cin>>tiles[i]; // The order of the tiles is most important, so can't sort away
    vector<boot> boots(n);
    f(i, m) {
        cin>>boots[i].d>>boots[i].s; boots[i].i=i;
    }
    sort(all(boots), [&](boot& a, boot& b) {
        return a.d > b.d;
    });

    vi tilesByDepth(n-2); // Exclude the first and last
    for(int i=1; i<=n-2; ++i) tilesByDepth[i-1]=i;
    sort(all(tilesByDepth), [&](int a, int b) {return tiles[a]>tiles[b]; });

    set<int> validIndices; f(i, n) validIndices.insert(i);
    vb res(m, false);
    int i=0, step=1; // Iterate through tilesByDepth, eliminate largest tiles first
    for(auto b : boots) {
        while(i < n-2 && tiles[tilesByDepth[i]] > b.d) {
            auto it = validIndices.find(tilesByDepth[i]);
            step = max(step, *next(it)-*prev(it)); // Note that these bounds are always valid since 0 and n-1 always remain
            validIndices.erase(it); // By monotonicity this index is not available for any of the next boots as well
            i++;
        }
        res[b.i]= b.s >= step;
    }
    for(auto x : res) cout<<x<<en;
}

