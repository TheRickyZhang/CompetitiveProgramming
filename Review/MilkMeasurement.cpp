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

int main() {
    setIO("measurement");
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int g; cin>>n>>g;
    vvi nums(n);
    map<int, int> mp; // id, prod
    map<int, int> freq; // prod, freq;
    f(i, n) {
        int day, id, d; cin>>day>>id>>d;
        nums[i] = {day, id, d};
        mp[id]=g;
    }
    sort(all(nums), [&](vi& a, vi& b) {
        return a[0]<b[0];
    }); // Sorted by day, id, d. Note that since possible duplicate days ONLY sort by day
    freq[g]=n;

    int res=0;
    for(auto v : nums) {
        int id=v[1], d=v[2];
        int prev=mp[id];
        int curr=prev+d;
        bool wasLargest = prev==freq.rbegin()->first; // Note the rbegin()->first access
        int prevCount=freq[prev];

        // Remove
        mp[id]=curr;
        if(--freq[prev] == 0) freq.erase(prev);
        freq[curr]++;
        bool newLargest = curr==freq.rbegin()->first;
        if(wasLargest) {
            if(!newLargest || freq[curr] != prevCount) res++; // Not only XOR, but change in frequency also triggers res++
        } else if(newLargest) {
            res++;
        }
    }
    cout<<res<<en;
}