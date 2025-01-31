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

struct st {
    ll h, w, i;
};

bool cmp(st a, st b){
    if(a.h == b.h) return a.w > b.w;
    return a.h < b.h;
}

void solve(int tc){
    int n; cin >> n;
    vector<st> v(n);
    f(i, n){
        cin >> v[i].h >> v[i].w;
        if(v[i].h < v[i].w){
            swap(v[i].h, v[i].w);
        }
        v[i].i = i;
    }
    sort(all(v), cmp);
    vi overlap(n, -1);
    int x = v[0].i, y = v[0].w;
    // The overlapping v for a given i is the v with the minimum width for a given prefix
    for(int i=1; i<n; i++){
        if(v[i].w > y){
            overlap[v[i].i] = x;
        } else {
            x = v[i].i;
            y = v[i].w;
        }
    }
    f(i, n)cout << overlap[i]+1 << " ";
    cout << en;
}

int main(){
    int t; cin >> t;
    f(i, t) solve(i);
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ifstream cin("fenceplan.in");
    ofstream cout("fenceplan.out");
    cin>>n>>m;
    vpii pos(n);
    f(i, n) cin>>pos[i].ff>>pos[i].ss;
    vvi adj(n);
    f(i, m) {
        int u, v; cin>>u>>v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }
    vb vis(n, false);
    function<void(int, int&, int&, int&, int&)> dfs=[&](int u, int& lx, int&rx, int&ly, int& ry) {
        vis[u]=true;
        auto [x, y] = pos[u];
        lx=min(lx, x); rx=max(rx, x);
        ly=min(ly, y); ry=max(ry, y);
        for(int v : adj[u]) {
            if(!vis[v]) dfs(v, lx, rx, ly, ry);
        }
    };
    int res=INT_MAX;
    f(i, n) {
        if(vis[i]) continue;
        int lx=INT_MAX, rx=INT_MIN, ly=INT_MAX, ry=INT_MIN;
        dfs(i, lx, rx, ly, ry);
        // cout<<lx<<sp<<rx<<sp<<ly<<sp<<ry<<en;
        res=min(res, 2*(rx-lx+ry-ly));
    }
    cout<<res<<en;
}


int main() {
    ifstream cin("revegetate.in"); ofstream cout("revegetate.out");
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>m;
    vi p(n);
    f(i, n) p[i]=i;
    vi sz(n, 1);

    function<int(int)> par = [&](int u) {
        if(p[u]==u) return u;
        return p[u]=par(p[u]);
    };
    function<void(int, int)> merge = [&](int a, int b) {
        int x = par(a), y = par(b);
        if(x==y) return;
        if(sz[x] < sz[y]) swap(x, y);
        sz[x] += sz[y];
        p[y]=x;
    };

    f(i, m) {
        string s; cin>>s;
        cin>>a>>b; a--; b--;
        merge(a, b);
    }
    // cout<<p<<en;
    set<int> s;
    f(i, n) s.insert(par(i));
    cout<<1<<string(s.size(), '0')<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>k;
    vi nums(n, 0);
    f(i, k) {
        int l, r; cin>>l>>r; l--; r--;
        nums[l]++;
        if(r < n-1) nums[r+1]--;
    }
    f(i, n-1) nums[i+1] += nums[i];
    sort(all(nums));
    cout<<nums[n/2]<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ifstream cin("hps.in"); ofstream cout("hps.out");
    cin>>n; vi nums(n);
    f(i, n) {
        char c; cin>>c;
        if(c=='P') nums[i]=0;
        else if(c=='H') nums[i]=1;
        else nums[i]=2;
    }
    vi pre(n, 0), post(n, 0);

    int a=0, b=0, c=0;
    f(i, n) {
        if(nums[i]==0) b++;
        else if(nums[i]==1) c++;
        else a++;
        pre[i] = max({a, b, c});
    }
    a=0, b=0, c=0;
    repr(i, n, 0) {
        if(nums[i]==0) b++;
        else if(nums[i]==1) c++;
        else a++;
        post[i] = max({a, b, c});
    }
    // cout<<pre<<en<<post<<en;
    int res=max(post[0], pre[n-1]);
    f(i, n-1) res = max(res, pre[i]+post[i+1]);
    cout<<res<<en;
}


