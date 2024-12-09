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
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-37; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

constexpr int N = 100005;
ll t, n, m, a, b;
string s;
vi nums;

// Indices whose suffixes are in lexigraphical order
vi suf(N), pos(N), temp(N, 0), lcp(N);
int gap;
// Basically pos[x] < pos[y] BUT if prefix end early = smaller
bool comp(int x, int y) {
    if(pos[x] != pos[y]) return pos[x] < pos[y];
    x += gap; y += gap;
    if(x < N && y < N) return pos[x] < pos[y];
    return x > y; //
}
// Use prefix doubling algorithm
void suffix() {
    f(i, N) {
        suf[i] = i;
        pos[i] = s[i]; // ASCII values
    }
    for(gap = 1; ; gap<<=1) {
        sort(all(suf), comp);
        // Ex: suf(banana) -> [1, 3, 5, 0, 2, 4}
        // s[1]==s[3] -> false, nothing.
        // s[5]!=s[0] -> true,
        f(i, N-1) temp[i+1] = temp[i] + comp(suf[i], suf[i+1]);
        // temp = [0, 0, 0, 1, 2, 2] (since 5-0, 0-2 only different pairs)
        f(i, N) pos[suf[i]] = temp[i];
        // pos = [1, 0, 2, 0, 2, 0]

        if(temp[N-1]==N-1) break;
    }
}

void build_lcp() {
    for (int i = 0, k = 0; i < N; i++) if (pos[i] != N-1) {
        int j = sa[pos[i] + 1];
        while (S[i + k] == S[j + k])
            k++;
        lcp[pos[i]] = k;
        if (k) k--;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
}
