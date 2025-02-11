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

// Common mistakes/clarifications:
// Sometimes when sorting pii you should actually sort the secondary direction opposite of the primary
// Most time-based priority things sort by ending time first, not starting
// Use a multiset instead of a set, when failing!

// Use set.upper_bound instead of upper_bound(all(set)), for multiset weird syntax this can mean log(n) vs n time.

// Lower_bound is first [a...], upper bound is first (a...)
// 1st >= x: lower_bound
// 1st <= x: upper_bound-1 (handle upper_bound==begin()) OR lower_bound with greater<>
// 1st > x: upper_bound
// 1st < x: lower_bound-1 (handle lower_bound==begin()) OR upper_bound with greater<>

// Two different types of binary search
int bs(vi& arr, int x)
    int l, r;
    while(l<r)
        int mid=l+(r-l)/2;
    if(arr[mid]<x)
        l=m+1;
    else
        r=m;
    return l; // Sometimes might return l-1 for last invalid

int bs(vi& arr, int x)
    int l, r;
    while(l<=r)
        int m=l+(r-l)/2;
    if(arr[m]<x) l=m+1;
    else if(arr[m]>x) r=m-1;
    else return m;

auto binarySearch = [&](int x) {  // Example of from-scratch binary search
    int l, r;
    while (l<r) {
        int m = l+(r-l)/2;

        // >=
        if (nums[m] < x) l=m+1; // The +1 is when it goes over, so returns smallest element > (upper_bound)
        else r=m;

        // >
        if(nums[m] <= x) l=m+1;
        else r=m;

        // NOTE: reverse ops <=, < just return l-1;
    }
    return l;
};

// Two pointer (verbose)
vi nums;
mp<int, int> mp;
int l=0, r=0, cnt=0, res, mx;
while(r<n)
    while(r<n && cnt < mx)
        if(condition[nums[r]])
            if(!mp[x]++) cnt++;
        r++;
    while(l<r && cnt >=mx)
        res=max(res, (r-1) - (l) + 1);
        if(condition[nums[l]])
            if(--mp[nums[l]] == 0) cnt--;
        l++;

// Two pointer (simple)
int l=0, cnt=0, res=0, mx=...;
mp<int, int> mp;
f(r, n)
    // Note the equivilancy in &&; this will short circuit and only affect mp if condition true
    if (condition[nums[r]] && !mp[nums[r]]++) cnt++;
    while (cnt >= mx)
        res = max(res, r-l+1);
        if (condition[nums[l]] && --mp[nums[l]] == 0) cnt--;
        l++;
