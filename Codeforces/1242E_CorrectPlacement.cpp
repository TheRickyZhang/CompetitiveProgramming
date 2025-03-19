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
#include <bits/stdc++.h>

struct st {
    ll h, w, i;
};

bool cmp(st a, st b){
    if(a.h == b.h) return a.w > b.w;
    return a.h < b.h;
}

void solve(int tc){
    int n; cin >> n;
    vector<st> v(n);
    f(i, n){
        cin >> v[i].h >> v[i].w;
        if(v[i].h < v[i].w){
            swap(v[i].h, v[i].w);
        }
        v[i].i = i;
    }
    sort(all(v), cmp);
    vi overlap(n, -1);
    int x = v[0].i, y = v[0].w;
    // The overlapping v for a given i is the v with the minimum width for a given prefix
    for(int i=1; i<n; i++){
        if(v[i].w > y){
            overlap[v[i].i] = x;
        } else {
            x = v[i].i;
            y = v[i].w;
        }
    }
    f(i, n)cout << overlap[i]+1 << " ";
    cout << en;
}

int main(){
    int t; cin >> t;
    f(i, t) solve(i);
}

// constexpr int N = 100000;
// ll t, n, m, k, a, b;
// vvi nums;
// vi res;
// void solve() {
//     sort(all(nums), [&](vi& a, vi& b) {
//         if(a[0]==b[0]) return a[1]<b[1];
//         return a[0]<b[0];
//     });
//     cout<<"nums "<<nums<<en;
//     // map ==y vals to end of streak
//     vi pos(2*n);
//     repr(i, 2*n, 0) {
//         int it=i;
//         pos[i]=i;
//         while(it>0 && nums[it][0]==nums[it-1][0]) {
//             pos[--it]=i;
//         }
//         i=it;
//     }
//     cout<<"pos "<<pos<<en;
//
//     // Do suffix max
//     vpii suffixMax(2*n);
//     suffixMax[2*n-1]={nums[2*n-1][1], 2*n-1};
//     repr(i, 2*n-1, 0) {
//         auto [x, pos] = suffixMax[i+1];
//         if(nums[i][1] > x) {
//             suffixMax[i] = {nums[i][1], i};
//         } else {
//             suffixMax[i] = suffixMax[i+1];
//         }
//     }
//     cout<<"suf "<<suffixMax<<en;
//
//     // Try to find
//     f(i, 2*n) {
//         auto [mx, j] = suffixMax[pos[i]];
//         if(mx > nums[i][1]) res[nums[j][2]] = nums[i][2]+1;
//     }
// }
//
// int main() {
//     ios::sync_with_stdio(false); cin.tie(nullptr);
//     cin>>t;
//     f(i, t) {
//         cin>>n;
//         nums.assign(2*n, vi()); res.assign(n, -1);
//         f(i, n) {
//             int x, y; cin>>x>>y;
//             nums[i]={x, y, i};
//             nums[i+n]={y, x, i};
//         }
//         solve();
//         for(int x : res) cout<<x<<SP;
//         cout<<en;
//     }
// }