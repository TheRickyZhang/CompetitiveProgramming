#include<bits/stdc++.h>
using namespace std;

#define all(a) a.begin(),a.end()
#define pb push_back
#define sz(a) ((int)a.size())

using ll=long long;
using u32=unsigned int;
using u64=unsigned long long;
using i128=__int128;
using u128=unsigned __int128;

using pii=pair<int,int>;
using pll=pair<ll,ll>;

template<typename T> using vc=vector<T>;
template<typename T> using vvc=vc<vc<T>>;
template<typename T> using vvvc=vc<vvc<T>>;

using vi=vc<int>;
using vll=vc<ll>;
using vvi=vc<vi>;
using vvll=vc<vll>;

#define vv(type,name,n,...) \
    vector<vector<type>> name(n,vector<type>(__VA_ARGS__))
#define vvv(type,name,n,m,...) \
    vector<vector<vector<type>>> name(n,vector<vector<type>>(m,vector<type>(__VA_ARGS__)))

template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

// https://trap.jp/post/1224/
#define rep1(n) for(ll i=0; i<(ll)(n); ++i)
#define rep2(i,n) for(ll i=0; i<(ll)(n); ++i)
#define rep3(i,a,b) for(ll i=(ll)(a); i<(ll)(b); ++i)
#define rep4(i,a,b,c) for(ll i=(ll)(a); i<(ll)(b); i+=(c))
#define cut4(a,b,c,d,e,...) e
#define rep(...) cut4(__VA_ARGS__,rep4,rep3,rep2,rep1)(__VA_ARGS__)
#define per1(n) for(ll i=((ll)n)-1; i>=0; --i)
#define per2(i,n) for(ll i=((ll)n)-1; i>=0; --i)
#define per3(i,a,b) for(ll i=((ll)a)-1; i>=(ll)(b); --i)
#define per4(i,a,b,c) for(ll i=((ll)a)-1; i>=(ll)(b); i-=(c))
#define per(...) cut4(__VA_ARGS__,per4,per3,per2,per1)(__VA_ARGS__)
#define rep_subset(i,s) for(ll i=(s); i>=0; i=(i==0?-1:(i-1)&(s)))

template<typename T, typename S> constexpr T ifloor(const T a, const S b){return a/b-(a%b&&(a^b)<0);}
template<typename T, typename S> constexpr T iceil(const T a, const S b){return ifloor(a+b-1,b);}

template<typename T>
void sort_unique(vector<T> &vec){
    sort(vec.begin(),vec.end());
    vec.resize(unique(vec.begin(),vec.end())-vec.begin());
}

template<typename T, typename S> constexpr bool chmin(T &a, const S b){if(a>b) return a=b,true; return false;}
template<typename T, typename S> constexpr bool chmax(T &a, const S b){if(a<b) return a=b,true; return false;}

template<typename T, typename S> istream& operator >> (istream& i, pair<T,S> &p){return i >> p.first >> p.second;}
template<typename T, typename S> ostream& operator << (ostream& o, const pair<T,S> &p){return o << p.first << ' ' << p.second;}

#ifdef i_am_noob
#define bug(...) cerr << "#" << __LINE__ << ' ' << #__VA_ARGS__ << "- ", _do(__VA_ARGS__)
template<typename T> void _do(vector<T> x){for(auto i: x) cerr << i << ' ';cerr << "\n";}
template<typename T> void _do(set<T> x){for(auto i: x) cerr << i << ' ';cerr << "\n";}
template<typename T> void _do(unordered_set<T> x){for(auto i: x) cerr << i << ' ';cerr << "\n";}
template<typename T> void _do(T && x) {cerr << x << endl;}
template<typename T, typename ...S> void _do(T && x, S&&...y) {cerr << x << ", "; _do(y...);}
#else
#define bug(...) 777771449
#endif

template<typename T> void print(vector<T> x){for(auto i: x) cout << i << ' ';cout << "\n";}
template<typename T> void print(set<T> x){for(auto i: x) cout << i << ' ';cout << "\n";}
template<typename T> void print(unordered_set<T> x){for(auto i: x) cout << i << ' ';cout << "\n";}
template<typename T> void print(T && x) {cout << x << "\n";}
template<typename T, typename... S> void print(T && x, S&&... y) {cout << x << ' ';print(y...);}

template<typename T> istream& operator >> (istream& i, vector<T> &vec){for(auto &x: vec) i >> x; return i;}

vvi read_graph(int n, int m, int base=1){
    vvi adj(n);
    for(int i=0,u,v; i<m; ++i){
        cin >> u >> v,u-=base,v-=base;
        adj[u].pb(v),adj[v].pb(u);
    }
    return adj;
}

vvi read_tree(int n, int base=1){return read_graph(n,n-1,base);}

