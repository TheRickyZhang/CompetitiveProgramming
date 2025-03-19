#include <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define repr(i, a, b) for (int i = (a); i >= (b); --i)
#define str string
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");
tpl_<tn_ T>using v=vector<T>; using ll=long long; using pii=pair<int,int>; using pll=pair<ll,ll>; using t3=tuple<int,int,int>; using t4=tuple<int,int,int,int>;
using vi=v<int>; using vb=v<bool>; using vs=v<string>; using vvi=v<vi>; using vll=v<ll>; using vvll=v<vll>; using vpii=v<pii>; using vvpii=v<vpii>; using vpll=v<pll>; using vvpll=v<vpll>;
tpl_<tn_ K,tn_ T>using ump=unordered_map<K, T>; tpl_<tn_ T>using ust=unordered_set<T>; tpl_<tn_ K,tn_ T>using rmap=map<K,T,greater<K>>; tpl_<tn_ T>using rset=set<T,greater<T>>; tpl_<tn_ T>using mset=multiset<T>; tpl_<tn_ T>using rmset=multiset<T,greater<T>>;
tpl_<tn_ T>using pq=priority_queue<T>; tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;
tpl_<class It, class T> auto leq_bound(It first, It last, T val) { auto it = upper_bound(first, last, val); return it != first ? prev(it) : it;} tpl_<class C, class T>auto leq_bound(C& c, T val) {auto it = c.upper_bound(val);return it != c.begin() ? prev(it) : it;}
tpl_<class It, class T> auto less_bound(It first, It last, T val) {auto it = lower_bound(first, last, val);return it != first ? prev(it) : it; }tpl_<class C, class T>auto less_bound(C& c, T val) {auto it = c.lower_bound(val);return it!=c.begin()?prev(it):it;}
tpl_<class C, class T>auto lower_bound(C& c, T val) {return c.lower_bound(val);} tpl_<class C, class T>auto upper_bound(C& c, T val) {return c.upper_bound(val);}
tpl_<tn_ A, tn_ B> ostream& operator<<(ostream& os,const pair<A, B>& p){return os<<"("<<p.ff<<", "<<p.ss<<")";}
tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, str>, typename C::value_type>> ostream& operator<<(ostream& os, const C& v) { os<<"{"; str sep; for(const T& x : v) os<<sep<<x, sep=", "; return os<<"}";}
tpl_<tn_ A> ostream& operator<<(ostream& os, const v<v<A>>& v) { for (const auto& row : v) { os << "{ "; for (const auto& elem : row) {os<<elem<<" ";}os<<"}"<<"\n"; } return os;}
tpl_<tn_ K, tn_ T> ostream& operator<<(ostream& os, const map<K, T>& m) { os << "{"; str sep; for (const auto& kv : m) os << sep << kv.ff << ": " << kv.ss, sep = ", "; return os << "}"; }
struct pairHash{tpl_<class T1,class T2>size_t operator()(const pair<T1,T2>&p)const{return hash<T1>{}(p.first)^ (hash<T2>{}(p.second)<<1);}}; struct vectorHash{tpl_<class T>size_t operator()(const vector<T>&v)const{size_t h=0;for(const T&i:v)h^=hash<T>{}(i)+0x9e3779b9+(h<<6)+(h>>2);return h;}};
struct DSU{vi p,sz;explicit DSU(int n){p.resize(n),sz.resize(n,1),iota(all(p),0);}int par(int x){return x==p[x]?x:p[x]=par(p[x]);}void merge(int x,int y){x=par(x),y=par(y);if(x!=y){if(sz[x]<sz[y])swap(x,y);p[y]=x,sz[x]+=sz[y];}}};
const vector<pii> dirs={{0,1},{0,-1},{-1,0},{1,0}}; auto check=[](auto y,auto x,auto m,auto n){return y>=0&&y<m&&x>=0&&x<n;}; int encodeDir(const char c) {if(c=='R')return 0;if(c=='L')return 1;if(c=='U')return 2;if(c=='D')return 3;cerr<<"Invalid dir "<<c<<"\n";return -1;}
constexpr ll MOD=1000000007; constexpr int INF=1000000000; constexpr ll INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";
tpl_<tn_ T> T ceil(T num, T den) { return (num+den-1)/den;} tpl_<tn_ T> T mul(T a, T b, T mod=MOD) {return ((a%mod)*(b%mod))%mod;} tpl_<tn_ T>T add(T a, T b, T mod=MOD) {return (a+b) % mod;}

