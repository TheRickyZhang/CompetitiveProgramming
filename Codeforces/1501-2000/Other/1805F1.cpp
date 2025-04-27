#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pi = pair<int, int>;
using pll = pair<ll, ll>; using vpi = vector<pi>; using vvpi = vector<vpi>; using vpll = vector<pll>; using vvpll = vector<vpll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
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
constexpr ll MOD = 1000000007; constexpr ll INF = INT_MAX-37; constexpr ll INFL = 0x3f3f3f3f3f3f3f3f; const vector<pi> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
constexpr char EN = '\n'; constexpr char SP = ' '; auto en = EN; auto sp = SP;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = enable_if_t<!is_same_v<T_container, string>, typename T_container::value_type>> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

constexpr int N = 100000;
ll n, m, k, a, b;

ll poww(ll x, ll p) {
    ll res=1;
    while(p) {
        if(p % 2 == 1) res = (res*x) % MOD;
        x = (x*x) % MOD;
        p>>=1;
    }
    return res;
}
void chill(vll& nums, ll& res) {
    ll sz = nums.size();
    ll mn = nums[0];
    res+= mn*poww(2, sz-1) % MOD;
    f(i, sz) nums[i]-=mn;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    vll arr(n);
    f(i, n) cin>>arr[i];
    sort(all(arr));
    ll res=0;
    chill(arr, res);
    function<vll(vll&)> transform = [&](vll& nums) {
        // chill(nums, res);
        int sz = nums.size();
        vll ress(sz-1);
        typedef tuple<ll, ll, ll> t;
        priority_queue<t, vector<t>, greater<t>> q; // sum, i, j
        f(i, sz-1) q.push({nums[i+1]+nums[0], i+1, 0});
        f(idx, sz-1) {
            auto [x, i, j] = q.top(); q.pop();
            ress[idx]=x;
            if(j>=n-1) continue;
            if(j+1 != i && j<sz-1) q.push({nums[i]+nums[j+1], i, j+1});
            else if(j<sz-2) q.push({nums[i]+nums[j+2], i, j+2});
        }
        f(i, sz-1) ress[i] = (ress[i] % MOD);
        return ress;
    };
    f(i, n-1) {
        arr=transform(arr);
    }
    // cout<<res<<sp<<arr[0]<<en;
    res=(res + arr[0]) % MOD;
    cout<<res<<en;
}