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
int t, n, m, k, a, b;
void solve() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    vpii nums(n);
    vi temp(n);
    f(i, n) {
        int a, b; cin>>a>>b;
        nums[i]={a, b};
        temp[i]=b;
    }
    sort(all(temp));
    multiset<int> s(all(temp));  // Much faster to construct multiset form sorted range than inserting one by one
    sort(all(nums), [&](pii& a, pii& b) {
        if(a.ff==b.ff) return a.ss<b.ss;
        return a.ff > b.ss;
    }); // Descending first, rev

    vi pre(n+1, 0); // 1-indexed prefix
    f(i, n) pre[i+1] = max(pre[i], nums[i].ss);
    int res=1e9;
    f(i, n) { // Choose which of a is max
        s.erase(s.find(nums[i].ss)); // Erase element
        int x = nums[i].ff;
        int y = pre[i];
        if(y-x > res) break;
        auto lit = s.upper_bound(x);
        int l = lit==s.begin() ? y : *prev(lit);
        auto rit = s.lower_bound(x);
        int r = rit==s.end() ? y : *rit;
        res = min(res, abs(x - max(y, l)));
        res = min(res, abs(x - max(y, r)));
        // cout<<"pos"<<sp<<i<<sp<<res<<en;
    }
    cout<<res<<en;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>t; f(i, t) solve();
}