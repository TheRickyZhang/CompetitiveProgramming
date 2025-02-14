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
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpii vector<pair<int, int>>
#define vb vector<bool>
#define vvb vector<vector<bool>>

#define int long long
#define str string
int N = 10000; int MOD=1e9+7; constexpr int INF=1e9; constexpr int INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";


int t, k, n, m;
void solve() {
    
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    str s; cin>>s;
    n = s.size();
    vi dp(n+1, 0);
    dp[0] = dp[1] = 1;
    f(i, n) {
        if(s[i]=='m' || s[i]=='w') {
            cout<<0<<en; return 0;
        }
    }
    rep(i, 1, n-1) {
        if(s[i] == s[i-1] && (s[i] == 'u' || s[i] == 'n')) {
            // cout<<"HAPPENEING AT CHAR "<<s[i]<<sp<<i<<en;
            dp[i+1] = (dp[i] + dp[i-1]) % MOD;
        } else {
            dp[i+1] = dp[i];
        }
    }
    // for(int x : dp) cout<<x<<sp;
    // cout<<en<<"  ";
    // f(i, n) cout<<s[i]<<sp;
    // cout<<en;en
    cout<<dp[n] % MOD<<en;
}
