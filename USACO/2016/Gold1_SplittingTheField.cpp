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
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");
constexpr int MOD = 1000000007; constexpr ll INF = INT_MAX-37; constexpr ll INFL = 0x3f3f3f3f3f3f3f3f; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
constexpr char EN = '\n'; constexpr char SP = ' '; auto en = EN; auto sp = SP;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = enable_if_t<!is_same_v<T_container, string>, typename T_container::value_type>> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

int n;
ll res=0;
vpll nums;
ll search() {
    sort(all(nums));
    vpll pre(n), suf(n); // min/mx y-coords, since nums is sorted by x-coords
    auto upd = [](const pll& a, ll b) {
        return make_pair(min(a.ff, b), max(a.ss, b)); // Updates the min/max with a new y-coord
    };
    pre[0]={nums[0].ss, nums[0].ss};
    f(i, n-1) pre[i+1] = upd(pre[i], nums[i+1].ss);

    suf[n-1]={nums[n-1].ss, nums[n-1].ss};
    repr(i, n-1, 0) suf[i]=upd(suf[i+1], nums[i].ss);

    ll area = (nums[n-1].ff - nums[0].ff) * (pre[n-1].ss - pre[n-1].ff);

    ll res=INFL;
    f(i, n-1) {
        if(nums[i].ff == nums[i+1].ff) continue;
        ll r1=(nums[i].ff-nums[0].ff) * (pre[i].ss - pre[i].ff);
        ll r2=(nums[n-1].ff-nums[i+1].ff) * (suf[i+1].ss - suf[i+1].ff);
        res=min(res, r1+r2);
    }
    // cout<<pre<<en<<suf<<en;
    // cout<<area<<SP<<res<<en;
    return area-res;
}

int main() {
    setIO("split");
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    nums.assign(n, pii());
    f(i, n) cin>>nums[i].ff>>nums[i].ss;
    ll res=0;
    res=max(res, search());
    for(pll& x : nums) swap(x.ff, x.ss);
    res=max(res, search());
    cout<<res<<en;
}