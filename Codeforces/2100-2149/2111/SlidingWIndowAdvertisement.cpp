#include <bits/stdc++.h>
using namespace std;
#define tpl_ template
#define tn_ typename
#define f(i,to) for(int i=0;i<(to);++i)
#define repr(i,a,b) for(int i=(a);i>=(b);--i)
#define int long long
#define sp " "
#define en "\n"
tpl_<tn_ T> using v=vector<T>;
using vi=v<int>;

// LiChao for max(lines) on x∈[0..N-1], with segment‐insertion
struct Li{
    struct L{ int m,b; };
    int N;
    v<L> st;
    Li(int n):N(n),st(4*n,{0,0}){}
    inline int eval(const L &l,int x){ return l.m*x + l.b; }
    // add line nw over node v covering [l..r]
    void add_line(L nw,int v,int l,int r){
        int m=(l+r)>>1;
        bool lef = eval(nw,l) > eval(st[v],l);
        bool mid = eval(nw,m) > eval(st[v],m);
        if(mid) swap(st[v],nw);
        if(l==r) return;
        if(lef!=mid) add_line(nw,v<<1,l,m);
        else      add_line(nw,v<<1|1,m+1,r);
    }
    // insert line over whole domain
    void add_line(int m,int b){ add_line({m,b},1,0,N-1); }
    // insert line over subsegment [ql..qr]
    void add_seg(L nw,int v,int l,int r,int ql,int qr){
        if(ql>r||qr<l) return;
        if(ql<=l&&r<=qr){ add_line(nw,v,l,r); return; }
        int m=(l+r)>>1;
        add_seg(nw,v<<1,l,m,ql,qr);
        add_seg(nw,v<<1|1,m+1,r,ql,qr);
    }
    void add_seg(int m,int b,int l,int r){ add_seg({m,b},1,0,N-1,l,r); }
    int query(int x){
        int v=1,l=0,r=N-1,ans=eval(st[1],x);
        while(l<r){
            int m=(l+r)>>1;
            if(x<=m){ v=v<<1; r=m; }
            else     { v=v<<1|1; l=m+1; }
            ans = max(ans, eval(st[v],x));
        }
        return ans;
    }
};

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,k; cin>>n>>k;
    vi h(n); f(i,n) cin>>h[i];

    // 1) prev/next smaller to get maximal span [L+1..R-1]
    vi L(n),R(n);
    {
        stack<int> st;
        f(i,n){
            while(!st.empty()&&h[st.top()]>=h[i]) st.pop();
            L[i] = st.empty()?-1:st.top();
            st.push(i);
        }
        while(!st.empty()) st.pop();
        repr(i,n-1,0){
            while(!st.empty()&&h[st.top()]>h[i]) st.pop();
            R[i] = st.empty()?n:st.top();
            st.push(i);
        }
    }

    int M = n - k + 1;             // number of windows
    Li lc(M);

    // 2) for each j, add its 3 pieces over [start..end]
    f(j,n){
        int spanL = L[j] + 1;
        int spanR = R[j] - 1;
        int s = spanR - spanL + 1;
        int lo = max((int)0, spanL - k + 1);
        int hi = min(M-1, spanR);
        if(lo>hi) continue;
        int hj = h[j];

        // rising  f(i)=hj*(i + k - spanL)  on [lo.. min(spanL,hi)]
        int r1_lo = lo, r1_hi = min(spanL,hi);
        if(r1_lo<=r1_hi)
            lc.add_seg(hj, hj*(k - spanL), r1_lo, r1_hi);

        // constant f(i)=hj*k  on windows fully inside span
        if(s>=k){
            int c_lo = max(spanL, lo);
            int c_hi = min(hi, spanR - k + 1);
            if(c_lo<=c_hi)
                lc.add_seg(0, hj*k, c_lo, c_hi);
        }

        // falling   f(i)=hj*(spanR - i +1) = -hj*i + hj*(spanR+1)
        int f_lo = max(lo, spanR - k + 1);
        int f_hi = hi;
        if(f_lo<=f_hi)
            lc.add_seg(-hj, hj*(spanR + 1), f_lo, f_hi);
    }

    // 3) answer each window‐start
    for(int i=0;i<M;++i){
        cout<<lc.query(i)<<sp;
    }
    cout<<en;
    return 0;
}
