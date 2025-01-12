// Generate subsets recursively and iteratively
#include <bits/stdc++.h>
using namespace std;
void generateSubsetsRecursively(int idx, int n, vector<int> &subset)
{
    if (idx == n) // Do something with subset
    else {
        recurse(idx+1, n, subset);
        subset.push_back(idx);
        recurse(idx+1, n, subset);
        subset.pop_back();
    }
}

void generateSubsetsIteratively(int n) {
    for(int i = 0; i < (1 << n); ++i) {
        vector<int> subset;
        for(int j = 0; j < n; ++j) {
            if(i & (1 << j)) {
                subset.push_back(j);
            }
        }
        // Do something with subste
    }
}

// Generate permutations

// Maintain permutation and chosen vectors, check (set push) function (set pop)
void generatePermutationsR(int n, vector<int>& permutation, vector<int>& chosen) {
    if(permutation.size() == n) {
        // Do something
    } else {
        for(int i = 0; i < n; ++i) {
            if(chosen[i]) continue;

            chosen[i] = true;
            permutation.push_back(i);

            generatePermutationsR(n, permutation, chosen);

            chosen[i] = false;
            permutation.pop_back();
        }
    }
}

// Use do-while next_permutation, must start with already sorted order
void generatePermutationsI(int n) {
    vector<int> permutation;
    for(int i = 0; i < n; ++i) {
        permutation.push_back(i);
    }
    do {
        // Do something
    } while (next_permutation(permutation.begin(), permutation.end()));
}

// Backtracking
void generalBacktrack(int depth, int n, auto& state, auto& options, auto& res, auto isValid) {
    if (depth == n) {
        // Do something with res, ex count++ or push_back(state)
    } else {
        for (const auto& option : options) {
            if (!isValid(state, option)) continue;
            state.push_back(option);
            generalBacktrack(depth + 1, n, state, options, res, isValid);
            state.pop_back();
        }
    }
}

// Specific example to N-queens - can simplify problem by only iterating through rows and checking attacks with
// col, diag1, and diag2 arrays, while y is in header. Works since nxn board and symmetry of n queens
void NQueens(int y, int n, int& count, vector<int>& column, vector<int>& diag1, vector<int>& diag2) {
    if (y == n) {
        count++;
        return;
    }
    for (int x = 0; x < n; x++) {
        if (column[x] || diag1[x + y] || diag2[x - y + n - 1]) continue;
        column[x] = diag1[x + y] = diag2[x - y + n - 1] = 1;
        NQueens(y + 1, n, count, column, diag1, diag2);
        column[x] = diag1[x + y] = diag2[x - y + n - 1] = 0;
    }
}

// General solving strategies:
// Scheduling - select earliest end times
// Task and deadline scores - select shortest tasks first
// Minimize sum of (a-n): n=median, minimize (a-n^2): n = mean

// Dynamic programming

// Recursive. initialize dp to INF here. Afterward, return dp[n]
int minCoins(int x, vector<int>& coins, vector<int>& dp) {
    if(x < 0) return INF;
    if(x == 0) return 0;
    if(dp[x] != INF) return dp[x];
    for(int c : coins) {
        dp[x] = min(dp[x], minCoins(x-c, coins, dp)+1);
    }
    return dp[x];
}

// Iterative - preferred for efficiency
void minCoins(vector<int>& coins) {
    vector<int>dp(n, INF);
    dp[0] = 0;
    for(int i = 0; i <= n; ++i) {
        for(int c : coins) {
            dp[i] = min(dp[i], dp[i-c]+1);
        }
    }
    return dp[n]
}

// Count number of solutions
void countCoinCombos(vi& coins) {
    vi dp(n, 0);
    dp[0] = 1;
    for(int x = 1; x <= n; ++x) {
        for(auto c : coins) {
            if(c-x >= 0) {
                dp[c] += dp[c-x];
            }
        }
    }
    return dp[n]
}

// Longest increasing subsequence - can do O(n^2) with dp iterating through past lengths, or use this:
int lengthOfLIS(vector<int>& nums) {
    vector<int> dp; // Instead of storing the LIS per index, store the smallest numbers in our subsequence (greedy)

    for (int num : nums) {
        // find the smallest spot num can be inserted, replacing larger numbers
        auto it = lower_bound(dp.begin(), dp.end(), num);
        if (it == dp.end()) {
            dp.push_back(num);
        } else {
            *it = num;
        }
    }

    // Note that even if replacing not the last element (invalid list), the length of the array is still accurate
    return dp.size();
}

