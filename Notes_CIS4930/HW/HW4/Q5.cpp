class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int currMax = 0;
        int curr = 0;
        int res = 0;
        for(int i = 0; i < n-1; ++i) {
            currMax = max(currMax, i+nums[i]);
            if(i==curr) {
                res++;
                curr = currMax;
            }
        }
        return res;
    }
};