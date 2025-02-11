#include <bits/stdc++.h>
using namespace std;

#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define repr(i, a, b) for (int i = (a); i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define all(x) begin(x), end(x)
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpii vector<pair<int, int>>
#define vb vector<bool>
#define vvb vector<vector<bool>>

#define int long long
#define str string
int N = 10000; int MOD=1e9+7; constexpr int INF=1e9; constexpr int INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";


int t, k, n, m;
void solve() {

}

int ln = 31;
struct TrieNode {
    TrieNode* ch[2];
    int cnt;
    TrieNode() : ch{nullptr, nullptr}, cnt(0) {}
};

struct Trie {
    TrieNode* root;
    Trie() { root = new TrieNode();}
    ~Trie() { delete root; }
    void add(int x) {
        auto it = root;
        repr(i, ln, 0) {
            int b = (x>>i) & 1;
            if(!it->ch[b]) it->ch[b] = new TrieNode();
            it = it->ch[b];
            it->cnt++;
        }
    }

    int queryAndDelete(int x) {
        TrieNode* it = root; int res = 0;
        repr(i, ln, 0) {
            int b = (x>>i) & 1;
            if(it->ch[b] && it->ch[b]->cnt > 0) {
                it = it->ch[b];
            } else {
                res = res | (1<<i);
                it = it->ch[1-b];
            }
            it->cnt--;
        }
        return res;
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n;
    Trie t;
    vi a(n), b(n);
    f(i, n) cin>>a[i];
    f(i, n) cin>>b[i];
    f(i, n) {
        t.add(b[i]);
    }
    vi res(n);
    f(i, n) res[i] = t.queryAndDelete(a[i]);
    for(int x : res) cout<<x<<sp;
    cout<<en;
}
