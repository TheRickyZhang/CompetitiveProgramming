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

int n, m, k;
int32_t main() {
    cin>>n>>m;
    vi c(n+1, -1);
    vi in(n+1, 0);
    vvi adj(n+1);
    f(i, m) {
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    f(i, n) {
        if(c[i+1] != -1) continue;
        queue<pii> q;
        q.emplace(i+1, 0); c[i+1] = 0;
        while(!q.empty()) {
            auto [u, p] = q.front(); q.pop();
            int other = 1-c[u];
            for(int v : adj[u]) {
                if(v==p || c[v] == other) continue;
                if(c[v] == c[u]) {
                    cout<<"IMPOSSIBLE"<<en;
                    return 0;
                }
                c[v] = other;
                q.emplace(v, u);
            }
        }
    }
    f(i, n) {
        cout<<c[i+1]+1<<" ";
    }
}


int N = 100001;
int n, m;
vvi adj(N);
vb visited(N, false);
int main() {
    cin>>n>>m;
    int u, v;
    f(i, m) {
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi res;
    auto bfs = [&](int a) {
        queue<int> q;
        q.push(a); visited[a] = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int v : adj[u]) {
                if(visited[v]) continue;
                visited[v] = true;
                q.push(v);
            }
        }
    };
    f(i, n) {
        if(!visited[i+1]) {
            bfs(i+1);
            res.pb(i+1);
        }
    }
    int sz = res.size();
    cout<<sz-1<<en;
    f(i,sz-1) {
        cout<<res[i+1]<<" "<<res[i]<<en;
    }
    return 0;
}

int n, m;
int main() {
    cin>>n>>m;
    vvi grid(n, vi(m, 0));
    string row;
    f(i, n) {
        cin>>row;
        f(j, m) {
            grid[i][j] = row[j]=='.';
        }
    }
    vvi visited(n, vi(m, 0));

    function<void(int, int)> bfs = [&](int y, int x) {
        queue<pii> q;
        q.emplace(y, x); visited[y][x] = 1;
        while(!q.empty()) {
            auto [cy, cx] = q.front(); q.pop();
            for(auto [dy, dx] : dirs) {
                int ny = dy + cy, nx = cx+dx;
                if(check(ny, nx, n, m) && grid[ny][nx] && !visited[ny][nx]) {
                    q.emplace(ny, nx);
                    visited[ny][nx] = 1;
                }
            }
        }
    };
    int res = 0;
    f(i, n) {
        f(j, m) {
            if(!visited[i][j] && grid[i][j]) {
                bfs(i, j);
                res++;
            }
        }
    }
    cout<<res<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    vvi adj(n);
    vi deg(n, 0);
    f(i, m) {
        int a, b; cin>>a>>b; a--; b--;
        deg[b]++; adj[a].pb(b);
    }
    vi res;
    queue<int> q;
    f(i, n) {
        if(deg[i]==0) q.push(i);
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        res.pb(u);
        for(int v : adj[u]) {
            if(--deg[v]==0) q.push(v);
        }
    }
    if(res.size() == n) {
        for(int x : res) cout<<x+1<<" ";
    } else {
        cout<<"IMPOSSIBLE"<<en;
    }
}


