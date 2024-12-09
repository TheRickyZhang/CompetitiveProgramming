#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using pii = pair<int, int>;
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
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define trav(a, x) for (auto &a : x)
constexpr int MOD = 100000007; const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };

// I couldn't get my version to run fast enough :(, looks like this offset methodology is needed
class Solution {
    bool dfs(int row, int col, vvi& blocked, vvi& vis, vi& cell, vi& destination, int& dr, int& dc){
        if(abs(cell[1]-col)>=blocked.size() || abs(cell[0]-row)>=blocked.size()){
            return true;
        }
        if(row == destination[0] && col == destination[1]){
            return true;
        }
        vis[row + dr][col + dc] = 1;
        int r, c;
        for(auto [dy, dx] : dirs){
            r=row+dy;
            c=col+dx;
            if(r>=0 && c>=0 && r<1e6 && c<1e6 && !vis[r+dr][c+dc]){
                if(dfs(r,c,blocked,vis,cell,destination,dr,dc)) return true;
            }
        }
        return false;
    }

    bool notTrapped(vector<vector<int>>& blocked, vector<int>& cell,vector<int>& destination){
        vvi vis(blocked.size()*2+1,vector<int> (blocked.size()*2+1,0));
        int dr=blocked.size()-cell[0];
        int dc=blocked.size()-cell[1];
        for(auto it:blocked){
            int r = it[0] +dr;
            int c = it[1] +dc;
            if(r>=0 && c>=0 && r<blocked.size()*2+1 && c<blocked.size()*2+1){
                vis[r][c]=1;
            } 
        }
        return dfs(cell[0],cell[1],blocked,vis,cell,destination,dr,dc);
    }
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        return notTrapped(blocked, source, target) && notTrapped(blocked, target, source);
    }
};