import java.util.ArrayList;
import java.util.Arrays;

class Solution {
    static final int MOD = 1_000_000_007;

    private int add(int x, int y) {
        int s = x + y;
        return s >= MOD ? s - MOD : s;
    }

    private int mul(int x, int y) {
        return (int)((long)x * y % MOD);
    }

    private int fpow(int x, int p) {
        int res = 1;
        while (p > 0) {
            if ((p & 1) == 1) res = mul(res, x);
            x = mul(x, x);
            p >>= 1;
        }
        return res;
    }

    public int countBalancedPermutations(String num) {
        int n = num.length();
        ArrayList<Integer> a = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            a.add(num.charAt(i) - '0');
        }

        int tot = 0;
        for (int x : a) tot += x;
        if ((tot & 1) == 1) return 0;
        tot >>= 1;
        int half = n / 2;

        int[][] dp = new int[tot+1][half+1];
        dp[0][0] = 1;
        for (int x : a) {
            for (int s = tot - x; s >= 0; s--) {
                for (int k = half - 1; k >= 0; k--) {
                    dp[s+x][k+1] = add(dp[s+x][k+1], dp[s][k]);
                }
            }
        }
        int res = dp[tot][half];

        int[] freq = new int[10];
        for (int x : a) freq[x]++;

        int[] fa = new int[n+1], ifa = new int[n+1];
        fa[0] = 1;
        for (int i = 1; i <= n; i++) {
            fa[i] = mul(fa[i-1], i);
        }
        ifa[n] = fpow(fa[n], MOD-2);
        for (int i = n; i >= 1; i--) {
            ifa[i-1] = mul(ifa[i], i);
        }

        res = mul(res, fa[half]);
        res = mul(res, fa[n-half]);
        for (int f : freq) {
            res = mul(res, ifa[f]);
        }

        return res;
    }
}