const int MAX = 1005;
const int di[] = {0, 0, -1, 1};
const int dj[] = {-1, 1, 0, 0};
const char allDirs[] = {'L', 'R', 'U', 'D'};

int n, q, curGood, good[MAX][MAX], dir[MAX][MAX];

bool inside(int i, int j){
    return i >= 1 and i <= n and j >= 1 and j <= n;
}
bool isGood(int i, int j){
    // Checks if in and is usable
    if (!inside(i, j))
        return false;

    for (int d = 0; d < 4; d++){
        // If it has a direction and d is not that direction
        if (dir[i][j] != -1 and d != dir[i][j])
            continue;

        int ni = i + di[d];
        int nj = j + dj[d];

        // Good if pointing outside or towards an good cell
        if (!inside(ni, nj) or good[ni][nj])
            return true;
    }
    return false;
}
void dfs(int i, int j){
    if (!isGood(i, j) or good[i][j])
        return;

    good[i][j] = true;
    curGood++;

    for (int d = 0; d < 4; d++)
        dfs(i + di[d], j + dj[d]);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;

    // -1 meaning it can be anything
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dir[i][j] = -1;

    vector<tuple<int, int, char>> upds(q);
    vector<int> res;

    for (auto &[r, c, t] : upds){
        cin >> r >> c >> t;
        dir[r][c] = find(allDirs, allDirs + 4, t) - allDirs;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dfs(i, j);

    reverse(upds.begin(), upds.end());

    for (auto [r, c, t] : upds){
        res.push_back(n * n - curGood);

        dir[r][c] = -1;
        dfs(r, c);
    }

    reverse(res.begin(), res.end());

    for (int i : res)
        cout << i << "\n";
}


// int main() {
//     ios::sync_with_stdio(false); cin.tie(nullptr);
//     cin>>n>>k;
//     vvi grid(n, vi(n, -1)); // Contains directions
//     v<vb> fail(n, vb(n, false));
//
//     int res=0;
//     auto mark = [&](vpii& vis) {
//         // cout<<"HERE"<<en;
//         for(auto [y, x] : vis) {
//             if(!fail[y][x]) {
//                 fail[y][x] = true; res++;
//             }
//         }
//     };
//     auto dfs = [&](int a, int b) {
//         stack<pii> s;
//         vpii vis;
//         s.push({a, b});
//         while(!s.empty()) {
//             auto [y, x] = s.top(); s.pop();
//             if(fail[y][x]) {
//                 mark(vis); return;
//             }
//             vis.emplace_back(y, x);
//             auto [dy, dx] = dirs[grid[y][x]];
//             int ny=y+dy, nx=x+dx;
//             if(check(ny, nx, n, n) && grid[ny][nx] >= 0) {
//                 if(ny == a && nx == b) {
//                     mark(vis); return;
//                 }
//                 s.emplace(ny, nx);
//             } else {
//                 return;
//             }
//         }
//     };
//     f(i, k) {
//         int y, x; cin>>y>>x; char c; cin>>c;
//         y--; x--;
//         int d = encodeDir(c);
//         grid[y][x] = d;
//         dfs(y, x);
//         // cout<<y<<sp<<x<<en;
//         // cout<<grid<<en<<fail<<en;
//         cout<<res<<en;
//     }
// }