int main() {
    setIO("lifeguards");
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    vpii nums(n);
    f(i, n) {
        int l, r; cin>>l>>r;
        nums[i]={l, r};
    }
    sort(all(nums));

    // Calc total time without double counting
    int tot=0;
    int a=0, b=0;
    for(auto [l, r] : nums) {
        if(r > b) {
            a=max(b, l);
            tot+=r-a;
            b=r;
        }
    }

    // Calculate alone time via sorted intervals for 0 and n-1 edge, then 1->n-2
    int res = tot; // alone time
    res = min(res, min(nums[1].ff, nums[0].ss) - nums[0].ff);
    res = min(res, nums[n-1].ss - max(nums[n-2].ss, nums[n-1].ff));
    for(int i=1; i<n-1; ++i) {
        res = min(res, min(nums[i+1].ff, nums[i].ss) - max(nums[i].ff, nums[i-1].ss));
    }
    res = max(res, 0);
    // cout<<tot<<SP<<res<<en;
    cout<<tot-res<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    setIO("milkvisits");
    cin>>n>>m;
    vi col(n);
    string s; cin>>s;
    f(i, n) {
        col[i] = (s[i] =='H') ? 1 : 0;
    }
    vvi adj(n);
    f(i, n-1) {
        int u, v; cin>>u>>v; u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vvi parts;
    vi type(n, -1);
    f(i, n) {
        if(type[i]!=-1) continue;
        queue<pii> q; q.emplace(i, -1);
        int c=col[i];
        while(!q.empty()) {
            auto [u, p] = q.front(); q.pop();
            type[u] = i;
            for(int v : adj[u]) {
                if(col[v] != c || v==p) continue;
                q.emplace(v, u);
            }
        }
    }
    f(i, m) {
        int u, v; char c;
        cin>>u>>v>>c; u--; v--;
        int t = (c=='H') ? 1 : 0;
        cout<<(type[u]==type[v] && col[u]!=t ? "0" : "1");
    }
}


constexpr int N = 100000;
ll t, n, m, k, a, b;
vll p, sz;
ll par(int x) {
    if(p[x]==x) return x;
    return p[x]=par(x);
}
void unite(int x, int y) {
    ll a=par(x), b=par(y);
    if(a==b) return;
    if(sz[a]<sz[b]) swap(a, b);
    sz[a]+=sz[b]; p[b]=a;
}

typedef tuple<ll, ll, ll> edge;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    vvpll adj(n);
    vpll points;
    f(i, n) {
        ll a, b; cin>>a>>b;
        f(j, points.size()) {
            auto [x, y]=points[j];
            ll d=(a-x)*(a-x) + (b-y)*(b-y);
            adj[i].pb({j, d});
            adj[j].pb({i, d});
        }
        points.pb({a, b});
    }
    // for(auto v : adj) cout<<v<<en;

    mpqq q; vb vis(n, false);
    q.emplace(0, 0); ll res=0;
    while(!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if(vis[u]) continue; vis[u]=true;
        res=max(res, d);
        for(auto[v, dd] : adj[u]) {
            if(!vis[v]) q.emplace(dd, v);
        }
    }
    cout<<res<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    setIO("mootube");
    cin>>n>>t;
    vvpii adj(n);
    f(i, n-1) {
        int u, v, w; cin>>u>>v>>w;
        u--; v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    f(i, t) {
        int k, u; cin>>k>>u;
        queue<tuple<int,int,int>> q;
        q.push({u-1, -1, INF}); // node, parent, MIN
        int res=0;
        while(!q.empty()) {
            auto [u, p, w] = q.front(); q.pop();
            if(w >= k && w != INF) res++;
            for(auto [v, nw] : adj[u]) {
                if(v==p) continue;
                q.emplace(v, u, min(w, nw));
            }
        }
        cout<<res<<en;
    }
}


int main() {
    setIO("mountains");
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    vpii nums(n);
    f(i, n) {
        int a, b; cin>>a>>b;
        nums[i] = {a-b, a+b};
    }
    sort(all(nums), [&](pii& a, pii& b) {
        if(a.ff == b.ff) return a.ss > b.ss;
        return a.ff < b.ff;
    });
    int mx=0, res=0;
    for(auto [l, r] : nums) {
        if(r > mx) {
            mx=r; res++;
        }
    }
    cout<<res<<en;
}


int main() {
    setIO("sort");
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    vpii nums(n);
    f(i, n) {
        cin>>nums[i].ff; nums[i].ss=i;
    }
    sort(all(nums)); // Want to find the most "out of order" elements
    ll res=0;
    f(i, n) {
        res=max(res, 1LL * (nums[i].ss - i));
    }
    cout<<res+1<<en;
}


int n, k;
int main(){
    ifstream cin("paintbarn.in");
    ofstream cout("paintbarn.out");
    int n,k;
    cin>>n>>k;
    const int N=200;
    vvi brn(N,vi(N,0));
    f(_,n){
        int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
        for(int y=y1;y<y2;y++){
            brn[y][x1]++;
            if(x2<N) brn[y][x2]--;
        }
    }
    f(r,N){
        int sf=0;
        f(c,N){
            sf+=brn[r][c];
            brn[r][c]=sf;
        }
    }
    vvi lfto(N,vi(N,0));
    int ra=0; // rn_amt
    f(r,N){
        f(c,N){
            if(brn[r][c]==k){
                lfto[r][c]=-1;
                ra++;
            } else if(brn[r][c]==k-1){
                lfto[r][c]=1;
            }
        }
    }
    // 2D prefix sums for lfto => plft
    vvi plft(N+1,vi(N+1,0));
    for(int r=1;r<=N;r++){
        for(int c=1;c<=N;c++){
            plft[r][c]=plft[r-1][c]+plft[r][c-1]-plft[r-1][c-1]+lfto[r-1][c-1];
        }
    }
    auto rsum=[&](int fr,int fc,int tr,int tc){
        return plft[tr+1][tc+1] - plft[fr][tc+1] - plft[tr+1][fc] + plft[fr][fc];
    };
    // top/bot/left/right best arrays
    vi top(N),bot(N),lft(N),rht(N);
    // 2D "Kadane" for all col splits
    f(st,N){
        for(int ed=st;ed<N;ed++){
            int ts=0,ls=0,rc=0;
            for(int i=1;i<N;i++){
                rc=ts+rsum(i-1,st,i-1,ed);
                top[i]=max(top[i],ts=max(0,rc));
                rc=ls+rsum(st,i-1,ed,i-1);
                lft[i]=max(lft[i],ls=max(0,rc));
            }
            int bs=0,rs=0;
            for(int i=N-1;i>=1;i--){
                rc=bs+rsum(i,st,i,ed);
                bot[i]=max(bot[i],bs=max(0,rc));
                rc=rs+rsum(st,i,ed,i);
                rht[i]=max(rht[i],rs=max(0,rc));
            }
        }
    }
    // cumulative maxima
    for(int i=1;i<N;i++){
        top[i]=max(top[i],top[i-1]);
        lft[i]=max(lft[i],lft[i-1]);
    }
    for(int i=N-2;i>=0;i--){
        bot[i]=max(bot[i],bot[i+1]);
        rht[i]=max(rht[i],rht[i+1]);
    }
    // best combination
    int mp=0; // max_paintable
    f(i,N){
        mp=max(mp,top[i]+bot[i]);
        mp=max(mp,lft[i]+rht[i]);
    }
    cout<<ra+mp<<en;
}


int main() {
    setIO("pairup");
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    vpii nums(n);
    f(i, n) cin>>nums[i].ss>>nums[i].ff;
    sort(all(nums));
    int l=0, r=n-1;
    int res=0;
    while(l < r) {
        res=max(res, nums[l].ff+nums[r].ff);
        if(nums[l].ss == nums[r].ss) {
            l++; r--;
        } else {
            if(nums[l].ss > nums[r].ss) {
                nums[l].ss -= nums[r].ss;
                r--;
            } else {
                nums[r].ss -= nums[l].ss;
                l++;
            }
        }
    }
    cout<<res<<en;
}


typedef pair<int, int> Point;
bool ycomp(Point p, Point q) { return p.second < q.second; }

const int MAX_N = 2500;
int pref[MAX_N + 1][MAX_N + 1];
Point p[MAX_N];

int rsum(int x1, int y1, int x2, int y2) {
    return pref[x2 + 1][y2 + 1] - pref[x2 + 1][y1] - pref[x1][y2 + 1] + pref[x1][y1];
}

int main(void) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p[i] = make_pair(x, y);
    }

    sort(p, p + n);
    for (int i = 0; i < n; i++) { p[i].first = i + 1; }
    sort(p, p + n, ycomp);
    for (int i = 0; i < n; i++) { p[i].second = i + 1; }

    for (int i = 0; i < n; i++) { pref[p[i].first][p[i].second] = 1; }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }
    long long answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int x1 = min(p[i].first, p[j].first) - 1;
            int x2 = max(p[i].first, p[j].first) - 1;
            answer += rsum(0, i, x1, j) * rsum(x2, i, n - 1, j);
        }
    }

    cout << answer + 1 << endl;
}

