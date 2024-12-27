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

constexpr int N = 100000;
ll t, n, m, k, a, b;

int main() {
    cin>>n;
    vi nums(n);
    f(i, n) cin>>nums[i];
    multiset<int> taken;
    taken.insert(max(nums[0], nums[1]));
    for(int i=2; i<n; i+=2) {
        int mn = *taken.begin();
        // Only need an iterative comparison of whether to greedily swap out
        if(mn < min(nums[i], nums[i+1])) {
            taken.erase(taken.begin());
            taken.insert(nums[i]); taken.insert(nums[i+1]);
        } else {
            taken.insert(max(nums[i], nums[i+1]));
        }
    }
    ll res=0;
    for(int x : taken) res += x;
    cout<<res<<en;
}

// // My solution (Problem: cannot know how to take early when can delay maximum)
// int main() {
//     ios::sync_with_stdio(false); cin.tie(nullptr);
//     cin>>n;
//     vll nums(n); ump<ll, mpq> indices; set<ll> s;
//     f(i, n) {
//         ll x; cin>>x;
//         nums[i]=x;
//         s.insert(x);
//         indices[x].push(i);
//     }
//     ll res=0;
//     vb taken(n, false);
//     ll it=0;
//     vi a, b;
//     f(i, n) {
//         if(i % 2==0) {
//             ll x = *prev(s.end());
//             taken[indices[x].top()] = true;
//             indices[x].pop();
//             if(indices[x].empty()) s.erase(x);
//             res += x;
//             a.pb(x);
//         } else {
//             while(it < n-1 && taken[it]) it++;
//             int x = nums[it];
//             b.pb(x);
//             taken[it]=true;
//             indices[x].pop();
//             if(indices[x].empty()) s.erase(x);
//         }
//     }
//     cout<<a<<en<<b<<en;
//     cout<<res<<en;
// }