constexpr int N = 100000;
ll t, n, m, k, a, b;
typedef tuple<ll, ll, ll> edge;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    vector<edge> edges(m);
    f(i, m) {
        int u, v, w;
        cin>>u>>v>>w;
        edges[i]={u, v, w};
    }
    vll dist(n+1, INFL);
    vi par(n+1, -1);
    dist[1]=0;
    ll it=0;
    f(j, n) {
        f(i, m) {
            auto [u, v, w] = edges[i];
            if(dist[u]+w < dist[v]) {
                par[v]=u;
                dist[v]=dist[u]+w;
                if(j==n-1) it=v;
            }
        }
    }
    if(it==0) {
        cout<<"NO"; return 0;
    }
    f(i, n) {
        it=par[it];
    }
    vll cycle;
    while(true) {
        cycle.push_back(it);
        if(it == cycle.front() && (int)cycle.size()>1) break;
        it=par[it];
    }
    reverse(all(cycle));
    cout<<"YES"<<en;
    for(int x : cycle) cout<<x<<" ";
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    vector<vpll> adj(n+1);
    f(i, m) {
        int u, v, w;
        cin>>u>>v>>w;
        adj[u].pb({v, w});
        // adj[v].pb({u, w});
    }
    priority_queue<pll, vpll, greater<>> q;
    vll dist(n+1, LLONG_MAX); vb vis(n+1, false);
    q.push({0, 1}); dist[1]=0;
    while(!q.empty()) {
        auto [w, u] = q.top(); q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(auto [v, dw] : adj[u]) {
            ll nw=w+dw;
            if(nw<dist[v]) {
                dist[v]=nw;
                q.emplace(nw, v);
            }
        }
    }
    f(i, n) {
        cout<<dist[i+1]<<en;
    }
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    k=1;
    vector<vpll> adj(n+1);
    f(i, m) {
        ll u, v, w;
        cin>>u>>v>>w;
        adj[u].pb({v, w});
    }
    vvll dis(n+1, vll(k+1, INFL));
    dis[1][k]=0;
    priority_queue<node, vector<node>, greater<>> q; // dist, u, coupons left
    q.push({0, 1, k});

    while(!q.empty()) {
        auto [d, u, x] = q.top(); q.pop();
        if(dis[u][x] < d) continue;
        for(auto& [v, w] : adj[u]) {
            ll nd=d+w;
            if(nd < dis[v][x]) {
                dis[v][x]=nd;
                q.emplace(nd, v, x);
            }
            ll ndd=d+w/2;
            if(x > 0 && ndd < dis[v][x-1]) {
                dis[v][x-1]=ndd;
                q.emplace(ndd, v, x-1);
            }
        }
    }
    // for(auto v : dis) cout<<v<<en;
    cout<<*min_element(all(dis[n]))<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>m;
    vvi adj1(n+1), adj2(n+1);
    vb vis1(n+1, false), vis2(n+1, false);
    f(i, m) {
        int u, v; cin>>u>>v;
        adj1[u].pb(v);
        adj2[v].pb(u);
    }
    function<void(int, int, vvi&, vb&)> dfs=[&](int u, int p, vvi& adj, vb& vis) {
        vis[u]=true;
        for(int v : adj[u]) {
            if(v==p || vis[v]) continue;
            dfs(v, u, adj, vis);
        }
    };
    dfs(1, 0, adj1, vis1);
    dfs(1, 0, adj2, vis2);
    // cout<<vis1<<en<<vis2<<en;
    for(int i=1; i<=n; ++i) {
        if(vis1[i] && vis2[i]) continue;
        cout<<"NO"<<en;
        if(!vis1[i]) cout<<1<<" "<<i<<en;
        else cout<<i<<" "<<1<<en;
        return 0;
    }
    cout<<"YES"<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    vvi adj(n+1);
    f(i, m) {
        int u, v; cin>>u>>v;
        adj[u].pb(v);
    }
    vb vis(n+1, false); vll order;
    function<void(int)> dfs = [&](int u) {
        vis[u]=true;
        for(int v : adj[u]) {
            if(!vis[v]) dfs(v);
        }
        order.pb(u);
    };
    f(i, n) {
        if(!vis[i+1]) dfs(i+1);
    }
    reverse(all(order));
    vll dp(n+1, 0);
    dp[1]=1;
    for(ll u : order) {
        for(ll v : adj[u]) {
            dp[v] = (dp[v]+dp[u]) % MOD;
        }
    }
    cout<<dp[n]%MOD<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    vvpll adj(n+1);
    f(i, m) {
        int u, v, w; cin>>u>>v>>w;
        adj[u].pb({v, w});
    }

    vll dist(n+1, INFL), ways(n+1, 0), mn(n+1, INT_MAX), mx(n+1, INT_MIN);
    vb vis(n+1, false);
    mpqq q;
    dist[1]=0; ways[1]=1; mn[1]=mx[1]=0;
    q.push({0, 1});
    while(!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if(dist[u] < d) continue;
        for(auto [v, dd] : adj[u]) {
            ll nd=d+dd;
            if(nd == dist[v]) {
                ways[v]=(ways[v]+ways[u]) % MOD;
                mn[v]=min(mn[v], mn[u]+1);
                mx[v]=max(mx[v], mx[u]+1);
            } else if(nd < dist[v]) {
                ways[v]=ways[u];
                mn[v]=mn[u]+1; mx[v]=mx[u]+1;
                dist[v]=nd;
                q.emplace(nd, v);
            }
        }
    }
    cout<<dist[n]<<sp<<ways[n]<<sp<<mn[n]<<sp<<mx[n]<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m>>q;
    vvll dist(n+1, vll(n+1, 1e18));
    f(i, m) {
        ll u, v, w; cin>>u>>v>>w;
        dist[u][v]=min(dist[u][v], w);
        dist[v][u]=min(dist[v][u], w);
    }
    for(int i=1; i<=n; ++i) dist[i][i]=0;
    for(int k=1; k<=n; ++k) {
        for(int i=1; i<=n; ++i) {
            for(int j=1; j<=n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
            }
        }
    }
    f(i, q) {
        ll a, b; cin>>a>>b;
        if(dist[a][b] != 1e18) cout<<dist[a][b]<<en;
        else cout<<-1<<en;
    }
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    vvpii adj(n+1);
    f(i, m) {
        int u, v; cin>>u>>v;
        adj[u].pb({v, 1});
    }

    vb vis(n+1, false);
    vi order;
    function<void(int)> dfs=[&](int u) {
        vis[u]=true;
        for(auto [v, w] : adj[u]) {
            if(!vis[v]) dfs(v);
        }
        order.pb(u);
    };
    f(i, n) if(!vis[i+1]) dfs(i+1);
    reverse(all(order));

    vll dist(n+1, LLONG_MIN);
    vi par(n+1, 0);
    dist[1]=0; par[1]=1;
    for(int u : order) {
        if(dist[u]==LLONG_MIN) continue;
        for(auto [v, w] : adj[u]) {
            int nw=dist[u]+w;
            if(nw>dist[v]) {
                par[v]=u;
                dist[v]=nw;
            }
        }
    }
    if(dist[n]==LLONG_MIN) cout<<"IMPOSSIBLE"<<en;
    else {
        vi res;
        int it=n;
        while(it != par[it]) {
            res.pb(it);
            it=par[it];
        }
        res.pb(1);
        reverse(all(res));
        cout<<res.size()<<en;
        for(int x : res) cout<<x<<" ";
    }
}


