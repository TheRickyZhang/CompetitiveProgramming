#include <bits/stdc++.h>

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

//constexpr int N = 200000;
//int ln = log2(N) + 1;
//ll t, n, m, k, a, b, q;
//vvi par;
//vi len; // Steps from outside cycle -> in, OR position in cycle
//vb vis;
//
//void dfs(int u) {
//    if(vis[u]) return;
//    vis[u]=true;
//    dfs(par[u][0]);
//    len[u]=len[par[u][0]] + 1;
//}
//
//int lift(int x, int p) {
//    int i = 0;
//    while(p) {
//        if(p&1) x=par[x][i];
//        p>>=1; i++;
//    }
//    return x;
//}
//
//int main() {
//    cin>>n>>q;
//    par=vvi(n, vi(ln, 0));
//    len=vi(n, 0);
//    vis=vb(n, false);
//
//    f(i, n){
//        int a; cin>>a; a--;
//        par[i][0] = a;
//    }
//
//    f(i, n) {
//        f(j, ln-1) {
//            par[i][j+1]=par[par[i][j]][j];
//        }
//    }
//
//    f(i, n) {
//        if(!vis[i]) dfs(i);
//    }
//
//    f(i, q) {
//        int x, y; cin>>x>>y; x--; y--;
//        int xx = lift(x, len[x]);
//        if(lift(x, len[x] - len[y]) == y) {
//            cout<<len[x]-len[y]<<endl;
//        } else if(lift(xx, len[xx] - len[y]) == y) {
//            cout<<len[x]+len[xx]-len[y]<<endl;
//        } else {
//            cout<<-1<<endl;
//        }
//    }
//}