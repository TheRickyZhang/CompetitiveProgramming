// Template written by Ricky Zhang
using vi = vector<int>;
using vll = vector<long long>;
using ll = long long;
using pii = pair<int, int>;
using pq = priority_queue<int>;
using mpq = priority_queue<int, vector<int>, greater<>>;
#define ump unordered_map
#define FOR(i, to) for (int i = 0; i < (to); ++i)
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define repr(i, a, b) for (int i = a-1; i >= b; --i)
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
constexpr int INF = 1000000000;
constexpr int MOD = 1000000007;
constexpr char en = '\n';
const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

class Solution {
public:
    int maxSatisfaction(vector<int>& s) {
        sort(all(s));
        int res = 0;
        int n = s.size();
        FOR(i, n) {
            int temp = 0;
            rep(j, i, n) {
                temp += s[j] * (j-i+1);
            }
            res = max(res, temp);
        }
        return res;
    }
};