// Knapsack Problem


void knapsackPossible(vi& weights) {
    vector<vector<bool>> dp(W + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;  // Base case: 0 weight with 0 items is always possible.

    for(int k = 1; k <= n; ++k) {
        for(int x = W; x >= w[k]; --x) {  // Iterate backwards to prevent overwriting.
            dp[x][k] |= dp[x - w[k]][k - 1];  // If x-w[k] is possible with k-1 items, x is possible with k items.
        }
    }
}

// Edit distance (Levenshtein distance)
void minEditDistance(string word1, string word2) {
    int m = word1.size(), n=word2.size();

    // Initialize the base cases of converting from empty string
    rep(i, 0, m+1) {
        dp[i][0] = i;
    }
    rep(j, 0, n+1) {
        dp[0][j] = j;
    }

    dp[m+1][n+1];
    dp[0][0] = 0; // Note: will need to shift index->index+1, as is common in dp for base case 0
    rep(i, 1, m) {
        rep(j, 1, n) {
            dp[i+1][j+1] = min({
               dp[i][j + 1],
               dp[i + 1][j],
               dp[i][j] + (word1[i] == word2[j] ? 0 : 1)
            })
        }
    }
    return dp[m][n];
}

// Domino tilings - think about how to represent strucutres in a different way. Ex can break into components and use
// dp row by row.


// Range queries

// Prefix sum - sum up everything to a certain index, so any subarray is prefix[end] - prefix[start-1]
// Can also do 2D prefix, where in rectangular grid of ABCD, S = S(D)-S(A)-S(B)-S(C)

// Precomputed minimum queries - Calculate minimum for all (a, b) where L=b-a+1 is a power of 2.
// Then, min(a, b) = min(dp[a][l/2], dp[b-l/2][l/2]

// Binary indexed tree/ Fenwick Tree = sum of log n, building blocks to build up an number w/ powers of 2s
// k & -k -> Lowest set bit, indicates steps needed in the tree to go to next pow 2.
// Note - tree[] is 1 larger than nums[]. Need to add 1 when going from class -> helper method calls
vi tree;
vi nums;
int n;

void add(int index, int val) {
    while(index <= n) {
        tree[index] += val;
        index += (k & -k);
    }
}

void sum(int end) {
    int res = 0;
    while(end >= 1) {
        res += tree[i];
        end -= (end & -end);
    }
    return res;
}

// -----------------------

FenwickTree(vi& nums) {
    this->n = nums.size();
    tree.resize(n+1, 0);
    this->nums = nums;
    rep(i, 0, n) {
        add(i+1, nums[i]);
    }
}

void update(int index, int val) {
    int diff = val - nums[index];
    nums[index] = val;
    add(index+1, diff);
}

int sumRange(int start, int end) {
    return sum(end+1) - sum(start);
}

// For things like count smaller numbers after self or range sum, need to compress actual values -> lengths THEN use tree
// Compression = map values of arr to rank
// Iterate in the order where the condition you're looking for would be satisfied if it is compared to previously computed values

// Segment Tree - note arr is stored from [n] -> [2n-1], with root at [1]. Remember to set += n, then i/=2
// Combine: min/max, gcd, and/xor/or
class SegmentTree {
    vi tree;
    int n;
    // tree should be set to up to 4n size
    // Note that you start at top (pos 0), then work way down using recursion
    // This is an example of finding min, but others would modify min logic for sum, max, etc
    void constructTree(vi arr, int low, int high, int pos) {
        if(low == high) {
            tree[pos] = arr[low];
            return;
        }
        int mid = (low+high)/2;
        constructTree(arr, low, mid, 2*pos + 1);
        constructTree(arr, mid+1, high, 2*pos+2;)
        tree[pos] = min(tree[2*pos+1], tree[2*pos+2]);
    }

    // L and H are boundaries of original query - needed to check if range is totally insider the query range
    int rangeMin(vi arr, int low, int high, int l, int h, int pos) {
        // Total overlap
        if(low <= l && high >= h) {
            return tree[pos]
        }
        // No overlap
        if(low > h || high < l) {
            return INT_MAX;
        }
        int mid = (low+high)/2;
        return min(range(low, mid), range(mid+1, high));
    }
};

// Bit operations
// x & (x-1) -> sets rightmost 1 to 0 (can test if pow 2)
// x | (x-1) -> inverts everything after rightmost 1
// x & -x -> returns rightmost 1
// Use for(i=0, i < (1<<n), i++) for subset iteration

// Represent states efficiently, etc. counting rectangles in black/white grid of all black corners = AND of numbers representing rows


// Can convert permutations to subsets
// Elevator problem - convert determine minimum number of rides if elevator has weight capacity w and arr of people weights.
// For each subset of people, calculate {min rides needed, min weight of last group}
// S = subset, p = person, max weight = x
// If last(S / p) + weight[p] <= x, can add p, else create new ride

vpii best[1<<N];
best[0] = {1,0}; // empty group

// Note: iterating through indices = subsets. This loop works because for all cases are processed in order (within next subset)
rep(s, 1, 1<<n) {
    best[s] = {n+1, 0} // Initialize to worst case value where every person needs ride
    rep(p, 0, n) {
        if(s&(1<<p)) {   // If include person p
            auto option = best[s^(1<<p)];   // ^ toggles to option where no person p.
            if(option.second + weight[p] <= x) {     // Key insight from above
                option.second += weight[p];
            } else {
                option.first++;
                option.second = weight[p];
            }
            best[s] = min(best[s], option);   // Works on pairs since first element = count, second element = used weight
        }
    }
}

// Graph algorithms
// Initialize adjList, dist (INF), visited structure, and min heap pair<int>
void dijkstra(int start, int end) {
    distance[start] = 0;
    pq.push({0, start});
    while(!pq.empty()) {
        int from = pq.top().second();
        pq.pop();

        if(processed[from]) continue;
        processed[from] = true;

        for(auto pair : adj[from]) {
            auto& [to, weight] = pair;
            if(distance[from] + weight < distance[to]) {
                distance[to] = distance[from] + weight;
                pq.push({distance[to], to});
            }
        }
    }
}

// Calculate max diameter of tree
unordered_map<Node*, int> toLeaf;
unordered_map<Node*, int> maxLength;

void dfs(Node* node) {
    if(node->children.empty()) {
        toLeaf[node] = 0;
        maxLength[node] = 0;
        return
    }
    // Take the max two child paths - simple in concept, may be more difficult to execute
    int maxToLeaf1 = 0, int maxToLeaf2 = 0;
    for(auto child : node->children) {
        dfs(child);
        int toLeaf = toLeaf[child]+1;
        // Assign this so that maxToLeaf1 >= maxToLeaf2
        if(toLeaf > min(maxToLeaf1, maxToLeaf2)) {
            min(maxToLeaf1, maxToLeaf2) = toLeaf;
        }
    }
    // Don't forget this step!
    toLeaf[node] = maxToLeaf1;
    int maxLengthThroughNode = maxToLeaf1 + maxToLeaf2;

    // Also need to search for
    int maxChildLength = 0;
    for(auto child : node->children) {
        maxChildLength = max(maxChildLength, maxLength[child]);
    }
    maxLength[node] = max(maxLengthThroughNode, maxChildLength);
}

// Smarter/easier algorithm - do two farthest searches, second = max distance


// Union find
vi link;
vi size;
rep(i, 0, n) link[i] = i;
rep(i, 0, n) size[i] = 1;

int find(int x) {
    if(link[x] == x) return x;
	return parent[x] == find(parent[x]);
}
bool isSameSet(int x, int y) {
    return find(x) == find(y);
}
void unite(int x, int Y) {
    int a = find(x);
    int b = find(y);
    if(size[a] < size[b]) {
        swap(a, b);
    }
    size[a] += size[b];
    link[b] = a;
}

// Topolical sort
unordered_map<int, vi> adjList;
vi inDegree;
queue<int> q;
while(!q.empty()) {
    int sz = q.size();
    rep(i, 0, sz) {
        int from = q.front();
        q.pop();
        for(int to : adjList[from]) {
            if(--inDegree[to] == 0) {
                q.push(to);
            }
        }
    }
}

// Floyd's turtle and hare algorithm for cycle detections (if only one successor):
// Use following steps (until meet): 1/2, 1/1, 0/1

// Can model subtree queries similar to binary indexed tree, where the id, value, and subtree size of each node are stored
// Lowest common answer can also be done in range query, though for single tests bfs can work

int choose(int n, int k){
	if(k > n) return 0;
	if(2*n > k) k = n-k;
	if(k == 0) return 1;
	int result = k;
	for(int i = 2; i <= k; ++i){
		result *= n-k+1;
		result /= k;
	}
}

auto coordinateCompression(vector<int> arr) {
    vector<int> sorted = arr;
    sort(all(sorted));

    ump<int, int> valueToRank;
	ump<int, int> rankToValue;
    int rank = 1;

    for (int value : sorted) {
        if (!valueToRank.count(value)) {
            valueToRank[value] = rank;
			rankToValue[rank] = value;
            rank++;
        }
    }
    // Replace values if needed, perform operation, then use rankToValue to convert back
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = valueToRank[arr[i]];
    }

    return {arr, valueToRank};
}


