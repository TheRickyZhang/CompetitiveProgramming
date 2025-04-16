#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define N 200000

int i,j,k,n,m,t,res[N+50],f[N+50];
basic_string<int> v[N+50];
vector<pair<int,int> > q[N+50];

struct SB{
#define md ((l+r)/2)
#define ls (id*2)
#define rs (ls+1)
    int f[N*4+50];
    void add(int id,int l,int r,int x,int y){
        if(l==r){f[id]=y; return;}
        if(x<=md)add(ls,l,md,x,y);
        else add(rs,md+1,r,x,y);
        f[id]=max(f[ls],f[rs]);
    }
    int get(int id,int l,int r,int x,int y){
        if(x>y)return -1e9;
        if(x<=l&&r<=y)return f[id];
        int res=-1e9;
        if(x<=md)res=max(res,get(ls,l,md,x,y));
        if(y>md)res=max(res,get(rs,md+1,r,x,y));
        return res;
    }
}sb;

void dfs0(int x,int fa){
    for(auto i:v[x])if(i!=fa){dfs0(i,x); f[x]=max(f[x],f[i]+1);}
}

void dfs1(int x,int fa,int d){
    for(auto [id,w]:q[x]){
        res[id]=max(f[x],sb.get(1,1,n,max(1,d-w),d-1)-(N-d));
    }
    int mx1=0,i1=0,mx2=0;
    for(auto i:v[x])if(i!=fa){
        if(f[i]+1>mx1){
            mx2=mx1; mx1=f[i]+1; i1=i;
        }
        else mx2=max(mx2,f[i]+1);
    }
    for(auto i:v[x])if(i!=fa){
        sb.add(1,1,n,d,(i==i1?mx2:mx1)+(N-d));
        dfs1(i,x,d+1);
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(i=1;i<n;i++){
            cin>>j>>k; v[j]+=k; v[k]+=j;
        }
        cin>>m;
        for(i=1;i<=m;i++){
            res[i]=0; cin>>j>>k;
            q[j].push_back({i,k});
        }
        dfs0(1,0); dfs1(1,0,1);
        for(i=1;i<=m;i++)cout<<res[i]<<' '; cout<<'\n';
        for(i=1;i<=n;i++){
            q[i]={}; v[i]={}; f[i]=0;
        }
    }
}
