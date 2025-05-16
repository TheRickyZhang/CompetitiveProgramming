#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vvpii = vector<vpii>; using vpll = vector<pll>; using vvpll = vector<vpll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
using vvi = vector<vector<int>>; using vvll = vector<vector<ll>>;
#define ump unordered_map
#define ust unordered_set
#define f(i, to) for (int i = 0; i < int(to); ++i)
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
string en = "\n";

/* IDEA for optimal method:
Use z-algorithm on possible prefixes and strings
Maintain a vi res with max values. As you insert each string update the corresopnding value in res;
*/

vll res(20, 0);

struct TrieNode {
    vector<TrieNode*> ch;
    ll cnt;
    ll lvl;
    TrieNode() : ch(26, nullptr), cnt(0), lvl(0) {};
};

struct Trie {
    TrieNode* root;
    Trie() { root = new TrieNode(); }
    void insert(str s) {
        auto it = root;
        f(i, s.size()) {
            ll c = s[i]-'a';
            if(!it->ch[c]) it->ch[c] = new TrieNode();
            it = it->ch[c];
            it->cnt++; it->lvl=i+1;
            res[it->lvl] = max(res[it->lvl], it->cnt);
        }
    }
};

// void solve(TrieNode* it, vi& res, int i){
//     res[i] = max(res[i], it->cnt);
//     for(auto child : it->ch) {
//         if(child) solve(child, res, i+1);
//     }
// }

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll n, k; cin>>n>>k; string s;
    Trie t;
    f(i, n) {
        cin>>s; t.insert(s);
    }
    // solve(t.root, res, 0);
    // for(ll x : res) cout<<x<<" ";
    // cout<<en;

    f(i, k) {
        ll a; cin>>a;
        cout<<(res[a]>0 ? res[a] : -1)<<en;
    }
    return 0;
}