int N;
bitset<501> reachable[501];
vector<int> gifts[501];

void calc_reachable_floyd() {
    for (int i = 1; i <= N; ++i)
        for (int g : gifts[i])
            reachable[i][g] = true;
    for (int k = 1; k <= N; ++k) // run floyd-warshall
        for (int i = 1; i <= N; ++i)
            if (reachable[i][k])
                reachable[i] |= reachable[k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    assert(N <= 500);
    for (int i = 1; i <= N; ++i) {
        gifts[i].resize(N);
        for (int &g : gifts[i])
            cin >> g;
        while (gifts[i].back() != i)
            gifts[i].pop_back();
    }

    calc_reachable_floyd();

    for (int i = 1; i <= N; ++i)
        for (int g : gifts[i])
            if (reachable[g][i]) {
                cout << g << "\n";
                break;
            }
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    freopen("rental.in", "r", stdin);
    freopen("rental.out", "w", stdout);

    int n, m, r; cin >> n >> m >> r;
    vector<int> milk(n);
    for (int i = 0; i < n; i++) cin >> milk[i];
    sort(milk.begin(), milk.end(), greater<int>());

    vector<pair<int,int>> shops(m);
    for (int i = 0; i < m; i++) cin >> shops[i].second >> shops[i].first;
    sort(shops.begin(), shops.end(), greater<pair<int,int>>());

    vector<int> rentArr(r);
    for (int i = 0; i < r; i++) cin >> rentArr[i];
    sort(rentArr.begin(), rentArr.end(), greater<int>());

    // prefix sums for renting
    vector<long long> rentPS(r+1,0LL);
    for (int i = 1; i <= r; i++)
        rentPS[i] = rentPS[i-1]+rentArr[i-1];

    // prefix sums for selling
    vector<long long> sellPS(n+1,0LL);
    {
        int shopIndex=0;
        long long money=0;
        for (int i = 0; i < n; i++) {
            int amt = milk[i];
            while (shopIndex<m && amt>0) {
                int use = min(amt, shops[shopIndex].second);
                amt -= use;
                money += (long long)use * shops[shopIndex].first;
                shops[shopIndex].second -= use;
                if (shops[shopIndex].second == 0) shopIndex++;
            }
            sellPS[i+1]=money;
        }
    }

    long long ans=0;
    // Try all splits: first i cows sell, rest rent
    for (int i = 0; i <= min(n, r); i++) {
        ans = max(ans, sellPS[n-i] + rentPS[i]);
    }

    cout<<ans<<"\n";
}


int n;
ll res=0;
vpll nums;
ll search() {
    sort(all(nums));
    vpll pre(n), suf(n); // min/mx y-coords, since nums is sorted by x-coords
    auto upd = [](const pll& a, ll b) {
        return make_pair(min(a.ff, b), max(a.ss, b)); // Updates the min/max with a new y-coord
    };
    pre[0]={nums[0].ss, nums[0].ss};
    f(i, n-1) pre[i+1] = upd(pre[i], nums[i+1].ss);

    suf[n-1]={nums[n-1].ss, nums[n-1].ss};
    repr(i, n-1, 0) suf[i]=upd(suf[i+1], nums[i].ss);

    ll area = (nums[n-1].ff - nums[0].ff) * (pre[n-1].ss - pre[n-1].ff);

    ll res=INFL;
    f(i, n-1) {
        if(nums[i].ff == nums[i+1].ff) continue;
        ll r1=(nums[i].ff-nums[0].ff) * (pre[i].ss - pre[i].ff);
        ll r2=(nums[n-1].ff-nums[i+1].ff) * (suf[i+1].ss - suf[i+1].ff);
        res=min(res, r1+r2);
    }
    // cout<<pre<<en<<suf<<en;
    // cout<<area<<SP<<res<<en;
    return area-res;
}

int main() {
    setIO("split");
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    nums.assign(n, pii());
    f(i, n) cin>>nums[i].ff>>nums[i].ss;
    ll res=0;
    res=max(res, search());
    for(pll& x : nums) swap(x.ff, x.ss);
    res=max(res, search());
    cout<<res<<en;
}


constexpr int N = 100000;
ll t, n, m, k, a, b;

struct cow {
    int x; int y; int id;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    vector<cow> vn, ve;
    f(i, n) {
        char c; int x, y;
        cin>>c>>x>>y;
        if(c=='N') vn.pb({x, y, i});
        else ve.pb({x, y, i});
    }
    // Note that if we are processing east, north in i-j looping
    // To make sure we consider earlier possible intersections first,
    // sort east directions PRIMARILY ascending height then SECONDARILY width
    // This logic holds for up-down by symmetry
    /*
     * ------------> (3)
     *
     * -->(2) --->(1) // This can intersect the earliest possible
     */
    sort(all(vn), [&](cow& a, cow& b) {
        if(a.x==b.x) return a.y<b.y;
        return a.x<b.x;
    });
    sort(all(ve), [&](cow& a, cow& b) {
       if(a.y==b.y) return a.x<b.x;
        return a.y<b.y;
    });
    vb stop(n, false);
    vi blame(n, 0);  // Dfs-like, since we go reverse topologically no need to reverse
    for(auto& a : ve) {
        for(auto& b : vn) {
            if(stop[a.id] || stop[b.id] || b.y > a.y || a.x > b.x) continue;
            int dx = b.x-a.x, dy=a.y-b.y;
            if(dy < dx) {
                stop[a.id]=true;
                blame[b.id]+=blame[a.id]+1;
            } else if(dx < dy) {
                stop[b.id]=true;
                blame[a.id]+=blame[b.id]+1;
            } // else: skip per problem requirements
        }
    }
    f(i, n) cout<<blame[i]<<en;
}


constexpr int N = 100000;
ll t, n, m, k, a, b;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ifstream cin("div7.in"); ofstream cout("div7.out");
    cin>>n;
    vll nums(n+1, 0); f(i, n) cin>>nums[i+1];
    f(i, n) nums[i+1] = (nums[i+1] + nums[i]) % 7; // Prefix
    vll mp(7, -1); mp[0]=0;
    ll res = 0;
    for(int i = 1; i<=n; ++i) {
        ll c = nums[i];
        if(mp[c] != -1) res=max(res, i-mp[c]);
        if(mp[c]==-1) mp[c] = i;
    }
    cout<<res<<en;
}