template<typename T, typename S> pair<T,S> operator + (const pair<T,S> &a, const pair<T,S> &b){return {a.first+b.first,a.second+b.second};}

template<typename T> constexpr T inf=0;
template<> constexpr int inf<int> = 0x3f3f3f3f;
template<> constexpr ll inf<ll> = 0x3f3f3f3f3f3f3f3f;

template<typename T> vector<T> operator += (vector<T> &a, int val){for(auto &i: a) i+=val; return a;}

template<typename T> T isqrt(const T &x){T y=sqrt(x+2); while(y*y>x) y--; return y;}

#define ykh mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())

//#include<atcoder/all>
//using namespace atcoder;

//using mint=modint998244353;
//using mint=modint1000000007;

struct Tree{
    int n;
    vector<vector<int>> adj,anc;
    vector<int> par,tl,tr,dep,ord,siz,ch,head;
    Tree(int _n=0){
        n=_n;
        adj.resize(n);
    }
    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void init(){
        par.resize(n),tl.resize(n),tr.resize(n),dep.resize(n),anc.resize(n),siz.resize(n),ch.resize(n),head.resize(n);
        int cur=-1,m=0;
        while((1<<m)<=n) m++;
        for(int i=0; i<n; ++i) anc[i].resize(m),ch[i]=-1;
        auto dfs1=[&](auto &self, int u, int fa) -> void{
            par[u]=fa;
            siz[u]=1;
            for(int v: adj[u]) if(v!=fa) self(self,v,u),siz[u]+=siz[v];
            for(int v: adj[u]) if(v!=fa&&(ch[u]==-1||siz[v]>siz[ch[u]])) ch[u]=v;
        };
        auto dfs2=[&](auto &self, int u, int fa) -> void{
            ord.push_back(u);
            tl[u]=++cur;
            anc[u][0]=fa;
            if(fa==-1) dep[u]=0;
            else dep[u]=dep[fa]+1;
            for(int i=1; i<m; ++i){
                if(anc[u][i-1]==-1) anc[u][i]=-1;
                else anc[u][i]=anc[anc[u][i-1]][i-1];
            }
            if(ch[u]!=-1) self(self,ch[u],u);
            for(int v: adj[u]) if(v!=fa&&v!=ch[u]) self(self,v,u);
            tr[u]=cur;
        };
        dfs1(dfs1,0,-1);
        dfs2(dfs2,0,-1);
        head[0]=0;
        for(int u: ord){
            for(int v: adj[u]) if(v!=par[u]){
                if(v==ch[u]) head[v]=head[u];
                else head[v]=v;
            }
        }
    }
    bool is_anc(int u, int v){return tl[u]<=tl[v]&&tr[u]>=tr[v];}
    int get_anc(int u, int x){
        for(int i=anc[0].size()-1; i>=0; --i) if(u!=-1&&(x>>i&1)) u=anc[u][i];
        return u;
    }
    int lca(int u, int v){
        if(is_anc(u,v)) return u;
        for(int i=anc[0].size()-1; i>=0; --i) if(anc[u][i]!=-1&&!is_anc(anc[u][i],v)) u=anc[u][i];
        return par[u];
    }
};

void ahcorz(){
    int lft=150;
    auto query=[&](int u){
        assert(lft>0);
        cout << "? " << u+1 << endl;
        lft--;
        int res; cin >> res; return res;
    };
    int n; cin >> n;
    Tree tree(n);
    rep(n-1){
        int u,v; cin >> u >> v; u--,v--;
        tree.add_edge(u,v);
    }
    tree.init();
    vi vis(n);
    auto fill_vis=[&](auto &self, int u){
        if(vis[u]) return;
        vis[u]=1;
        for(int v: tree.adj[u]) if(v!=tree.par[u]) self(self,v);
    };
    vi ord(n); iota(all(ord),0);
    sort(all(ord),[&](int i, int j){return tree.dep[i]<tree.dep[j];});
    per(n){
        int u=ord[i];
        if(vis[u]) continue;
        int v=u;
        rep(_,(lft-1)/2-1){
            if(v==0) break;
            v=tree.par[v];
        }
        if(!query(v)){
            fill_vis(fill_vis,v);
            continue;
        }
        int x=tree.ord.back();
        int m=tree.dep[u]-tree.dep[v]+1;
        rep(_,m){
            if(query(x)){
                cout << "! " << x+1 << endl;
                return;
            }
            if(!query(v)){
                int y=tree.par[v];
                if(y!=-1) y=tree.par[y];
                if(y==-1) y=0;
                cout << "! " << y+1 << endl;
                return;
            }
        }
        cout << "! 1" << endl;
        return;
    }
    assert(0);
}

signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cout << fixed << setprecision(20);
    int t=1;
    cin >> t;
    while(t--) ahcorz();
}