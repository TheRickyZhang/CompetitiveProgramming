#include <bits/stdc++.h>
using namespace std;

using vi=vector<int>; using ll=long long; using vll=vector<long long>; using vb=vector<bool>; using vs=vector<string>; using pii=pair<int, int>;
using pll=pair<ll, ll>; using vpii=vector<pii>; using vvpii=vector<vpii>; using vpll=vector<pll>; using vvpll=vector<vpll>; using pq=priority_queue<ll>; using pqq=priority_queue<pll>;
using vvi=vector<vector<int>>; using vvll=vector<vector<ll>>; using mpq=priority_queue<ll, vector<ll>, greater<>>; using mpqq=priority_queue<pll, vpll, greater<>>;
#define ump unordered_map
#define ust unordered_set
#define f(i, to) for (int i=0; i < (to); ++i)
#define fe(i, to) for (int i=1; i <= (to); ++i)
#define rep(i, a, b) for (int i=(a); i < (b); ++i)
#define repr(i, a, b) for (int i=(a)-1; i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");
constexpr int MOD=1000000007; constexpr ll INF=INT_MAX-37; constexpr ll INFL=0x3f3f3f3f3f3f3f3f; const vector<pii> dirs={{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
constexpr char EN='\n'; constexpr char SP=' '; auto en=EN; auto sp=SP;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T=enable_if_t<!is_same_v<T_container, string>, typename T_container::value_type>> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep=", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep=", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue=0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check=[](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };

void solve() {
    ll n; cin >> n;
    vll nums(n);
    ll pos=-1; // should be same answer even with pos==-1
    f(i, n) {
        cin>>nums[i];
        if(abs(nums[i]) != 1) pos=i;
    }
    if(pos == -1) {
        ll cmx = 0, mx = 0, cmn = 0, mn = 0;
        f(i, n) {
            cmx = max(nums[i], cmx + nums[i]);
            mx = max(mx, cmx);
            cmn = min(nums[i], cmn + nums[i]);
            mn = min(mn, cmn);
        }
        cout << (mx - mn + 1) << en;
        for(int i = mn; i <= mx; ++i) cout << i << " ";
        cout << en;
        return;
    }

    ll lmn=0, lmx=0;
    ll rmn=0, rmx=0;
    vll premx(n,0);
    vll premn(n, 0);

    ll a=0, b=0;
    repr(i, pos, 0) {
        lmn=min(lmn, a=min(a + nums[i], a));
        lmx=max(lmx, b=max(b + nums[i], nums[i]));
    }
    a=0, b=0;
    rep(i, pos+1, n) {
        rmn=min(rmn, a=min(a + nums[i], a));
        rmx=max(rmx, b=max(b + nums[i], nums[i]));
    }

    ll curr=0;
    repr(i, pos, 0) {
        curr += nums[i];
        premx[i]=max(premx[i + 1], curr);
        premn[i]=min(premn[i + 1], curr);
    }
    curr=0;
    rep(i, pos+1, n) {
        curr += nums[i];
        premx[i]=max(premx[i - 1], curr);
        premn[i]=min(premn[i - 1], curr);
    }

    ll clmn=premn[0], crmn=premn[n-1], clmx=premx[0], crmx=premx[n-1];
    ll l=min({0LL, clmn, crmn, clmn+crmn}); ll r=max({0LL, clmx, crmx, clmx+crmx});
    l+=nums[pos]; r+=nums[pos];
    // cout << lmn << SP << lmx << SP << rmn << SP << rmx << SP << l << SP << r << en;

    vpll pairs={{lmn, lmx}, {rmn, rmx}, {l, r}};
    sort(all(pairs));
    // for(auto [a, b] : pairs) cout<<a<<SP<<b<<","<<en;

    // Merge
    vpll res={pairs[0]};
    if(pairs[1].ff <= res.back().ss) res.back().ss=max(res.back().ss, pairs[1].ss);
    else res.pb(pairs[1]);
    if(pairs[2].ff <= res.back().ss) res.back().ss=max(res.back().ss, pairs[2].ss);
    else res.pb(pairs[2]);

    ll cnt=0;
    for(auto [l, r] : res) cnt += r-l+1;
    cout<<cnt<<en;
    for(auto [l, r] : res) rep(i, l, r+1) cout<<i<<SP;
    cout<<en;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin>>t; f(i, t) solve();
}