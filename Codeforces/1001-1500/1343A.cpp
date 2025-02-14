#include <bits/stdc++.h>
using namespace std;

#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define repr(i, a, b) for (int i = (a); i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define all(x) begin(x), end(x)

#define int long long
#define str string
int N = 10000; int MOD=1e9+7; constexpr int INF=1e9; constexpr int INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";


int t, k, n, m;
void solve() {
    cin>>n;
    for(int i = 4; i <= n+1; i <<= 1) {
        if(n % (i-1) == 0) {
            cout<<n/(i-1)<<en;
            return;
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin>>t; f(i, t) solve();
}