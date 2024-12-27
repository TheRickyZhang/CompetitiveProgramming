#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vvpii = vector<vpii>; using vpll = vector<pll>; using vvpll = vector<vpll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
using vvi = vector<vector<int>>; using vvll = vector<vector<ll>>; using mpq = priority_queue<ll, vector<ll>, greater<>>; using mpqq = priority_queue<pll, vpll, greater<>>;
#define ump unordered_map
#define ust unordered_set
#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");
constexpr int MOD = 1000000007; constexpr ll INF = INT_MAX-37; constexpr ll INFL = 0x3f3f3f3f3f3f3f3f; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
constexpr char EN = '\n'; constexpr char SP = ' '; auto en = EN; auto sp = SP;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = enable_if_t<!is_same_v<T_container, string>, typename T_container::value_type>> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s; int m;
    set<int> diff; // [0, n]
    cin>>s>>m;
    int n=s.size();
    diff.insert(0); diff.insert(n); // The first and last+1 items are always changed from before
    f(i, n) if(s[i] != s[i+1]) diff.insert(i+1);
    vi cnt(m+1, 0); pq q; // Both store lengths, need random access and largest values
    auto ad=[&](int x) {
        cnt[x]++; q.push(x);
    };
    for(auto it=diff.begin(); next(it) != diff.end(); ++it) {
        int dd = *next(it) - *it; // Difference between elements in diff
        ad(dd);
    }

    auto modify = [&](int x) {
        if(x==0 || x==s.size()) return;
        auto it=diff.find(x);
        if(it != diff.end()) {
            int a=*prev(it), b=*next(it);
            diff.erase(it);
            cnt[x-a]--; cnt[b-x]--;
            ad(b-a);
        } else {
            it=diff.insert(x).first;
            int a=*prev(it), b=*next(it);
            cnt[b-a]--; ad(x-a), ad(b-x);
        }
    };
    f(i, m) {
        int x; cin>>x;
        // Note the 1-indexing. Focus on the two diffs that include a comparison of nums[i]
        modify(x-1); // Merge everything index i was blocking
        modify(x);   // Merge everything index i+1 was blocking - note this reverses the above affect except for the intended index i
        while(!cnt[q.top()]) q.pop();
        cout<<q.top()<<SP;
    }
}