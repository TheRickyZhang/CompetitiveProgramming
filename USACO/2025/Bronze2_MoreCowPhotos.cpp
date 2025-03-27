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

int t, k, n, m;
void solve() {
    cin>>n;
    vi a(n); f(i, n) cin>>a[i];
    vi freq(n+1, 0);
    f(i, n) freq[a[i]]++;
    int res = 0;
    bool mid = false;
    repr(i, n, 0) {
        if(!mid && freq[i] > 0) {
            res++;
            mid = true;
        } else {
            if(freq[i] >= 2) res += 2;
        }
    }
    cout<<res<<en;
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin>>t; f(i, t) solve();
}