int par[200001][31];
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, q; cin>>n>>q;
    f(i, n) cin>>par[i+1][0];
    for(int j=1; j<31; ++j) {
        for(int i=1; i<= n; ++i) {
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }
    f(_, q) {
        int x, p; cin>>x>>p;
        int i=0;
        while(p) {
            if(p&1) x = par[x][i];
            p>>=1; i++;
        }
        cout<<x<<en;
    }
}


using namespace std;
const int maxN = 2e5+1, logN = 20;

bool vis[maxN];
int N, Q, ds[maxN], d[maxN], comp[maxN], cyc[maxN], p[logN][maxN];
vector<int> cycleSeeds, G[maxN];

int find(int u){
    if(ds[u] < 0)   return u;
    ds[u] = find(ds[u]);
    return ds[u];
}

bool merge(int u, int v){
    u = find(u); v = find(v);
    if(u == v)  return false;
    if(ds[u] < ds[v])   swap(u, v);
    ds[v] += ds[u];
    ds[u] = v;
    return true;
}

void init_parents(){
    for(int i = 1; i < logN; i++)
        for(int j = 1; j <= N; j++)
            p[i][j] = p[i-1][p[i-1][j]];
}

int travel(int u, int k){
    int v = u;
    for(int i = logN-1; i >= 0; i--)
        if(k&(1<<i))
            v = p[i][v];
    return v;
}

