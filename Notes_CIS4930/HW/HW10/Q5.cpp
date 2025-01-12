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
#define ff first
#define ss second

// Honestly not too sure what's going on here...
class segment_tree {
public:
    vll t;
    int n;
    
    // Constructor initializes the segment tree with size x and sets all values to -INF
    segment_tree(int x) {
        n = x;
        t.assign(2 * n, -INF);
    }
    void update(int pos, ll val) {
        for(t[pos += n] = val; pos > 1; pos >>= 1)
            t[pos / 2] = max(t[pos], t[pos ^ 1]);
    }
    int query(int a, int b) {
        ll res = -INF;
        for(int l = a + n, r = b + n + 1; l < r; l >>= 1, r >>= 1){
            if(l & 1) res = max(res, t[l++]);
            if(r & 1) res = max(res, t[--r]);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> maximumSumQueries(vector<int>& a, vector<int>& b, vector<vector<int>>& q) {
        // create and sort the s-t pairs in descending order
        vpii st, v;
        f(i, a.size()) st.pb({a[i], b[i]});
        sort(rall(st));
        
        // filter out non-useful pairs for v, temp
        vpii temp;
        v.pb(st[0]);
        int ix = 0;
        temp.pb({st[0].ss, ix++});
        f(i, st.size()) {
            pii p = v.back();
            if(p.ff >= st[i].ff && p.ss >= st[i].ss) continue;
            v.pb(st[i]);
            temp.pb({st[i].ss, ix++});
        }
        
        // sort temp and map values->indieces
        sort(all(temp));
        map<int, vi> id;
        for(auto x : temp) id[x.ff].pb(x.ss);
        
        int n = v.size();
        segment_tree tr(n);
        
        f(i, q.size()) {
            q[i].pb(i); // append original index
            int r = 0, l = n - 1;
            // binary search where v[mid].ff >= q[i][0]
            while(r <= l) {
                int mid = (r + l) / 2;
                if(v[mid].ff < q[i][0]) l = mid - 1;
                else r = mid + 1;
            }
            q[i].pb(l);
            // Rearrange the query parameters
            swap(q[i][0], q[i][3]);
            swap(q[i][1], q[i][2]);
        }
        
        sort(all(q));
        
        int pre = 0;
        vi fans(q.size());
        
        f(i, q.size()) {
            // Update the segment tree with all relevant pairs up to the current query
            while(pre <= q[i][0]) {
                ll sum = v[pre].ff + v[pre].ss;
                int ix = id[v[pre].ss].back();
                tr.update(ix, sum);
                pre++;
            }
            
            // Binary search to find the lower bound for the second threshold
            int tt = q[i][2];
            int r = 0, l = n - 1;
            while(r <= l) {
                int mid = (r + l) / 2;
                if(temp[mid].ff >= tt)
                    l = mid - 1;
                else
                    r = mid + 1;
            }
            fans[q[i][1]] = tr.query(l + 1, n - 1);
        }
        for(int &x : fans) {
            if(x == -INF) x = -1;
        }
        return fans;
    }
};