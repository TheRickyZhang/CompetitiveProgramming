#include <bits/stdc++.h>
using namespace std;

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

struct TN {
    unordered_map<char, TN*> ch;
    bool win = false;  // possibility to win
    bool lose = false; // forced to lose
};

void dfs(TN* node) {
    if (node->ch.empty()) {
        node->lose = true; // No moves left, current player loses
        return;
    }
    node->win = false;
    node->lose = false;
    for (auto& [c, child] : node->ch) {
        dfs(child);
        if (!child->win) node->win = true;   // If any child is losing, current is winning
        if (!child->lose) node->lose = true; // If any child is winning, current can lose
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n;
    long long k;
    cin >> n >> k;
    TN* root = new TN();
    // insert all
    f(i, n) {
        str s; cin >> s;
        TN* node = root;
        for (char ch : s) {
            if (!node->ch.count(ch)) node->ch[ch] = new TN();
            node = node->ch[ch];
        }
    }
    dfs(root);
    if (!root->win) {
        cout<<"Second"<<en;
    } else if (root->lose) {   // If can pick, can change state in favor
        cout<<"First"<<en;
    } else {
        cout<<(k % 2==1 ? "First" : "Second")<<en;
    }
    return 0;
}
