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
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-37; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n'; constexpr char sp = ' ';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };


#define N 300001
#define mod 1000000007
#define inf 1e9

int p[N],r[N];
int length[N];
vector< vi > adj(N);
bool visited[N];
int depth[N];

int parent(int a)
{
    if(p[a]==a)
        return a;
    return p[a]=parent(p[a]);
}

void mergeSet(int a,int b)
{
    a=parent(a),b=parent(b);
    if(r[a]>r[b])
        p[b]=a;
    else
        p[a]=b;
    if(r[a]==r[b])
        r[b]++;
}

void dfs(int node,int p,vi &v)
{
    if(visited[node])
        return;
    v.push_back(node);
    visited[node]=true;
    depth[node]=depth[p]+1;
    for(int i=0;i<adj[node].size();i++)
        dfs(adj[node][i],node,v);
}

int findFurthestNode(vi &v,bool flag)
{
    int temp=0,node=0;
    for(int i=0;i<v.size();i++)
    {
        if(!flag)
            visited[v[i]]=false;
        if(depth[v[i]]>=temp)
            temp=depth[v[i]],node=v[i];
    }
    return node;
}

void createRegion(int node)
{
    if(visited[node])
        return;
    int t=node;
    vi v;
    dfs(node,0,v);
    node=findFurthestNode(v,false);
    v.clear();
    dfs(node,0,v);
    node=findFurthestNode(v,true);
    t=parent(t);
    length[t]=depth[node]-1;
}

void mergeRegion(int a,int b)
{
    a=parent(a),b=parent(b);
    if(a==b)
        return;
    mergeSet(a,b);
    int l1=length[a],l2=length[b];
    a=parent(a);
    int l=max(l1/2,l1-l1/2)+max(l2/2,l2-l2/2)+1;
    length[a]=max(max(l1,l2),l);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("Input.txt","r",stdin);
//    freopen("Output.txt","w",stdout);
    for(int i=1;i<N;i++)
        p[i]=i;
    int n,m,q;
    cin>>n>>m>>q;
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        mergeSet(a,b);
    }
    for(int i=1;i<=n;i++)
        createRegion(i);
    for(int i=0;i<q;i++)
    {
        int t,a,b;
        cin>>t;
        if(t==1)
        {
            cin>>a;
            cout<<length[parent(a)]<<endl;
        }
        else
        {
            cin>>a>>b;
            mergeRegion(a,b);
        }
    }
    return 0;
}