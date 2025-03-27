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
    int x, k; cin>>x>>k;
    vi res;
    repr(i, 5, 0) {
        if(k & (1<<i)) {
            int val = (1<<(1<<i))-1;
            res.pb(val); x -= val;
        }
    }
    if(x < 0) {
        cout<<-1<<en; return;
    }
    auto print = [&]() {
        cout<<res.size()<<en;
        for(int val : res) cout<<val<<sp;
        cout<<en;
    };
    if(__builtin_popcount(x) % 2 == 0) {
        repr(i, 31, 0) {
            if(x & (1<<i)) res.pb(1<<i);
        }
        print();
    } else {
        if(x==1) {
            if(res.back() == 1) {
                res.pop_back();
                res.push_back(2);
                print();
            } else {
                cout<<-1<<en;
            }
        } else {
            bool flag = false;
            rep(i, 0, 31) {
                if(x & (1<<i)) {
                    if(!flag && i > 0) {
                        flag = true;
                        res.pb(1<<(i-1)); res.pb(1<<(i-1));
                    } else {
                        res.pb(1<<i);
                    }
                }
            }
            print();
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin>>t; f(i, t) solve();
}
