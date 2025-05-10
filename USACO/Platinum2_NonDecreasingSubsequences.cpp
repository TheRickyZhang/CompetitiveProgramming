#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,n) for(int i=0;i<(n);++i)
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define repr(i,a,b) for(int i=(a);i>=(b);--i)
#define vi vector<int>
#define en "\n"
const int MOD = 1000000007;

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,k; cin>>n>>k;
    vi A(n);
    f(i,n){ cin>>A[i]; --A[i]; }

    int Q; cin>>Q;
    vi l(Q), r(Q), qid(Q), ans(Q);
    f(i,Q){
        cin>>l[i]>>r[i];
        --l[i]; --r[i];
        qid[i]=i;
    }

    vector<array<int,21>> lres(n), rres(n);
    int cnt[21];

    auto countLeft = [&](int a,int b){
        rep(i,a,b) f(j,k) lres[i][j]=0;
        for(int v=k-1; v>=0; --v){
            rep(j,v,k-1) cnt[j]=0;
            repr(i,b,a){
                if(A[i]==v){
                    cnt[v] = (2*cnt[v] + 1) % MOD;
                    rep(j,v+1,k-1)
                        cnt[j] = (2*cnt[j] + lres[i][j]) % MOD;
                }
                rep(j,v,k-1)
                    lres[i][j] = (lres[i][j] + cnt[j]) % MOD;
            }
        }
        // make cumulative so lres[i][j] = sum of exact up to j
        rep(i,a,b) rep(j,1,k-1)
            lres[i][j] = (lres[i][j] + lres[i][j-1]) % MOD;
    };

    auto countRight = [&](int a,int b){
        rep(i,a,b) f(j,k) rres[i][j]=0;
        rep(v,0,k-1){
            rep(j,0,v) cnt[j]=0;
            rep(i,a,b){
                if(A[i]==v){
                    cnt[v] = (2*cnt[v] + 1) % MOD;
                    rep(j,0,v-1)
                        cnt[j] = (2*cnt[j] + rres[i][j]) % MOD;
                }
                rep(j,0,v)
                    rres[i][j] = (rres[i][j] + cnt[j]) % MOD;
            }
        }
        // make cumulative so rres[i][j] = sum from j..end
        rep(i,a,b) repr(j,k-2,0)
            rres[i][j] = (rres[i][j] + rres[i][j+1]) % MOD;
    };

    function<void(int,int,int,int)> solve = [&](int a,int b,int qa,int qb){
        if(a>b||qa>qb) return;
        if(a==b){
            rep(x,qa,qb) ans[qid[x]] = 1;
            return;
        }
        int m=(a+b)>>1;
        countLeft(a,m);
        countRight(m+1,b);

        int keep=0;
        rep(x,qa,qb){
            int q=qid[x], L=l[q], R=r[q];
            if(L<=m && R>m){
                int prev=0, cross=0;
                rep(j,0,k-1){
                    int f_exact = (lres[L][j] - prev + MOD) % MOD;
                    cross = (cross + f_exact * rres[R][j]) % MOD;
                    prev = lres[L][j];
                }
                int cur = (cross
                         + lres[L][k-1]
                         + rres[R][0]
                         + 1) % MOD;
                ans[q] = cur;
            } else {
                qid[qa+keep++] = q;
            }
        }
        int mid=qa;
        rep(x,qa,qa+keep-1){
            if(r[qid[x]] <= m){
                swap(qid[x], qid[mid]);
                mid++;
            }
        }
        solve(a,   m,  qa,    mid-1);
        solve(m+1, b,  mid,   qa+keep-1);
    };

    solve(0,n-1,0,Q-1);
    f(i,Q) cout<<ans[i]<<en;
    return 0;
}
