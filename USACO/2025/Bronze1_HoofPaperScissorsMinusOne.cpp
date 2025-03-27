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
    
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>m;
    v<bitset<3000>> beat(n);
    f(i, n) {
        string s; cin>>s;
        f(j, s.size()) {
            if(s[j] == 'W') beat[j].set(i);
            else if(s[j] == 'L') beat[i].set(j);
        }
    }
    f(i, m) {
        int a, b; cin>>a>>b; a--; b--;
        int good = (beat[a] & beat[b]).count();
        int res = 2 * good * n - good * good;
        cout<<res<<en;
    }
}
