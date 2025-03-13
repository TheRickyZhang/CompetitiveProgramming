#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pl=pair<ll,ll>;
const int N=1e5+5,P=1e9+7;
struct S
{
    ll a,b;
    S():a(0),b(1){};
    S(ll x,ll y):a(x%P),b(y%P){};
}e(1,0);
S operator+(const S&x,const S&y)
{
    return S(x.a+y.a,x.b+y.b);
}
S operator*(const S&x,const S&y)
{
    auto&[A,B]=x;auto&[C,D]=y;
    return S(A*D+B*C+A*C,B*D+A*C);
}
S operator^(S a,int b)
{
    S r;
    for(;b;a=a*a,b>>=1)if(b&1)r=r*a;
    return r;
}
struct
{
    S vl,mu;
}t[N*4];
void U(int o)
{
    t[o].vl=t[o*2].vl+t[o*2+1].vl;
}
void Ap(int o,S mu)
{
    t[o].vl=t[o].vl*mu,t[o].mu=t[o].mu*mu;
}
void D(int o)
{
    if(!t[o].mu.a&&t[o].mu.b==1)
        return;
    Ap(o*2,t[o].mu),Ap(o*2+1,t[o].mu);
    t[o].mu=S();
}
void C(int o,int L,int R,int l,int r,S k)
{
    if(R<l||r<L)
        return;
    if(l<=L&&R<=r)
    {
        Ap(o,k);
        return;
    }
    D(o);
    int M=(L+R)/2;
    C(o*2,L,M,l,r,k),C(o*2+1,M+1,R,l,r,k);
    U(o);
}
ll Q(int o,int L,int R,int l,int r)
{
    if(R<l||r<L)
        return 0;
    if(l<=L&&R<=r)
        return t[o].vl.a;
    D(o);
    int M=(L+R)/2;
    return Q(o*2,L,M,l,r)+Q(o*2+1,M+1,R,l,r);
}
signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    int n,m;cin>>n>>m;
    for(int i=1,x;i<=n;i++)
        cin>>x,C(1,1,n,i,i,e^x);
    while(m--)
    {
        int op,l,r;cin>>op>>l>>r;
        if(op==1)
        {
            int x;cin>>x,C(1,1,n,l,r,e^x);
        }
        else
        {
            cout<<Q(1,1,n,l,r)%P<<'\n';
        }
    }
    return 0;
}