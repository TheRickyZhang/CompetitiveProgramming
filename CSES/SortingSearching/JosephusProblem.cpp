#include <bits/stdc++.h>
using namespace std;

// Set iterators will be modified!!!
using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vpll = vector<pll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
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
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-37; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n'; constexpr char sp = ' ';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

int n, k;
vi tree;
vi nums;

void add(int i, int x) {
    while(i <= n) {
        tree[i] += x;
        i += (i & -i);
    }
}
int query(int i) {
    int res = 0;
    while(i > 0) {
        res += tree[i];
        i -= (i & -i);
    }
    return res;
}

// NEED to use < to find last less than, then add 1, otherwise <= can overshoot since there can be multiple positions with same sum
int findkth(int k) {
    int i = 0;
    int mask = 1 << (int)log2(n);
    while(mask > 0) {
        int ni = i + mask;
        if(ni <= n && tree[ni] < k) {
            i = ni;
            k -= tree[ni];
        }
        mask >>= 1;
    }
    return i + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n>>k;
    tree.resize(n + 1, 0);
    nums.resize(n, 0);
    f(i, n) add(i + 1, 1);

    int curr = 0;

    f(i, n) {
        curr = (curr + 1) % (n - i);
        int pos = findkth(curr + 1);
        cout<<pos<<en;
        add(pos, -1);
    }
    return 0;
}
