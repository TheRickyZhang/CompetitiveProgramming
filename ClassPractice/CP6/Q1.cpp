#include <bits/stdc++.h>
using namespace std;

// Much harder than it seems, with strings and input handling adding much complexity
// Use FLOYD-WARSHALL to find cycles!!!! As adj[i][i] = INF at first
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
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-96; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y,auto x,auto m,auto n) {return y >= 0 && y < m && x >= 0 && x < n; };

int n, nlines, u, v, w;
str name, line, s;
map<str, int> m; // name to int id
vs fnames;
vi cycle;
vvi adj, p;

int main(){
    ios::sync_with_stdio();
    cin.tie(nullptr);
    
    cin >> n;
    adj.assign(n, vi(n, INF));
    // Path: p[i][j] is the last node before j on path i -> j (look into this, slightly modified pre arr)
    p.assign(n, vi(n, -1));

    // Initialize path matrix
    f(i, n) f(j, n) p[i][j] = i;

    f(i, n){
        cin >> name;
        fnames.pb(name);
        m[name] = i;
    }

    for(int i = 0; i < n; ++i){
        cin >> name >> nlines;
        for(int j = 0; j < nlines; ++j){
            cin >> name; // skip "import"
            while(cin >> name){
                if(name.back() == ',') name.pop_back();
                if(m.find(name) != m.end()){
                    v = m[name];
                    adj[i][v] = 1;
                }
                if(cin.peek() == '\n') break;
            }
        }
    }

    // Floyd-Warshall Algorithm to find all-pairs shortest paths
    f(k, n){
        f(i, n){
            f(j, n){
                // Prevent integer overflow
                if(adj[i][k] != INF && adj[k][j] != INF && adj[i][k] + adj[k][j] < adj[i][j]){
                    adj[i][j] = adj[i][k] + adj[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }

    // Find the smallest cycle
    int mnIndex = -1, mnSize = INF;
    f(i, n){
        if(adj[i][i] < mnSize){
            mnIndex = i;
            mnSize = adj[i][i];
        }
    }
    if(mnSize == INF){
        cout << "SHIP IT" << en;
        return 0;
    }

    // Reconstruct path
    int curr = p[mnIndex][mnIndex];
    cycle.pb(mnIndex);
    while(curr != mnIndex){
        cycle.pb(curr);
        curr = p[mnIndex][curr];
    }
    reverse(all(cycle));

    trav(i, cycle){
        cout << fnames[i] << " ";
    }
    cout << en;
    return 0;
}

// My actual first attempt - tried to prune possible cycle nodes w/ topological at first, then do shortest path from each remaining node
// Always prints "SHIP IT", don't want to spend time to figure out if this method is possibly feasible.
// From online solutions Floyd-Warshall method seems so much easier - most difficult part is input handling!

// int main() {
//     int n;
//     cin>>n; cin.ignore();
//     vs files(n);
//     f(i, n) cin>>files[i];
//     cin.ignore();
//
//     ump<str, vs> adj;
//     ump<str, int> in;
//
     // f(_, n) {
     //     str a, temp;
     //     int sz;
     //     cin>>a>>sz; cin.ignore();
     //     getline(cin, temp);
     //
     //     str name;
     //     // form adj from annoying input
     //     rep(i, 7, temp.size()) {
     //         if(temp[i] == ',') {
     //             adj[a].pb(name);
     //             in[name]++;
     //             name = "";
     //             if(name==a) {
     //                 cout<<a<<en;
     //                 return 0;
     //             }
     //         } else if(temp[i] != ' ') {
     //             name += temp[i];
     //         }
     //     }
     // }
//     // Note - visited set is not needed here (as in topo they can only be considered once - when in[s]==0!
//     queue<str> q;
//
//     for(str s : files) {
//         if(in[s] == 0) q.push(s);
//     }
//
//     while(!q.empty()) {
//         str u = q.front(); q.pop();
//         for(str& v : adj[u]) {
//             if(--in[v]==0) {
//                 q.push(v);
//             }
//         }
//     }
//
//     // Now the remaining nodes are entire vector space (lol) for cycles, increasing efficiency
//     ust<str> valid;
//     for(str& s : files) {
//         if(in[s]>0) valid.insert(s);
//     }
//     if(valid.empty()) {
//         cout<<"SHIP IT"<<en;
//         return 0;
//     }
//
//     auto findShortestCycle = [&](const str& a) {
//         ump<str, int> dist;
//         ump<str, str> p; // parent
//         queue<str> q;
//
//         q.push(a); dist[a] = 0;
//         while(!q.empty()) {
//             str u =q.front(); q.pop();
//             for (str& v : adj[u]) {
//                 if(!valid.count(v)) continue; // Must ONLY have nodes in valid
//                 if(v==a) { // note that a cycle of len 1 is possible too (nned && dist[u] >= 1)?
//                     vs cycle = {a};
//                     str curr = u;
//                     while(curr != a) {
//                         cycle.pb(curr);
//                         curr = p[curr];
//                     }
//                     reverse(all(cycle));
//                     return cycle;
//                 }
//
//                 if(!dist.count(v)) { // NOt explored yet
//                     dist[v] = dist[u]+1;
//                     p[v] = u;
//                     q.push(v);
//                 }
//             }
//         }
//         vs empty;
//         return empty;
//     };
//
//     vs res;
//     for(str file : valid) {
//         vs cycle = findShortestCycle(file);
//         if(cycle.size() < res.size()) {
//             res = cycle;
//             if(res.size() == 1) break;
//         }
//     }
//     if(res.empty()) cout<<"SHIP IT"<<en;
//     else {
//         f(i, res.size()) cout<<res[i]<<' ';
//         cout<<en;
//     }
//     return 0;
// }