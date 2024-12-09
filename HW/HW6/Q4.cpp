class Solution {
public:
    vector<vector<int>> dp;
    int solve(int rm, vector<int>& coins, int i) {
        if(i < 0 || rm < 0) return 0;
        if(rm == 0) return 1;
        if(dp[i][rm] != -1) return dp[i][rm];
        return dp[i][rm] = solve(rm-coins[i], coins, i) + solve(rm, coins, i-1);
    }
    int change(int amount, vector<int>& coins) {
        dp.resize(coins.size(), vector<int>(amount+1, -1));
        return solve(amount, coins, coins.size()-1);
    }
};