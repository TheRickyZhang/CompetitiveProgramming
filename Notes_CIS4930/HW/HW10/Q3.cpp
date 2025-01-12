using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vpll = vector<pll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
using vvi = vector<vector<int>>; using vvll = vector<vector<ll>>; using mpq = priority_queue<ll, vector<ll>, greater<>>; using mpqq = priority_queue<pll, vpll, greater<>>;
#define ump unordered_map
#define ust unordered_set
#define f(i, to) for (int i = 0; i < (to); ++i)
#define fr(i, to) for (int i = (to-1); i >=0; --i)
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
constexpr int MOD = 1000000007; constexpr int INF = INT_MAX-37; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };
class Solution {
public:
    class SegmentTree {
        int n;
        vi tree;
    public:
        SegmentTree(int size) : n(size), tree(2 * size) {
            tree[0] = 0;
            f(i, n) tree[i+n] = 1;
            fr(i, n) tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
        
        // Trying a more compressed version - I think I'll stick with my recursion
        void addValue(int idx, int val) {
            idx += n;
            tree[idx] += val;
            while (idx > 1) {
                idx >>= 1;
                tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
            }
        }
        
        int getSum(int left, int right) {
            int count = 0;
            left += n;
            right += n;
            while (left <= right) {
                if (left % 2) count += tree[left++];
                if (!(right % 2)) count += tree[right--];
                left >>= 1;
                right >>= 1;
            }
            return count;
        }
    };

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vll sum(nums.size() + 1, 0);
        f(i, nums.size()) {
            sum[i + 1] = sum[i] + nums[i];
        }
        
        // unique prefixes, as we want sum(0, j) = sum(0, i) + lower,upper
        vll pre(all(sum));
        sort(all(pre));
        SegmentTree tree(pre.size());
        
        int count = 0;
        for (const auto& x : sum) {
            int idx = lower_bound(all(pre), x) - pre.begin();
            int lowerIdx = lower_bound(all(pre), x + lower) - pre.begin();
            int upperIdx = upper_bound(all(pre), x + upper) - pre.begin() - 1;
            tree.addValue(idx, -1);
            count += tree.getSum(lowerIdx, upperIdx);
        }
        
        return count;
    }
};