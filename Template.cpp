#include <bits/stdc++.h>
using namespace std;

// Template by Ricky Zhang
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
/* Data structures */
tpl_<tn_ T>using v=vector<T>; using ll=long long; using pii=pair<int,int>; using pll=pair<ll,ll>; using t3=tuple<int,int,int>; using t4=tuple<int,int,int,int>;
using vi=v<int>; using vb=v<bool>; using vs=v<string>; using vvi=v<vi>; using vll=v<ll>; using vvll=v<vll>; using vpii=v<pii>; using vvpii=v<vpii>; using vpll=v<pll>; using vvpll=v<vpll>;
tpl_<tn_ K,tn_ V>using ump=unordered_map<K, V>; tpl_<tn_ T>using ust=unordered_set<T>; tpl_<tn_ K,tn_ V>using rmap=map<K,V,greater<K>>; tpl_<tn_ T>using rset=set<T,greater<T>>; tpl_<tn_ T>using mset=multiset<T>; tpl_<tn_ T>using rmset=multiset<T,greater<T>>;
tpl_<tn_ T>using pq=priority_queue<T>; tpl_<tn_ T>using mpq=priority_queue<T,vector<T>,greater<T>>;
/* Binary search bounds */
tpl_<class It, class T> auto leq_bound(It first, It last, T val) { auto it = upper_bound(first, last, val); return it != first ? prev(it) : it;} tpl_<class C, class T>auto leq_bound(C& c, T val) {auto it = c.upper_bound(val);return it != c.begin() ? prev(it) : it;}
tpl_<class It, class T> auto less_bound(It first, It last, T val) {auto it = lower_bound(first, last, val);return it != first ? prev(it) : it; }tpl_<class C, class T>auto less_bound(C& c, T val) {auto it = c.lower_bound(val);return it!=c.begin()?prev(it):it;}
tpl_<class C, class T>auto lower_bound(C& c, T val) {return c.lower_bound(val);} ntpl_<class C, class T>auto upper_bound(C& c, T val) {return c.upper_bound(val);}
/* Debugging */
tpl_<tn_ A, tn_ B> ostream& operator<<(ostream& os, const pair<A, B>& p) { return os << "(" << p.ff << ", " << p.ss << ")"; }
tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, str>, typename C::value_type>> ostream& operator<<(ostream& os, const C& v) { os << "{"; str sep; for (const T& x : v) os << sep << x, sep = ", "; return os << "}"; }
tpl_<tn_ K, tn_ V> ostream& operator<<(ostream& os, const map<K, V>& m) { os << "{"; str sep; for (const auto& kv : m) os << sep << kv.ff << ": " << kv.ss, sep = ", "; return os << "}"; }
/* Special */
struct pairHash{tpl_<class T1,class T2>size_t operator()(const pair<T1,T2>&p)const{return hash<T1>{}(p.first)^ (hash<T2>{}(p.second)<<1);}}; struct vectorHash{tpl_<class T>size_t operator()(const vector<T>&v)const{size_t hashValue=0;for(const T&i:v)hashValue^=hash<T>{}(i)+0x9e3779b9+(hashValue<<6)+(hashValue>>2);return hashValue;}};
const vector<pii> dirs={{1,0},{0,-1},{0,1},{-1,0}}; auto check=[](auto y,auto x,auto m,auto n){return y>=0&&y<m&&x>=0&&x<n;};
constexpr int MOD=1000000007; constexpr int INF=1000000000; constexpr ll INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";
tpl_<tn_ T> T ceil(T num, T den) { return (num+den-1)/den;} tpl_<tn_ T> T mul(T a, T b, T mod=MOD) {return ((a%mod)*(b%mod))%mod;} tpl_<tn_ T>T add(T a, T b, T mod=MOD) {return (a+b) % mod;}


