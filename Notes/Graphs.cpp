// 2D Grids
int n, m; cin>>n>>m;
vvi grid(n, vi(m, 0)), vvi visited(n, vi(m, 0));
function<void(int, int)> bfs = [&](int y, int x)
    queue<pii> q;
    q.emplace(y, x); visited[y][x] = 1;
    while(!q.empty())
        auto [cy, cx] = q.front(); q.pop();
        for(auto [dy, dx] : dirs)
            int ny = dy + cy, nx = cx+dx;
            if(check(ny, nx, n, m) && grid[ny][nx] && !visited[ny][nx])
                q.emplace(ny, nx);
                visited[ny][nx] = 1;
int res = 0;
f(i, n) f(j, m)
        if(!visited[i][j] && grid[i][j]) bfs(i, j); res++;
cout<<res<<en;


// Usually, graphs are set up with adjacency list/matrix and distances. Keep track of visited/min dist during the traversal
vvpii adj(N); // node, weight

// Alternatively, compact information into:
struct Edge ...
vector<vector<Edge>> adj;

// Dijkstra space efficient (no vis) - better for if multiple ways of entering, unified way of removing stale entries
priority_queue<pii, vpii, greater<>> q;
vi dis(N, INF);
dis[a] = 0; pq.push({0, a});
while(!pq.empty())
    auto [d, u] = pq.top(); pq.pop();
    if(dis[u] < d) continue;
    if(u == b) return d;
    for(auto [v, dd] : adj[u])
        int nd = d+dd;
        if(nd < dis[v])
            dis[v] = nd;
            pq.push({nd, to});

// Dijkstra general (with vis) - A bit easier to understand and more broad usage
priority_queue<pll, vpll, greater<>> q;
vll dist(n+1, LLONG_MAX); vb vis(n+1, false);
q.push({0, 1}); dist[1]=0;
while(!q.empty())
    auto [d, u] = q.top(); q.pop();
    if(vis[u]) continue;
    vis[u]=true;
    for(auto [v, dd] : adj[u])
        ll nd=d+dd;
        if(nd<dist[v])
            dist[v]=nd;
            q.emplace(nd, v);


// Bellman-Ford
f(i, n-1)
    for(auto [u, v, w] : edges)
        int nw=dp[u]+w;
        if(nw < dp[v]) dp[v]=nw;
for(auto [u, v, w] : edges)
    if(dp[u]+w<dp[v])
        cout<<"Negative Cycle"<<en;

// Variant - Print Negative Cycle
vector<edge> edges(m);
vll dist(n+1, INFL); vi par(n+1, -1);
dist[1]=0; ll it=0;
f(j, n)
    f(i, m)
        auto [u, v, w] = edges[i];
        if(dist[u]+w < dist[v])
            par[v]=u;
            dist[v]=dist[u]+w;
            if(j==n-1) it=v;
if(it==0) cout<<"NO"; return 0;
f(i, n) it=par[it];
vll cycle;
while(true)
    cycle.push_back(it);
    if(it == cycle.front() && (int)cycle.size()>1) break;
    it=par[it];
reverse(all(cycle));

// Variant - Use DFS from start and end to limit options
vector<edge> edges;
void dfs(ll u, vvll& adj, vb& vis)
    if(vis[u]) return;
    vis[u]=true;
    for(int v : adj[u]) dfs(v, adj, vis);
vvll adj(n+1), radj(n+1);
vb vis(n+1), rvis(n+1);
dfs(1, adj, vis);
dfs(n, radj, rvis);
vll dp(n+1, INFL); dp[1]=0;
f(i, n)  // Relax weights - note order/liveliness doesn't matter due to timing
    bool valid=false;
    f(j, m)
        ll u=edges[j].u, v=edges[j].v, w= -edges[j].w; // Since we want positive weight cycle negate weight
        ll nw=dp[u]+w;
        if(nw < dp[v])
            valid=true;
            dp[v]=nw;
            if(i==n-1 && vis[v] && rvis[v]) cout<<-1<<en; return 0;
    if(!valid) break;
cout<<-dp[n]<<en;

// Floyd-Warshall
vvll dist(n+1, vll(n+1, INF));
f(i, m)
    ll u, v, w; cin>>u>>v>>w;
    dist[u][v]=min(dist[u][v], w);
    dist[v][u]=min(dist[v][u], w);
