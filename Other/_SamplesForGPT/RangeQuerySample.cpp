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


int main() {
    int n, q; cin>>n>>q;
    vll nums(n+1);
    f(i, n) cin>>nums[i+1];
    for(int i = 1; i <= n; ++i) {
        nums[i] += nums[i-1];
    }
    f(i, q) {
        int l, r;
        cin>>l>>r;
        ll res = nums[r] - nums[l-1];
        cout<<res<<en;
    }
}


int main() {
    int n, q; cin>>n>>q;
    vll nums(n+1);
    f(i, n) cin>>nums[i+1];
    for(int i = 1; i <= n; ++i) {
        nums[i] += nums[i-1];
    }
    f(i, q) {
        int l, r;
        cin>>l>>r;
        ll res = nums[r] - nums[l-1];
        cout<<res<<en;
    }
}


#define N 200000
ll n, q, t, a, b, u, k;
vll diff(N+1, 0);

void add(ll i, ll x) {
    while(i <= n) {
        diff[i] += x;
        i += (i&-i);
    }
}

ll sum(ll i) {
    ll res = 0;
    while(i>0) {
        res += diff[i];
        i -= (i&-i);
    }
    return res;
}

int main() {
    cin>>n>>q;
    vll nums(n);
    f(i, n) cin>>nums[i];

    // Add the difference to diff
    for(int i = 1; i <= n; ++i) {
        ll x = nums[i-1];
        add(i, x);
        add(i+1, -x);
    }
    f(i, q) {
        cin>>t;
        if(t == 1) {
            cin>>a>>b>>u;
            add(a, u);
            add(b+1, -u);
        } else {
            cin>>k;
            cout<<sum(k)<<en;
        }
    }
    return 0;
}


struct node {
    ll any{};
    ll pre{};
    ll post{};
    ll cumSum{};
    node() : any(0), pre(0), post(0), cumSum(0) {}
    explicit node(ll a) : any(a), pre(a), post(a), cumSum(a) {}
    node(ll a, ll b, ll c, ll d) : any(a), pre(b), post(c), cumSum(d) {}
};

node combine(const node& a, const node& b) {
    ll newAny = max({a.any, b.any, a.post + b.pre});
    ll newPre = max(a.pre, a.cumSum + b.pre);
    ll newPost = max(b.post, b.cumSum + a.post);
    ll cumSum = a.cumSum + b.cumSum;
    return {newAny, newPre, newPost, cumSum};
}

const ll NINF = -1e18;
const ll N = 200000;
vector<node> tree(4*N);
vll nums(N);

void build(ll i, ll a, ll b) {
    if(a==b) tree[i] = node(nums[a]);
    else {
        ll m = (a+b)/2;
        build(2*i, a, m);
        build(2*i+1, m+1, b);
        tree[i] = combine(tree[2*i], tree[2*i+1]);
    }
}

void update(ll i, ll a, ll b, ll pos, ll val) {
    if(a==b) tree[i] = node(val);
    else {
        ll m = (a+b)/2;
        if(pos<=m) update(2*i, a, m, pos, val);
        else update(2*i+1, m+1, b, pos, val);
        tree[i] = combine(tree[2*i], tree[2*i+1]);
    }
}

node query(ll i, ll a, ll b, ll l, ll r) {
    if(l>r) return node(NINF); // Hopefully this is the same as a sentinel node
    if(a==l&&b==r) return tree[i];
    ll m = (a+b)/2;
    node x = query(2*i, a, m, l, min(r, m));
    node y = query(2*i+1, m+1, b, max(l, m+1), r);
    if(x.any == NINF) return y; if(y.any==NINF) return x;
    return combine(x, y);
}

int n, q;
int main() {
    cin>>n>>q;
    f(i, n) cin>>nums[i];
    build(1, 0, n-1);
    int t, r, s;
    f(i, q) {
        cin>>t>>r>>s;
        if(t==1) {
            update(1, 0, n-1, r-1, s);
        } else {
            ll res = query(1, 0, n-1, r-1, s-1).any;
            if(res < 0) res = 0;
            cout<<res<<en;
        }
    }
    return 0;
}


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


#define N 200000
vll tree(4*N);
vll nums(N);
ll n, m, x;

void build(ll i, ll l, ll r) {
    if(l==r) tree[i] = nums[l];
    else {
        ll m = l+(r-l)/2;
        build(2*i, l, m);
        build(2*i+1, m+1, r);
        tree[i] = max(tree[2*i], tree[2*i+1]);
    }
}

// val is the amount to be subtraced off
void update(ll i, ll l, ll r, ll pos, ll val) {
    if(l==r) {
        tree[i] = val;
        nums[l] = val;
    } else {
        ll m = (l+r) / 2;
        if(pos <= m) update(2*i, l, m, pos, val);
        else update(2*i+1, m+1, r, pos, val);
        tree[i] = max(tree[2*i], tree[2*i+1]);
    }
}

// returns the pos
ll query(ll i, ll l, ll r, ll val) {
    if(tree[i] < val) return -1;
    if(l==r) return l;
    ll m = (r+l)/2;
    if(tree[2*i] >= val) return query(2*i, l, m, val);
    return query(2*i+1, m+1, r, val);
}

int main() {
    cin>>n>>m;
    f(i, n) cin>>nums[i];
    build(1, 0, n-1);

    vll queries(m);
    f(i, m) cin>>queries[i];
    for(ll x : queries) {
        ll idx = query(1, 0, n-1, x);
        if(idx == -1) {
            cout<<0<<en;
        } else {
            cout<<idx+1<<en;
            ll diff = nums[idx] - x;
            update(1, 0, n-1, idx, diff);
        }
    }
    return 0;
}


