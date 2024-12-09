#include <bits/stdc++.h>
using namespace std;

// Salary Queries
// USACO provided solution - coordinate compression with BIT
using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
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
#define str string
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-96; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y,auto x,auto m,auto n) {return y >= 0 && y < m && x >= 0 && x < n; };

const int MX = 4e5 + 5;

ll bit[MX];
vector<int> vals;
int n, q;
void update(int i, int val) {
    for(; i <= MX; i += i & (-i)) { bit[i] += val; }
}
void add(int x, int b) {
    int ind = upper_bound(vals.begin(), vals.end(), x) - vals.begin();
    update(ind, b);
}
ll sum(int x) {
    ll res = 0;
    for (; x; x -= x & (-x)) { res += bit[x]; }
    return res;
}
ll query(int x) {
    int ind = upper_bound(vals.begin(), vals.end(), x) - vals.begin();
    return sum(ind);
}

int main() {
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) { cin >> arr[i]; }
    vals = arr;
    vector<array<int, 3>> rec;
    for (int i = 0; i < q; i++) {
        char t;
        int a, b;
        cin >> t >> a >> b;
        rec.push_back({t == '?', a, b});
        if (t == '!') vals.push_back(b);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < n; i++) { add(arr[i], 1); }
    for (auto u : rec) {
        u[1]--;
        if (u[0] == 0) {
            add(arr[u[1]], -1);
            arr[u[1]] = u[2];
            add(arr[u[1]], 1);
        } else {
            cout << query(u[2]) - query(u[1]) << '\n';
        }
    }
}