for(int i=1; i<=n; ++i) dist[i][i]=0;
for(int k=1; k<=n; ++k)
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=n; ++j)
            dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]); // If INF+x might overflow have INF check here


// Tarjan's algorithm - print critical edges / number of bridges
vvi adj;
vi early(N), vi low(N);
int time;
function<void(int, int)> dfs = [&](int u, int parent)
    time++;
    early[u] = low[u] = time;
    for(int v : adj[u])
        if(v == parent) continue;
        if(early[v] == -1)
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > early[u]) res.pb({u, v});
        else low[u] = min(low[u], early[v]);
f(i, N) if(early[i] == -1) bfs(i, -1);

// Articulation points - critical vertices instead
vvi adj; vi low, disc, p, ap; int time;
void dfs(int u)
    low[u] = disc[u] = ++time;
    int children = 0;
    for(int v : adj[u])
        if(!disc[v])
            p[v] = u; children++;
            dfs(v);
            low[u] = min(low[u], low[v]);
            if(p[u] == -1 && children > 1) ap[u] = 1; // Root case
            if(p[u] != -1 && low[v] >= disc[u]) ap[u] = 1; // Articulation point
        else if(v != p[u])
            low[u] = min(low[u], disc[v]);


// Union find
vi p, sz;
rep(i, 0, n) p[i] = i; rep(i, 0, n) sz[i] = 1;
int par(int x)
    if(p[x] == x) return x;
    return parent[x] == find(parent[x]);
void unite(int x, int y)
    int a = find(x), b = find(y);
    if(a==b) return;
    if(sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b]; p[b] = a;

// MST - Kruskal
vector<tuple<int, int, int>> edges; // (w, u, v)
sort(all(edges));
int tw = 0;
for(auto& [w, u, v] : edges)
    int a = par(u), b = par(v);
    if(a != b)
        unite(u, v);
        tw += w;

// MST - Prim
mpqq q;  // (weight, vertex)
q.emplace(0, 1); vb vis(n+1, false); int tw = 0;
while(!q.empty())
    auto [w, u] = q.top(); q.pop();
    if(vis[v]) continue; vis[v]=true; // Note vis check must (?) go here
    tw += w;
    for(auto &[v, weight] : adj[u])
        if(!vis[v]) q.emplace(weight, v);


// Min flow - general bfs for finding augmenting paths
vvi adj, fl;
vi par(n, -1);
auto bfs = [&](int a, int b)
    queue<pii> q;  //node, flow
    q.push({a, INF});
    while(!q.empty())
        auto [u, f] = q.front(); q.pop();
        for(int v : adj[u])
            if(par[v] != -1 || fl[u][v] == 0) continue;
            par[v] = u;
            int nf = min(f, fl[u][v]);
            if(v == b) return nf;
            q.push({v, nf});
    return 0;
auto maxflow = [&](int a, int b)
    int f = 0;
    int nf = 0;
    while(nf = bfs(a, b)) // break if nflow = 0;
        f += nf;
        int curr = b;
        while(curr != a)
            int prev = parent[curr];
            fl[prev][curr] -= nf;
            fl[curr][prev] += nf;
            curr = prev;
    return f;

// Extension: Dinic's for fast maximum flow
struct Edge
    int to, rev; ll cap;
class MaxFlow
    int n; vve adj;
    MaxFlow(int n) : n(n), adj(n + 1){}
    void add_edge(int u, int v, ll cap)
        adj[u].pb({v, (int)adj[v].size(), cap});
        adj[v].pb({u, (int)adj[u].size() - 1, 0});
    bool bfs_level(int s, int t, vi &lvl)
        fill(all(lvl), -1);
        queue<int> q;
        q.push(s); lvl[s] = 0;
        while(!q.empty())
            int u = q.front(); q.pop();
            for(auto &e : adj[u])
                if(e.cap > 0 && lvl[e.to] == -1)
                    lvl[e.to] = lvl[u] + 1;
                    q.push(e.to);
                    if(e.to == t) return true;
        return false;
    ll dfs_flow(int u, int t, ll flow, vi &lvl, vi &ptr)
        if(u == t) return flow;
        for(int &i = ptr[u]; i < adj[u].size(); ++i)
            Edge &e = adj[u][i];
            if(e.cap > 0 && lvl[e.to] == lvl[u] + 1)
                ll pushed = dfs_flow(e.to, t, min(flow, e.cap), lvl, ptr);
                if(pushed > 0)
                    e.cap -= pushed;
                    adj[e.to][e.rev].cap += pushed;
                    return pushed;
        return 0;
    ll max_flow(int s, int t)
        ll flow = 0;
        vi lvl(n + 1);
        while(bfs_level(s, t, lvl))
            vi ptr(n + 1, 0);
            while(ll pushed = dfs_flow(s, t, INF, lvl, ptr))
                flow += pushed;
        return flow;