#define N 200000
int n;
vll nums(N);
vll tree(4*N);

void build(int i, int a, int b) {
    if(a==b) tree[i] = 1;
    else {
        int m = (a+b)/2;
        build(2*i, a, m);
        build(2*i+1, m+1, b);
        tree[i] = tree[2*i] + tree[2*i+1];
    }
}

// by default update to 0
void update(int i, int a, int b, int pos) {
    if(a==b) {
        if(tree[i] == 0) cout<<"HUH"<<en;
        tree[i] = 0;
    } else {
        int m = (a+b) / 2;
        if(pos <= m) update(2*i, a, m, pos);
        else update(2*i+1, m+1, b, pos);
        tree[i] = tree[2*i] + tree[2*i+1];
    }
}

int query(int i, int a, int b, int x) {
    if(a == b) return a;
    else {
        int m = (a+b)/2;
        if(x <= tree[2*i]) return query(2*i, a, m, x);
        return query(2*i+1, m+1, b, x - tree[2*i]);
    }
}

int main() {
    cin>>n;
    f(i, n) cin>>nums[i];
    build(1, 0, n-1);

    vll r(n);
    f(i, n) cin>>r[i];
    f(i, n) {
        int x = r[i];
        int idx = query(1, 0, n-1, x);
        cout<<nums[idx]<<en;
        update(1, 0, n-1, idx);
    }
    return 0;
}


#define N 200000
vll nums(N);
vll tree(4*N);
ll n, q, t, u, v;

void build(ll i, ll a, ll b) {
    if(a==b) tree[i] = nums[a];
    else {
        ll m = a+(b-a)/2;
        build(2*i, a, m);
        build(2*i+1, m+1, b);
        tree[i] = min(tree[2*i], tree[2*i+1]);
    }
}

void update(ll i, ll a, ll b, ll pos, ll val) {
    if(a==b) {
        tree[i] = val;
    } else {
        ll m = a+(b-a)/2;
        if(pos <= m) update(2*i, a, m, pos, val);
        else update(2*i+1, m+1, b, pos, val);
        tree[i] = min(tree[2*i], tree[2*i+1]);
    }
}

ll query(ll i, ll a, ll b, ll l, ll r) {
    if(l>r) return INF;
    if(a==l && b==r) return tree[i];
    ll m=a+(b-a)/2;
    return min(query(2*i, a, m, l, min(r, m)), query(2*i+1, m+1, b, max(l, m+1), r));
}

int main() {
    cin>>n>>q;
    f(i, n) cin>>nums[i];
    build(1, 0, n-1);
    f(i, q) {
        cin>>t>>u>>v;
        if(t==1) {
            update(1, 0, n-1, u-1, v);
        } else {
            cout<<query(1, 0, n-1, u-1, v-1)<<en;
        }
    }
    return 0;
}


#define N 200000
ll n, q;
vll nums(N);
vll tree(4*N);

void build(ll i, ll a, ll b) {
    if(a==b) {
        tree[i] = nums[a];
        return;
    }
    ll mid = a+(b-a)/2;
    build(2*i, a, mid);
    build(2*i+1, mid+1, b);
    tree[i] = tree[2*i] + tree[2*i+1];
}

void update(ll i, ll a, ll b, ll pos, ll x) {
    if(a==b) tree[i] = x;
    else {
        ll m = a+(b-a)/2;
        if(pos <= m) update(2*i, a, m, pos, x);
        else update(2*i+1, m+1, b, pos, x);
        tree[i] = tree[2*i]+tree[2*i+1];
    }
}

ll query(ll i, ll a, ll b, ll l, ll r) {
    if(l>r) return 0;
    if(a==l && b==r) return tree[i];
    ll m = a+(b-a)/2;
    return query(2*i, a, m, l, min(r, m)) + query(2*i+1, m+1, b, max(l,m+1), r);
}

int main() {
    cin>>n>>q;
    f(i, n) cin>>nums[i];

    build(1, 0, n-1);

    ll t, a, b;
    f(i, q) {
        cin>>t>>a>>b;
        if(t==1) {
            update(1, 0, n-1, a-1, b);
        } else {
            cout<<query(1, 0, n-1, a-1, b-1)<<en;
        }
    }
    return 0;
}


int main() {
    int n,q; cin>>n>>q;
    vi nums(n);
    f(i, n) cin>>nums[i];

    int ln = log2(n) + 1;
    vvi v(n, vi(ln, 0));
    f(i, n) v[i][0] = nums[i];
    for(int j = 1; (1<<j) <= n; ++j) {
        for(int i = 0; i+(1<<j) <= n; ++i) {
            v[i][j] = min(v[i][j-1], v[i+(1<<(j-1))][j-1]);
        }
    }
    int l, r;
    f(i, q) {
        cin>>l>>r; l--; r--;
        ln = log2(r-l+1);
        int res = min(v[l][ln], v[r-(1<<ln)+1][ln]);
        cout<<res<<en;
    }
    return 0;
}


#define N 200000
ll n,q,a,b;
vll nums(N+1, 0);
int main() {
    cin>>n>>q;
    f(i, n) cin>>nums[i+1];
    f(i, n) nums[i+1] ^= nums[i];
    f(i, q) {
        cin>>a>>b;
        ll res = nums[b] ^ nums[a-1];
        cout<<res<<en;
    }
    return 0;
}