void dfs(int u, int compID){
    vis[u] = true;
    comp[u] = compID;
    for(int v : G[u]){
        if(!vis[v]){
            d[v] = d[u]+1;
            dfs(v, compID);
        } else cyc[u] = d[u]+1;
        cyc[u] = max(cyc[u], cyc[v]);
    }
}

int query(int a, int b){
    if(a == b)  return 0;

    // Start and end are on different components
    if(comp[a] != comp[b])  return -1;

    // Start is on cycle
    if(cyc[a]){
        if(!cyc[b]) return -1;
        return (d[a]-d[b]+cyc[a]) % cyc[a];
    }

    // Start and end are on tree (must check if same tree)
    if(!cyc[b]){
        if(d[a] <= d[b])    return -1;
        int dist = d[a]-d[b];
        return (travel(a, dist) == b) ? dist : -1;
    }

    // Start is on tree and end is on cycle
    int root = a;
    for(int i = logN-1; i >= 0; i--){
        int par = p[i][root];
        if(!cyc[par])
            root = par;
    }
    root = p[0][root];

    return (d[a]-d[root]) + query(root, b);
}

int main(){
    scanf("%d %d", &N, &Q);
    fill(ds+1, ds+N+1, -1);
    for(int i = 1, x; i <= N; i++){
        scanf("%d", &x);
        p[0][i] = x;
        G[x].push_back(i);
        if(!merge(x, i))
            cycleSeeds.push_back(x);
    }

    init_parents();
    int compID = 1;
    for(int seed : cycleSeeds)
        dfs(seed, compID++);

    for(int i = 0, a, b; i < Q; i++){
        scanf("%d %d", &a, &b);
        printf("%d\n", query(a, b));
    }
}


int main() {
    cin>>n>>m;
    vvi adj(n+1);
    int a, b;
    f(i, m) {
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    queue<int> q;
    vi prev(n+1, -1);
    q.push(1); prev[1] = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : adj[u]) {
            if(prev[v]>0) continue;
            prev[v] = u;
            q.push(v);
            if(v==n) {
                vi res;
                while(v!=1) {
                    res.pb(v);
                    v = prev[v];
                }
                res.pb(1);
                reverse(all(res));
                cout<<res.size()<<endl;
                for(int x : res) cout<<x<<" ";
                return 0;
            }
        }
    }
    cout<<"IMPOSSIBLE"<<en;
    return 0;
}


const int N = 1000;
char grid[N][N];
pii par[N][N];
char dir[N][N];
bool vis[N][N];
int n, m;

int main() {
    cin>>n>>m;
    pii s, e;
    f(i, n) f(j, m) {
        cin>>grid[i][j];
        if(grid[i][j] == 'A') s = {i, j};
        if(grid[i][j] == 'B') e = {i, j};
    }

    queue<pii> q;
    q.push(s);
    vis[s.first][s.second] = true;

    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if(x == e.first && y == e.second) {
            str path;
            while(make_pair(x, y) != s) {
                path += dir[x][y];
                tie(x, y) = par[x][y];
            }
            reverse(all(path));
            cout<<"YES\n"<<path.size()<<en<<path<<en;
            return 0;
        }

        f(i, 4) {
            int nx = x + dirs[i].first, ny = y + dirs[i].second;
            if(check(nx, ny, n, m) && !vis[nx][ny] && grid[nx][ny] != '#') {
                vis[nx][ny] = true;
                par[nx][ny] = {x, y};
                dir[nx][ny] = "DLRU"[i];
                q.push({nx, ny});
            }
        }
    }

    cout<<"NO\n";
    return 0;
}


int n, m;
const int N = 100005;
int vis[N], p[N];
vvi adj(N);

