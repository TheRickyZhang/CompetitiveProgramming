// Range DP:
f(len, n) { // 1 less than len
    f(i, n-len) {  // Starting point
        int k = i+len; // Ending point
        rep(j, i, k-1) { // Mid point
            ckmn(dp[i][k], dp[i][j] + dp[j+1][k] - (nums[i]==nums[k]));
        }
    }
}

// Digit DP
// Key idea: [i][j][k] = {index, digit val, tightness flag of max searchable{
// Count numbers divisible by 3;

str s = to_string(x);
int n = s.size();
int m; // Based of specific condition
int dp[len+1][m][2];
memset(dp, 0, sizeof(dp));

int dp[n+1][m][2];
memset(dp, 0, sizeof(dp));
dp[0][0][1] = 1; // Very first digit (tight) = 1 way
f(i, n+1) {
    f(j, m) {
        f(k, 2) {
            int ii = n-i-1;
            int dd = s[ii]-'0';
            int mx = k ? int(s[i]-'0') : 9; // If bounded, only iterate up to that digit
            for(int d = 0; d <= mx; ++d) {
                // Specific condition -> early break;

                // count numbers mod m: no checks
                // count palindromes:
                if(d != dd) continue;
                // Magic numbers (same # at even indices) https://codeforces.com/contest/628/problem/D
                if((i % 2 == 0) && d != givend) continue;
                if((i % 2 == 1) && d == givend) continue;

                if(!i && !d) continue; // Only need to skip pos 0, 0 (leading 0)
                int ni = i+1;
                int nj = (10*j + p) % m;
                int nk = k && (d==int(s[i]-'0'));
                dp[ni][nj][nk] += dp[i][j][k];
            }
        }
    }
}
int res = accumulate(all(dp[n][0]), 0); // Every end pos state 0 mod m
