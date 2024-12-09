class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        sort(citations.begin(), citations.end());
        int l = 0;
        int r = n-1;
        int mid;
        while(l <= r) {
            mid = l + (r-l) / 2;
            if(citations[mid] == n-mid) return citations[mid];
            if(citations[mid] > n-mid) {
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
        return n-l;
    }
};