// Main function demonstrating the utilities
int main() {
    // Using vector<int> (vi)
    vi vec = {1, 2, 3, 3, 5};
    cout << "vi is a vector<int>: " << vec << "searching for 3" << en;

    cout << "lower_bound: "<< *lower_bound(all(vec), 3)<<en;
    cout << "upper_bound: "<< *upper_bound(all(vec), 3)<<en;
    cout << "leq_bound: "<< *leq_bound(all(vec), 3)<<en;
    cout << "less_bound: "<< *less_bound(all(vec), 3)<<en;

    set<int> s = {1, 2, 3, 5, 6};
    cout << "Set<int>: " << s << en;
    cout << "lower_bound: "<< *lower_bound(s, 5)<<en;
    cout << "upper_bound: "<< *upper_bound(s, 5)<<en;
    cout<<"leq_bound: "<< *leq_bound(s, 5)<<en;
    cout<<"less_bound: "<< *less_bound(s, 5)<<en;

    // Pair example (pii)
    pii p = {3, 7};
    cout << "pii is a pair<int, int>: " << p << en;

    // 2D vector example (vvi)
    vvi grid = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "vvi (2D vector<int>) is: " << grid << en;

    // Set and map usage
    ump<int, int> map = {{1, 2}, {3, 4}};
    cout << "unordered_map<int, int>: " << map << en;

    // Hashing example
    unordered_set<vi, vectorHash> hashedSet;
    hashedSet.insert(vec);
    cout << "Vector hash of {1, 2, 3, 4, 5} stored in ust<vi>: {";
    for (const auto& v : hashedSet) cout << v << " ";
    cout << "}" << en;

    // Using ceil and multiplication modulo
    cout << "ceil(10, 3): " << ceil(10, 3) << en;
    cout << "mul(123, 456): " << mul(123, 456) << en;

    // Directions and boundary checks
    int y = 1, x = 2, m = 3, n = 4;
    if (check(y, x, m, n)) cout << "(" << y << ", " << x << ") is within bounds!" << en;
    else cout << "(" << y << ", " << x << ") is out of bounds!" << en;

    return 0;
}

// // All macros written out
// tpl_<tn_ T>using v = vector<T>;
// using ll = long long;
// using pii = pair<int, int>;
// using pll = pair<ll, ll>;
// using t3 = tuple<int, int, int>;
// using t4 = tuple<int, int, int, int>;
// using vi = v<int>;
// using vb = v<bool>;
// using vs = v<string>;
// using vvi = v<vi>;
// using vll = v<ll>;
// using vvll = v<vll>;
// using vpii = v<pii>;
// using vvpii = v<vpii>;
// using vpll = v<pll>;
// using vvpll = v<vpll>;
// tpl_<tn_ K, tn_ V>using ump = unordered_map<K, V>;
// tpl_<tn_ T>using ust = unordered_set<T>;
// tpl_<tn_ K, tn_ V>using rmap = map<K, V, greater<K>>;
// tpl_<tn_ T>using rset = set<T, greater<T>>;
// tpl_<tn_ T>using mset = multiset<T>;
// tpl_<tn_ T>using rmset = multiset<T, greater<T>>;
// tpl_<tn_ T>using pq = priority_queue<T>;
// tpl_<tn_ T>using mpq = priority_queue<T, vector<T>, greater<T>>;
//
// tpl_<tn_ A, tn_ B>
// ostream& operator<<(ostream& os, const pair<A, B>& p) {
//     return os << "(" << p.first << ", " << p.second << ")";
// }
//
// tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, string>, typename C::value_type>>
// ostream& operator<<(ostream& os, const C& v) {
//     os << "{";
//     string sep;
//     for (const T& x : v) os << sep << x, sep = ", ";
//     return os << "}";
// }
//
// tpl_<tn_ K, tn_ V>
// ostream& operator<<(ostream& os, const map<K, V>& m) {
//     os << "{";
//     string sep;
//     for (const auto& kv : m) os << sep << kv.first << ": " << kv.second, sep = ", ";
//     return os << "}";
// }
//
// struct pairHash {
//     tpl_<class T1, class T2>
//     size_t operator()(const pair<T1, T2>& p) const {
//         return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1);
//     }
// };
//
// struct vectorHash {
//     tpl_<class T>
//     size_t operator()(const vector<T>& v) const {
//         size_t hashValue = 0;
//         for (const T& i : v)
//             hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
//         return hashValue;
//     }
// };
//
// const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
// auto check = [](auto y, auto x, auto m, auto n) {
//     return y >= 0 && y < m && x >= 0 && x < n;
// };
// constexpr int MOD = 1000000007;
// constexpr int INF = 1000000000;
// constexpr ll INFL = 0x3f3f3f3f3f3f3f3f;
// constexpr auto en = "\n";
// constexpr auto sp = " ";
// tpl_<tn_ T> T ceil(T num, T den) { return (num + den - 1) / den; }
// tpl_<tn_ T> T mul(T a, T b, T mod = MOD) { return ((a % mod) * (b % mod)) % mod; }
// tpl_<tn_ T> T add(T a, T b, T mod = MOD) { return (a + b) % mod; }
