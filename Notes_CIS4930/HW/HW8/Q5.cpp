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
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-5; const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };

int bits(int n) {
    return __builtin_popcount(n);
}

class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size();
        int n = seats[0].size();
        int mx = 1<<n;
        vvi dp(m, vi(mx, -1));

        vvi states(m);
        f(i, m) {
            int mask = 0;
            for(char c : seats[i]) {
                mask <<= 1;
                mask += (c=='.');
            }
            f(j, (1<<n)) {
                if((j & mask) == j && (j & (j<<1)) == 0) states[i].pb(j);
            }
        }

        for(int x : states[m-1]) {
            dp[m-1][x] = bits(x);
        }

        for(int i = m-2; i >= 0; --i) {
            for(int x : states[i]) {
                for(int y : states[i+1]) {
                    if( (x & (y<<1)) == 0 && (x & (y>>1)) == 0 ) {
                        dp[i][x] = max(dp[i][x], dp[i+1][y] + bits(x));
                    }
                }
            }
        }

        int res = 0;
        f(j, mx) {
            res = max(res, dp[0][j]);
        }
        return res;
    }
};