void dfs(int u, int par) {
    vis[u] = 1;
    p[u] = par;
    for (int v : adj[u]) {
        if (v == par) continue; // Skip the parent
        if (vis[v]) { // Cycle detected
            vi res;
            int x = u;
            while (x != v) {
                res.pb(x);
                x = p[x];
            }
            res.pb(v);
            res.pb(res[0]);
            cout << res.size() << en;
            for (int x : res) cout << x + 1 << " ";
            exit(0);
        }
        if (!vis[v]) {
            dfs(v, u);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs(i, -1);
    }
    cout << "IMPOSSIBLE\n";
}


const int N = 100005;
int n, m;
int state[N], par[N];
vector<int> adj[N];
int startNode = -1, endNode = -1;

bool dfs(int u) {
    state[u] = 1; // Mark as visiting
    for (int v : adj[u]) {
        if (state[v] == 0) {
            par[v] = u;
            if (dfs(v)) return true;
        } else if (state[v] == 1) {
            // Found a back edge, cycle detected
            startNode = v;
            endNode = u;
            return true;
        }
    }
    state[u] = 2; // Mark as done
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    fill(par, par + n + 1, -1);

    for (int i = 1; i <= n; i++) {
        if (state[i] == 0 && dfs(i)) {
            vector<int> cycle;
            cycle.push_back(startNode);
            for (int cur = endNode; cur != startNode; cur = par[cur]) {
                cycle.push_back(cur);
            }
            cycle.push_back(startNode);
            reverse(cycle.begin(), cycle.end());
            cout << cycle.size() << "\n";
            for (int x : cycle) cout << x << " ";
            cout << "\n";
            return 0;
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}


constexpr int N = 100000;
ll t, n, m, k, a, b;

struct edge {
    ll u, v, w;
    edge() : u(0), v(0), w(0) {}
    edge(ll u, ll v, ll w) : u(u), v(v), w(w) {}
};
vector<edge> edges;

void dfs(ll u, vvll& adj, vb& vis) {
    if(vis[u]) return;
    vis[u]=true;
    for(int v : adj[u]) {
        dfs(v, adj, vis);
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    vvll adj(n+1), radj(n+1);
    vb vis(n+1), rvis(n+1);
    edges.resize(m);
    f(i, m) {
        int u, v, w; cin>>u>>v>>w;
        adj[u].pb(v);
        radj[v].pb(u);
        edges[i] = edge(u, v, -w);
    }
    dfs(1, adj, vis);
    dfs(n, radj, rvis);
    // cout<<adj<<en<<radj<<en;

    vll dp(n+1, INFL);
    dp[1]=0;
    f(i, n) {  // Relax weights - note order/liveliness doesn't matter due to timing
        bool valid=false;
        f(j, m) {
            ll u=edges[j].u, v=edges[j].v, w= edges[j].w; // Since we want positive weight cycle negate weight
            ll nw=dp[u]+w;
            if(nw < dp[v]) {
                valid=true;
                dp[v]=nw;
                if(i==n-1 && vis[v] && rvis[v]) {
                    cout<<-1<<en; return 0;
                }
            }
        }
        if(!valid) break;
    }
    cout<<-dp[n]<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m>>k;
    vvpii adj(n+1);
    vector<pq> best(n+1); // We want a MAX queue since we want the K MIN values
    f(i, m) {
        int u, v, w; cin>>u>>v>>w;
        adj[u].pb({v, w});
    }

    best[1].push(0);
    priority_queue<pll, vpll, greater<>> q; // Weight, node
    q.push({0, 1});
    while(!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if(d > best[u].top()) continue; // Note that if u is in the queue then best[u] is not empty
        for(auto [v, dd] : adj[u]) {
            ll nd=d+dd;
            if(best[v].size() < k) {
                best[v].push(nd);
                q.emplace(nd, v);
            } else if(nd < best[v].top()) {
                best[v].pop();
                best[v].push(nd);
                q.emplace(nd, v);
            }
        }
    }
    vll res;
    auto& b=best[n];
    while(!b.empty()) {
        res.pb(b.top());
        b.pop();
    }
    reverse(all(res));
    for(ll x : res) cout<<x<<" ";
}