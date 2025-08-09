#include <bits/stdc++.h>
using namespace std;
#define f(i,to) for(int i=0;i<(to);++i)
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define repr(i,a,b) for(int i=(a);i>=(b);--i)
using ll = long long;
using vi = vector<ll>;
const char en = '\n';

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        vi p(n), s(n);
        f(i,n) cin>>p[i];
       f(i,n) cin>>s[i];
        bool ok = true;
        // prefix and suffix must be monotonic
        rep(i,1,n-1) if(p[i-1]%p[i]!=0) ok=false;
        rep(i,1,n-1) if(s[i]%s[i-1]!=0) ok=false;
        if(!ok){
            cout<<"No"<<en;
            continue;
        }
        // reconstruct a[i] = lcm(p[i], s[i])
        vi a(n);
        f(i,n) a[i] = lcm(p[i], s[i]);
        // recompute prefix and suffix gcds
        vi pre(n), suf(n);
        pre[0] = a[0];
        rep(i,1,n-1) pre[i] = gcd(pre[i-1], a[i]);
        suf[n-1] = a[n-1];
        repr(i,n-2,0) suf[i] = gcd(suf[i+1], a[i]);
        f(i,n){
            if(pre[i]!=p[i] || suf[i]!=s[i]){
                ok = false;
                break;
            }
        }
        cout<<(ok?"Yes":"No")<<en;
    }
    return 0;
}