// Count number of inversions in array (size 2 and 3)
// Size 2
int countInversionsSize2(vi& arr) {
    int n = arr.size();
	vector<int> temp(n, 0);
	return merge(arr, temp, 0, n-1);
}

int merge(vi& arr, vi& temp, int left, int right) {
    int inversions = 0;
    if(left < right) {
        int mid = (left+right)/2;
        inversions += merge(arr, temp, left, mid);
        inversions += merge(arr, temp, mid+1, right);
        inversions += mergeHalves(arr, temp, left, mid, right);
    }
    return inversions;
}

int mergeHalves(vi& arr, vi& temp, int left, int mid, int right) {
	int count = 0;
	int l = left;
	int r = mid+1;
	int index = left;
	while(l <= left && r <= right) {
		if(arr[left] > arr[right]) {
            count += mid-l+1;
            temp[index++] = arr[right++];
        } else {
            temp[index+] = arr[left+];
        }
	}
	while(l <= mid) {
        temp[index++] = arr[l++];
    }
	while(r <= right) {
        temp[index++] = arr[r++];
    }
	for(int i = left; i <= right; ++i) {
        arr[i] = temp[i];
    }
	return count;
}

int countInversionsSize3(vector<int>& nums) {
    int n = nums.size();
	ll res = 0;
    vector<int> numLeftSmaller(n, 0);

    set<int> s;
    for (int i = 0; i < n; ++i) {
        numLeftSmaller[i] = distance(s.begin(), s.lower_bound(nums[i]));
        s.insert(nums[i]);
    }

    set<int> s2;
    s2.insert(nums[n-1]);
    for (int i = n - 2; i >= 1; --i) {
        int rightGreater = distance(s2.upper_bound(nums[i]), s2.end());
        res += rightGreater * numLeftSmaller[i];
        s2.insert(nums[i]);
    }

    return res;
}

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> q;
    vector<int> res;

    for (int i = 0; i < nums.size(); ++i) {
        if (!q.empty() && q.front() <= i - k) {
            q.pop_front();
        }

        while (!q.empty() && nums[q.back()] < nums[i]) {
            q.pop_back();
        }

        q.push_back(i);
        if (i >= k - 1) {
            res.push_back(nums[q.front()]);
        }
    }

    return res;
}

