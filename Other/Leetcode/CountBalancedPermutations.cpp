#include <bits/stdc++.h>
using namespace std;
using vi = vector<long long>;
using vvi = vector<vi>;
#define f(i,to) for(int i=0;i<to;++i)
#define fe(i,to) for(int i=1;i<=to;++i)
#define repr(i,a,b) for(int i=a;i>=b;--i)
static const int MOD = 1000000007;
auto en = "\n";

class Solution {
public:
    int countBalancedPermutations(string num) {
        // now every "int" is really "long long"
#define int long long

        auto add = [&](int a, int b){ return (a + b < MOD ? a + b : a + b - MOD); };
        auto mult = [&](int a, int b){ return int((long long)a * b % MOD); };
        auto fpow = [&](int a, int e){
            int r = 1;
            while(e){
                if(e & 1) r = mult(r, a);
                a = mult(a, a);
                e >>= 1;
            }
            return r;
        };
        auto inv = [&](int x){ return fpow(x, MOD-2); };

        int n = num.size();
        vi a(n); f(i, n) a[i] = num[i] - '0';
        int tot = accumulate(a.begin(), a.end(), 0LL);
        if (tot & 1) {
#undef int
            return 0;
        }
        int cnt = n/2;
        tot >>= 1;

        vi freq(10, 0);
        f(i, n) freq[a[i]]++;

        vi fa(81, 1), ifa(81);
        fe(i, 80) fa[i] = mult(fa[i-1], i);
        ifa[80] = inv(fa[80]);
        repr(i, 79, 0) ifa[i] = mult(ifa[i+1], i+1);

        vvi dp(tot+1, vi(cnt+1, 0));
        dp[0][0] = 1;
        for (int x : a) {
            repr(i, tot, x)
                repr(j, cnt, 1)
                    dp[i][j] = add(dp[i][j], dp[i-x][j-1]);
        }

        int res = dp[tot][cnt];
        res = mult(mult(res, fa[cnt]), fa[n-cnt]);
        f(d, 10) res = mult(res, ifa[freq[d]]);

#undef int
        return (int)res;
    }
};
