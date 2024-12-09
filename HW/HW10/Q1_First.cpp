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

//First attempt - almost but very convoluted. Missing check for ridx-lidx < r-l. Why can't they just make the logic a bit easier?
int N = 50001;
vi tree;
int n, y, r, m, ly, ry, lv, rv;
ump<int, int> yrToIdx;
vi yr(N);
vi rn(N);

void build(int i, int a, int b) {
    if(a==b) tree[i] = rn[a];
    else {
        int m = (a+b)/2;
        build(2*i, a, m);
        build(2*i+1, m+1, b);
        tree[i] = max(tree[2*i], tree[2*i+1]);
    }
}

int query(int i, int a, int b, int l, int r) {
    if(l>r || b<l || a>r) return -INF;
    if(a==l && b==r) return tree[i]; // NOTE: could change to inequality
    int m = (a+b)/2;
    int lq = query(2*i, a, m, l, min(r, m));
    int rq = query(2*i+1, m+1, b, max(l, m+1), r);
    if(lq == -INF) return rq; if(rq == -INF) return lq;
    return max(lq, rq);
}

// These are years
int firstQuery(int l, int r) {
    // int lidx, ridx;
    int lidx = yrToIdx.count(l) ? yrToIdx[l]+1 : lower_bound(all(yr), l) - yr.begin();
    int ridx = yrToIdx.count(r) ? yrToIdx[r]-1 : upper_bound(all(yr), r) - yr.begin() - 1;

    cout<<"idx "<<lidx<<" "<<ridx<<en;
    if(lidx >= n || ridx < 0 || lidx > ridx) {
        cout<<"?"<<en;
        return -INF; // no elements = automatically passes check
    }
    return query(1, 0, n-1, lidx, ridx);
}

int main() {
    while(cin>>n) {
        if(n==0) break;
        tree.assign(4*n, 0); yr.assign(n, 0); rn.assign(n, 0);
        yrToIdx.clear();

        vpii copy(n);
        f(i, n) {
            cin>>y>>r;
            yrToIdx[y] = i;
            yr[i] = y; rn[i] = r;
        }
        cout<<"yr->idx: "<<yrToIdx<<en;

        build(1, 0, n-1);

        cin>>m;
        f(i, m) {
            cin>>ly>>ry;

            int mx = firstQuery(ly, ry);
            rv = yrToIdx.count(ry) ? rn[yrToIdx[ry]] : -INF;
            lv = yrToIdx.count(ly) ? rn[yrToIdx[ly]] : -INF;

            cout<<mx<<" "<<lv<<" "<<rv<<en;
            if(mx == -INF && (rv == -INF || lv == -INF)) {
                cout<<"maybe"<<en;
            } else if(mx == -INF) {
                cout<<(rv > lv ? "false" : "maybe")<<en;
            } else if(rv == -INF) {
                cout<<(mx >= lv ? "false" : "maybe")<<en;
            } else if(lv == -INF) {
                cout<<(mx >= rv ? "false" : "maybe")<<en;
            } else {
                if(mx < rv && rv <= lv) {
                    cout<<"true"<<en;
                } else {
                    cout<<"false"<<en;
                }
            }
        }
    }
}
