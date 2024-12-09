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
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-37; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

class Solution {
public:
int n;
    vi tree;
    // This could be made faster with iterative but I like recursion
    void build(int i, int a, int b) {
        if(a==b) tree[i] = 1;
        else {
            int m=(a+b)/2;
            build(2*i, a, m);
            build(2*i+1, m+1, b);
            tree[i] = tree[2*i] + tree[2*i+1];
        }
    }
    void update(int i, int a, int b, int pos) {
        if(a==b) {
            tree[i] = 0;
        }
        else {
            int m = (a+b)/2;
            if(pos <= m) update(2*i, a, m, pos);
            else update(2*i+1, m+1, b, pos);
            tree[i] = tree[2*i] + tree[2*i+1];
        }
    }
    int query(int i, int a, int b, int pos) {
        if(a==b) return a;
        int m = (a+b)/2;
        if(pos<=tree[2*i]) return query(2*i, a, m, pos);
        else return query(2*i+1, m+1, b, pos-tree[2*i]);
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // taller first -> becomes problem of insertion based on taken+offset
        sort(all(people), [&](const vi& a, const vi& b) {
            if(a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });
        // cout<<people<<en;
        n = people.size();
        vvi res(n);

        // I saw this idea from CSES range query problem! Set nodes as 0/1 to determine empty
        tree.resize(4*n); build(1,0,n-1);
        // cout<<tree<<en;
        f(i, n) {
            int h = people[i][0];
            int f = people[i][1];
            int idx = query(1,0,n-1,f+1);
            // cout<<f<<" "<<idx<<en;
            res[idx] = people[i];
            update(1, 0, n-1, idx);
            // cout<<tree<<en;
        }
        return res;
    }
};
