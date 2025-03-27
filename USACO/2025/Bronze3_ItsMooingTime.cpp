#include <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define repr(i, a, b) for (int i = (a); i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define all(x) begin(x), end(x)
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");

#define int long long
tpl_<tn_ T>
using v = vector<T>;
using ll=long long;
using pii=pair<int,int>;
using vi=v<int>;
using vvi=v<vi>;
int N = 100000;
int MOD=1e9+7;
constexpr int INFL=0x3f3f3f3f3f3f3f3f;
constexpr auto en = "\n"; constexpr auto sp = " ";
tpl_<class It, class T>     auto leq_bound  (It first, It last, T val) { auto it = upper_bound(first, last, val); return it != first ? prev(it) : last;} tpl_<class C, class T>auto leq_bound(C& c, T val) {auto it = c.upper_bound(val);return it != c.begin() ? prev(it) : c.end();}
tpl_<class It, class T>     auto less_bound (It first, It last, T val) {auto it = lower_bound(first, last, val);return it != first ? prev(it) : last; }tpl_<class C, class T>auto less_bound(C& c, T val) {auto it = c.lower_bound(val);return it != c.begin() ? prev(it) : c.end();}
tpl_<class T> bool       ckmn(T& a, const T& b) {return b < a ? a = b, 1 : 0;}  tpl_<class T> bool ckmx(T& a, const T& b) {return a < b ? a = b, 1 : 0;}

int t, k, n, m;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>k;
    string s; cin>>s;
    vi a(n); f(i, n) a[i] = s[i]-'a';
    vvi pos(26);
    vvi notpos(26);
    f(i, n) {
        f(j, 26) {
            if(j == a[i]) pos[j].pb(i);
            else notpos[j].pb(i);
        }
    }
    f(i, k) {
        int l, r; cin>>l>>r; l--; r--;
        int res = -1;
        f(c, 26) {
            auto right = leq_bound(all(pos[c]), r);
            auto left = lower_bound(all(notpos[c]), l);
            if(right == pos[c].end() || left == notpos[c].end() || *right < *left) {
                continue;
            }
            int rr = *right, ll = *left;
            // Correct but TLE
            // rep(i, ll+1, rr-1) {
            //     if(a[i]==c) ckmx(res, (i-ll) * (rr-i));
            // }
            int mid = (ll + rr) / 2;
            auto rit = lower_bound(all(pos[c]), mid);
            auto lit = leq_bound(all(pos[c]), mid);
            if(rit != pos[c].end() && ll < *rit && *rit < rr) ckmx(res, (*rit - ll) * (rr - *rit));
            if(lit != pos[c].end() && ll < *lit && *lit < rr) ckmx(res, (*lit - ll) * (rr - *lit));
        }
        if(res <= 0) cout<<-1<<en;
        else cout<<res<<en;
    }
}
