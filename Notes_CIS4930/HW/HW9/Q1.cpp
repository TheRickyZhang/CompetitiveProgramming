#include <bits/stdc++.h>
using namespace std;

// Shift values to indices, then segment tree for greatest directional subarray difference.
// AHHHH the reverse direction is so annoying
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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y,auto x,auto m,auto n) {return y >= 0 && y < m && x >= 0 && x < n; };

void build(vi &v, vvi &t, int i, int a, int b) {
    if(a == b) t[i] = {v[a], v[a], 0};
    else {
        int m = a + (b-a) / 2;
        build(v, t, i*2, a, m);
        build(v, t, i*2 + 1, m+1, b);
        vi l = t[i*2], r = t[i*2+1];
        t[i] = {min(l[0], r[0]), max(l[1], r[1]), max({r[1]-l[0], r[2], l[2]})};
    }
}

vi query(vvi &t, int i, int a, int b, int l, int r) {
    if(l > r) return {0, 0, -1};
    if(l == a && r == b) return t[i];
    int tm = a + (b-a)/2;
    vi ql = query(t, i*2, a, tm, l, min(r, tm));
    vi qr = query(t, i*2+1, tm+1, b, max(l, tm+1), r);
    if(ql[2] == -1) return qr;
    if(qr[2] == -1) return ql;
    return {min(ql[0], qr[0]), max(ql[1], qr[1]), max({qr[1] - ql[0], ql[2], qr[2]})};
}

int main() {
    int n; cin >> n;
    vi v(n), d(n); // base, step
    for(int i = 0; i < n; i++) cin >> v[i] >> d[i];
    int q; cin >> q;
    vvi queries(q);
    vi res(q);
    f(i, q) {
        int l, r; cin >>l>>r;
        queries[i] = {l-1, r-1};  // 1-indexing
    }

    for(int i = 0; i < 7; i++) {
        // Go from diagonal->straight
        vi vn(v);
        vi vn2(v);
        reverse(all(vn2));
        f(j, vn.size()){
            int offset = abs(j - i) % 7;
            int factor = min(offset, 6-offset);
            vn[j] += d[j]*factor;
            vn2[j] += d[n-1-j]*factor;
        }

        // FORWARD; segment tree/querying
        vvi t(4*n);
        build(vn, t, 1, 0, n - 1);
        f(j, q){
            if(queries[j][0] % 7 == i && queries[j][0] < queries[j][1]) {
                vi ans = query(t, 1, 0, n - 1, queries[j][0], queries[j][1]);
                res[j] = ans[2] == -1 ? 0 : ans[2];
            }
        }

        // REVERSE; segment tree/querying
        t = vvi(4*n);
        build(vn2, t, 1, 0, n - 1);
        f(j, q){
            int l = n-1-queries[j][0], r = n-1-queries[j][1];
            if(l % 7 == i && l < r) {
                vi ans = query(t, 1, 0, n-1, l, r);
                res[j] = ans[2] == -1 ? 0 : ans[2];
            }
        }
    }
    f(i, q) cout<<res[i]<<endl;
    return 0;
}