// Count Subtree Size (including self)
void dfs(int u, int p)
    sz[u]=1;
    for(int v : tree[u])
        if(v==p) continue;
        dfs(v, u); sz[u] += sz[v];

// Example: Find centroid of tree
int centroid(int u, int p)
    for(int v : tree[u])
        if(v != p && sz[v] > n/2) return centroid(v, u);
    return u;


// Make maximum pairs in tree
void dfs(int u, int p)
    for(int v : adj[u])
        if(v != p) dfs(v, u)
    if(p != -1 && !vis[u] && !vis[p])
        vis[u]=vis[p]=true;
        res++;


// Tree Diameter
function bfs = [&](int a)
    queue<pii> q;
    q.push({a, -1});
    int lvl = 0, node = -1;
    while(!q.empty())
        int sz = q.size();
        f(i, sz)
            auto [u, p]=q.front(); q.pop(); node = u;
            for(int v : adj[u])
                if(v==p) continue;
                q.emplace(v, u);
        lvl++;
    pii res={node, lvl-1};
    return res;
auto [furthest, d1] = bfs(1);
auto [f1, diam] = bfs(furthest);

// Example: Find maximum distance from each node
while(!q.empty())
    int sz = q.size();
    f(i, sz)
        int u = q.front(); q.pop(); f = u;
        for(int v : adj[u])
            if(vis[v]) continue; vis[v] = true;
            if(!dist.empty()) dist[v] = d;
            q.push(v);
    d++;
int x = bfs(0, empty);
int y = bfs(x, distx);
bfs(y, disty);
f(i, n) cout<<max(distx[i], disty[i])<<" ";

// Extension: sum of distances to all others
vvll adj(N);
vll in(N, 0), out(N, 0), sz(N, 0); // sum parents, sum children, size of subtree
void in_dfs(ll u, ll p)
    sz[u] = 1;
    for(ll v : adj[u])
        if(v==p) continue;
        in_dfs(v, u);
        sz[u] += sz[v];
        in[u] += in[v] + sz[v];
void out_dfs(ll u, ll p)
    // Simplified from out[u] = (out[p] + (n-sub[p]+1) + (in[par]-in[u]-sub[u]) + (sub[p]-sub[u]-1)
    // out from (parent) + (up parent->root) + (siblings->par) + (down parent->root)
    if(p >= 0) out[u] = n+out[p]+in[p]-in[u]-2*sz[u];
    for(ll v : adj[u])
        if(v != p) out_dfs(v, u);
in_dfs(0, -1);
out_dfs(0, -1);
f(i, n) cout<<in[i]+out[i]<<en;


// Binary Lifting
for(int i = 2; i <= n; ++i) cin>>p[i][0];
for(int j = 1; j < ln; ++j)
    for(int i = 1; i <= n; ++i)
        p[i][j] = p[p[i][j-1]][j-1];
f(i, q)
    f(j, ln) if(k & (1<<j)) x = p[x][j];

// Extension: Lowest Common Ancestor
queue<pii> qq; int d=0;
qq.emplace(1, 0);
while(!qq.empty())
    int sz = qq.size();
    f(i, sz)
        auto [u, p] = qq.front(); qq.pop();
        depth[u] = d; // Populate depths after binary lifting
        for(int v : adj[u])
            if(v==p) continue;
            qq.emplace(v, u);
    d++;
int query(int a, int b)
    if(depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    f(i, ln) if(diff & (1<<i)) a = par[a][i];
    if(a==b) return a;
    for(int i = ln-1; i>=0; --i) // Must decreasing steps to know for sure
        if(par[a][i] != par[b][i])
            a = par[a][i]; b = par[b][i];
    return par[a][0]; // since we track based on diff parent return one above

// + Distance between nodes
cout << depth[a] + depth[b] - 2*depth[lca] << endl;


// Euler tour: Flatten tree to array
ll t=0;
vi start(n+1, 0), end(n+1, 0), nums(n+1, 0);
function<void(ll, ll)> dfs=[&](ll u, ll p)
    start[u]=++t;
    // add(t, nums[u]);
    for(ll v : adj[u]) if(v != p) dfs(v, u);
    end[u]=t;

// Variant: Subtree queries
dfs(1, 0); // Add and sum on nums are BIT operations
ll a, s, x; cin>>a;
if(a==1)
    cin>>s>>x;
    ll diff=x-nums[s]; nums[s]=x;
    add(start[s], diff);
else
    cin>>s;
    cout<<sum(end[s]) - sum(start[s]-1)<<en;



// DIFFICULT - Much rarer to see.

// Trie for maximum bitwise XOR
struct TrieNode
    TrieNode* children[2];
    int count;
    TrieNode() : children{nullptr, nullptr}, count(0)
struct Trie
    TrieNode* root;
    Trie(){root = new TrieNode(); }
    void add(int x) // Add freq
        TrieNode* node = root;
        repr(i, ln, 0)
            int bit = (x>>i) & 1;
            if(!node->children[bit]) node->children[bit] = new TrieNode();
            node = node->children[bit];
            node->count++;
    void sub(int x) // Sub freq
        TrieNode* node = root;
        repr(i, ln, 0)
            int bit = (x >> i) & 1;
            TrieNode* child = node->children[bit];
            child->count--;
            if(child->count == 0)
                delete child; node->children[bit] = nullptr; break;
            node = child;
    int query(int x) const
        TrieNode* node = root; int res = 0;
        repr(i, ln, 0)
            if(!node) break; // Safety check
            int bit = (x >> i) & 1;
            if(node->children[1 - bit] && node->children[1 - bit]->count > 0)
                res |= (1 << i);
                node = node->children[1 - bit];
            else
                node = node->children[bit];
        return res;

// Counting Paths
void dfs(int u, int p)
    in[u]=++t;
    par[u][0]=p;
    for(int i=1; i<ln; ++i) par[u][i]=par[par[u][i-1]][i-1];
    for(int v : adj[u]) if(v!=p) dfs(v, u);
    out[u]=++t;
void propogate(int u)
    for(int v : adj[u])
        if(v==par[u][0]) continue;
        propogate(v);
        sub[u]+=sub[v];
bool ancestor(int u, int v) return in[u]<=in[v] && out[u]>=out[v]; // Quick Ancestor Check
int lca(int u, int v)
    if(ancestor(u, v)) return u;
    if(ancestor(v, u)) return v;
    repr(i, ln, 0)
        if(!ancestor(par[u][i], v)) u=par[u][i];
    return par[u][0];
dfs(1, 1);
f(i, m)
    int a, b; cin>>a>>b;
    int l=lca(a, b);
    sub[a]++; sub[b]++; sub[l]--;
    if(l!=1) sub[par[l][0]]--;
propogate(1);
f(i, n) cout<<sub[i+1]<<" ";