// Minimum distance with discount on edges - use dp[n][k] and add k into pq.
vvi dp(n, vi(k+1, INF));  mpqq q;
q.insert(0, 1, k);
dp[1][k]=0;
while(!q.empty())
    auto [d, u, x] = q.top(); q.pop(); // x is coupons left
    if(dp[u][x] < d) continue; // This part is crucial for removing stale entries (see above, in place of visited arr)
    for(auto [v, dd] : adj[u])
        int nd=d+dd, ndd=d+dd/2;
        if(nd < dp[v][x])
            dp[v][x]=nd;
            q.emplace(nd, v, x);
        else if(x > 0 && ndd<dp[v][x-1])
            dp[v][x-1]=ndd;
            q.emplace(ndd, v, x-1);
cout<<dp[n][k]<<en;


// Find shortest K paths, maintain vector of pqs
vector<pq> best, vvpll adj, mpqq q;
best[1].push(0);
q.insert({0, 1});
while(!q.empty())
    auto [d, u] = q.top(); q.pop();
    for(auto [v, dd] = adj[u])
        int nd=d+dd;
        if(nd > best[v].top()) continue;
        if(best[v].size() < k)
            best[v].insert(nd);
            q.emplace(nd, v);
        else if(nd < best[v].top())
            best[v].pop(); best[v].insert(nd);
            q.emplace(nd, v);
reverse(all(best[n])); cout<<best[n];


// Binary lifting - find Kth parent
vvi dp[N+1][ln+1];
f(i, n) cin>>dp[i][0];
for(int j=1; j<=ln; ++j)
    for(int i=1; i<=n; ++i)
        dp[i][j] = dp[dp[i][j-1]][j-1];
f(i, q)
    cin>>x>>p;
    int i=0;
    while(p)
        if(p&1) x = par[x][i];
        i++; p>>=1;
    cout<<x<<en;

// Longest route - must use topo + simple dp
auto dfs = [&](int u)
    vis[u]=true;
    for(int v : adj[u])
        if(!vis[v]) dfs(v);
    order.pb(u);
vvpii adj, vi order, vi dp, vi par;
dfs(1->n), reverse(all(order));
for(int x : order)
    for(auto [v, w] : adj[u])
        int nw=dp[u]+w;
        if(nw > dp[v])
            dp[v]=nw; par[v]=u;
// Backtrack par to get longest path


// Find min dist, number of ways, mn and mx freq
vvpll adj, vll dist, ways, mn, mx, mpqq q;
while(!q.empty())
    auto [d, u] = q.top(); q.pop();
    if(dist[u]<d) continue;
    for(v : u)
        if(nd=dist[v])
            ways +=, mxmn max/min (u+1)
        else if(nd<dist[v])
            set ways, mn, mx
            set dist and emplace (nd, v)
cout<<dist[n]<<ways[n]<<mn[n]<<mx[n]


// Solving eulerian circuit (each edge once / reconstruct some sequence), use multiset if multiple edges
vvi adj; vi res;
void dfs(int a)
    while (!adj[a].empty()) // Get any adjacent node, erase edge, recurse next node
        int b = adj[a].back();
        adj[a].pop_back();
        dfs(b);
    res.pb(a);
reverse(all(res)); return res;

// Extension: Stack-based and handle undirected multigraphs
vvi adj; vi circ; stack<int> S; int start = 1;
f(u, n) if(adj[u].size())
    start = u; break;
S.push(start);
while(!S.empty())
    int u = S.top();
    if(adj[u].empty())
        circ.pb(u); S.pop();
    else
        int v = adj[u].back(); adj[u].pop_back();
        auto it = find(all(adj[v]), u);
        if(it != adj[v].end()) adj[v].erase(it);
        S.push(v);
bool eulerian = true;
f(u, n) if(!adj[u].empty()) eulerian = false;
if(eulerian) reverse(all(circ));