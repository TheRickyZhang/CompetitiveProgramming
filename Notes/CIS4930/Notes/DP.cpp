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



/* DP On Graphs
Example - define a subtree* to be any set of connected vertices in a graph G (this is different from usual definition!).
Find the number of subtrees of size <= k in graph.

First, ignore k limitation.
It is natural to define f(u) as the number of subtrees including u, and g(u) as the number of subtrees excluding u.
    If the children of u are {v1, v2, ...}, then f(u) = MULT(f(v)+1), since we can pick any combination of f from children, including empty.
    Then, g(u) = SUM(f(v) + g(v)), as without the root, we only pick from each of the children without combination.

Now let's consider k. It is natural to extend f to f(u, k), counting subtrees of size k.
    Then for f, we can still combine any number of f for children, but with the restriction that SUM(a) = k-1.
    So, f(u, k) = SUM(PROD(f(v, a) | SUM(a) = k-1)
    g remains similar as g(u, k) = SUM(f(v, k) + g(v, k)). We notice that the k can be dropped.

All that's left to remain is to figure out how the f transition can be calculated efficiently. We can use traditional coin-sum DP:
    Let dp[i][j] = first i children, current sum j. Then dp[i][j] = SUM(dp[i-1][j-k] * f(i, k) for all k={0, K})
*/


/*
 *  Practice - minimum cost to delete nodes to a tree with k leafs
 *
 *  Let f = (u, k) be the minimum cost for the tree rooted at u to have k leaves
 *      Our base case is f(u, 1) = 0 if deg(u) = 0
 *      Then f(u, k) = MIN(SUM(f(v, a)) | SUM(a) = k)
 *      But we should also consider the cost of deleting a node. Thus, f(u, 0) = SUM(c(u)) for the subtree
 *
 *  In this case, a separate function g is not required, as the state update is already addressed in f.
 *
 *  So, we use dp[i][j] = {index of v, num leafs} with transition dp[i][j] = MIN(dp[i-1][a-k] * f(i, k)) for k={1, K}
 */