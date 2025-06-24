#include<bits/stdc++.h>
using namespace std;

const int N=3e5+5;
int n=0,q=0,a[N]={},b[N]={},c[N]={};
int x[N]={},y[N]={},z[N]={};

inline void init() {
    for(int i=1;i<=n;i++) a[i]=b[i]=c[i]=0;
    for(int i=1;i<=q;i++) x[i]=y[i]=z[i]=0;
    n=q=0;
}

inline void solve() {
    cin>>n>>q;
    for(int i=1;i<=n;i++) {
        cin>>b[i];
        c[i]=b[i];
    }
    for(int i=1;i<=q;i++) cin>>x[i]>>y[i]>>z[i];
    for(int i=q;i>=1;i--) {
        int v=c[z[i]];
        c[z[i]]=0;
        c[x[i]]=max(c[x[i]],v),c[y[i]]=max(c[y[i]],v);
    }
    for(int i=1;i<=n;i++) a[i]=c[i];
    for(int i=1;i<=q;i++) c[z[i]]=min(c[x[i]],c[y[i]]);
    for(int i=1;i<=n;i++)
        if(b[i]!=c[i]) {
            cout<<"-1\n";
            return;
        }
    for(int i=1;i<=n;i++) cout<<a[i]<<' ';
    cout<<'\n';
}

int T=0;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    for(int i=0;i<T;i++) init(),solve();

    return 0;
}
