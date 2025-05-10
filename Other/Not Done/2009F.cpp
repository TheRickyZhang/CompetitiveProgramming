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

constexpr ll N = 2e5+1;
vll nums(N, 0);

void solve() {
    int n, q; cin >> n >> q;
    vi nums(n);
    f(i, n) {
        cin>>nums[i];
    }
    int tot = accumulate(all(nums), 0);

    f(i, q) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        int res = 0;
        int leftFreq = l % n;
        int lcycle = l / n;
        f(i, leftFreq) {
            res += nums[(2*n-1-i-lcycle)%n];
        }
        int rcycle = r/n;
        int rightFreq = r % n;
        res += tot*(rcycle-lcycle);
        f(i, rightFreq+1) {
            res += nums[(i+rcycle)%n];
        }
        cout << "d " << leftFreq << " " << lcycle << " " << rightFreq << " " << rcycle << en;
        cout << res << en;
    }
}
int main() {
    ios::sync_with_stdio();
    cin.tie(NULL);

    ll t; cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}