vi maxSlidingWindow(vi nums, int k) {
    deque<int> q;
    vi res;
    FOR(i, n) {
        if(!q.empty() && q.front() <= i-k) q.pop_front();
        while(!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
        q.push_back(i);
        if(i >= k-1) res.push_back(nums[q.front()]);
    }
}



int countMinMaxSubarrays(vi& nums, int minK, int maxK)
{
    int n=nums.size();
    long long ans=0;
    int mn=-1, mx=-1, waste=-1;
    for(int i=0;i<n;++i)
    {
        if(nums[i]<minK || nums[i]>maxK)waste=i;
        if(nums[i]==minK)mn=i;
        if(nums[i]==maxK)mx=i;
        long long temp=min(mx,mn) - waste;
        ans+=(temp<=0)?0:temp;
    }
    return ans;
}

// Two different types of binary search
int bs(vi& arr, int x)
    int l, r;
    while(l<r)
        int mid=l+(r-l)/2;
        if(arr[mid]<x)
            l=m+1;
        else
            r=m;
    return l; // Sometimes might return l-1 for last invalid

int bs(vi& arr, int x)
    int l, r;
    while(l<=r)
        int m=l+(r-l)/2;
        if(arr[m]<x) l=m+1;
        else if(arr[m]>x) r=m-1;
        else return m;
