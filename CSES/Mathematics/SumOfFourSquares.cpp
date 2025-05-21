#include <bits/stdc++.h>
using namespace std;
#define f(i,to) for(int i=0;i<(to);++i)
#define tpl_ template
#define tn_ typename
#define str string
#define int long long
#define en "\n"
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin>>T;
    vector<int> ns(T);
    int m=0;
    f(i,T){ cin>>ns[i]; m = max(m, ns[i]); }

    vector<pair<int,int>> rep(m+1, {-1,-1});
    rep[0] = {0,0};
    for(int c=0; c*c<=m; ++c)
        for(int d=0; c*c + d*d<=m; ++d){
            int s = c*c + d*d;
            if(rep[s].first < 0) rep[s] = {c,d};
        }

    f(i,T){
            int n = ns[i];
            bool ok = false;
            for(int a=0; a*a<=n && !ok; ++a){
                int a2 = a*a;
                for(int b=0; a2 + b*b<=n; ++b){
                    int rem = n - a2 - b*b;
                    auto [c,d] = rep[rem];
                    if(c >= 0){
                        cout<<a<<" "<<b<<" "<<c<<" "<<d<<en;
                        ok = true;
                        break;
                    }
                }
            }
        }
}
