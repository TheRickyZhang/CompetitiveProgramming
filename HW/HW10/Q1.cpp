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

const int N = 50010;
vi tree;
int n, y, r, q, ly, ry, lv, rv;
ump<int, int> yrToIdx;
vi yr(N);
vi rn(N);

void build(int i, int a, int b) {
    if(a == b) tree[i] = rn[a];
    else {
        int m = (a + b) / 2;
        build(2*i + 1, a, m);
        build(2*i + 2, m + 1, b);
        tree[i] = max(tree[2*i +1], tree[2*i +2]);
    }
}

int query(int i, int a, int b, int l, int r) {
    if(r < a || l > b) return -INF;
    if(l <= a && b <= r) return tree[i];
    int m = (a + b) /2;
    return max(query(2*i +1, a, m, l, r), query(2*i +2, m+1, b, l, r));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(cin >> n) {
        if(n == 0) break;
        tree.assign(4*n, -INF);
        yr.assign(n, 0);
        rn.assign(n, 0);
        yrToIdx.clear();

        f(i, n) {
            cin >> y >> r;
            yrToIdx[y] = i;
            yr[i] = y; rn[i] = r;
        }

        build(0, 0, n-1);

        cin >> q;
        f(i, q) {
            cin >> ly >> ry;

            int lidx = lower_bound(all(yr), ly) - yr.begin();
            int ridx = lower_bound(all(yr), ry) - yr.begin();

            bool isl = (lidx < n && yr[lidx] == ly);
            bool isr = (ridx < n && yr[ridx] == ry);
            int mx = -INF;

            if(!isl && !isr) {
                cout<<"maybe"<<en;
            } else if(!isl) {
                rv = rn[ridx];
                if(lidx <= ridx -1) mx = query(0, 0, n-1, lidx, ridx -1);
                if(mx >= rv) cout<<"false"<<en;
                else cout<<"maybe"<<en;
            } else if(!isr) {
                lv = rn[lidx];
                if(lidx +1 <= ridx -1) mx = query(0, 0, n-1, lidx +1, ridx -1);
                if(mx >= lv) cout<<"false"<<en;
                else cout<<"maybe"<<en;
            } else {
                lv = rn[lidx];
                rv = rn[ridx];
                if(lv < rv) cout<<"false"<<en;
                else {
                    if(lidx +1 <= ridx -1) mx = query(0, 0, n-1, lidx +1, ridx -1);
                    if(mx >= rv) cout<<"false"<<en;
                    else {
                        if(ridx - lidx +1 == ry - ly +1) cout<<"true"<<en;
                        else cout<<"maybe"<<en;
                    }
                }
            }
        }
        cout<<en;
    }
}