// Better solution - instead of doing this weird difference array, do prefix from 1->n on min=(pre[i+k]-pre[i])
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ifstream cin("maxcross.in"); ofstream cout("maxcross.out");
    cin>>n>>k>>m;
    vi nums(m); f(i, m) cin>>nums[i];
    if (!binary_search(all(nums), 1)) nums.pb(1);
    if (!binary_search(all(nums), n)) nums.pb(n);
    sort(all(nums));
    m=nums.size();
    vi diff(m-1);
    f(i, m-1) diff[i] = nums[i+1]-nums[i];

    // cout<<diff<<en;
    // Two pointer for smallest length subarray sum k+1 (due to nature of problem)
    int l = 0, r=0, curr=diff[0], res=INF;
    while(r < m-1) {
        if(r<l) r++;
        else {
            if(curr>=k+1) {
                res = min(res, r-l);
                curr-=diff[l++];
            } else {
                curr+=diff[++r];
            }
        }
    }
    cout<<res<<en;
}

vi p, sz;
int par(int x) {
    if(x==p[x]) return x;
    return p[x]=par(p[x]);
}
void unite(int x, int y) {
    int a=par(x), b=par(y);
    if(a==b) return;
    if(sz[a]<sz[b]) swap(a, b);
    sz[a]+=sz[b]; p[b]=a;
}
typedef tuple<int, int, int> edge;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ifstream cin("wormsort.in"); ofstream cout("wormsort.out");
    cin>>n>>m;
    vi pos(n);
    f(i, n) {
        cin>>pos[i]; pos[i]--;
    }
    bool early=true;
    f(i, n) if(pos[i]!= i) early=false;
    if(early) { cout<<-1<<en; return 0; }
    vector<edge> edges;
    f(i, m) {
        int u, v, w; cin>>u>>v>>w; u--; v--;
        edges.pb({w, u, v});
    }
    sort(rall(edges));
    int l=1, r=1e9;
    while(l < r) {
        // cout<<l<<" "<<r<<en;
        int mid=l+(r-l)/2;
        p.assign(n, 0); sz.assign(n, 1); f(i, n) p[i]=i;
        bool valid=true;
        for(auto [w, u, v] : edges) {
            // cout<<w<<" "<<u<<" "<<v<<en;
            if(w<mid) break; unite(u, v);
        }
        // f(i, n) cout<<par(i)<<" "<<par(pos[i])<<en;
        // cout<<en;
        f(i, n) {
            if(par(i) != par(pos[i])) {
                valid=false; break;
            }
        }
        if(!valid) {
            r=mid;
        } else {
            l=mid+1;
        }
    }
    cout<<l-1<<en;
}