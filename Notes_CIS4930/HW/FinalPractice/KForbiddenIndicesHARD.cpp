#include <bits/stdc++.h>
using namespace std;

// Type Definitions
using vi = vector<int>;
using ll = long long;
using pii = pair<int, int>;
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define pb push_back
#define ff first
#define ss second
constexpr int MAX = 400005;

// Suffix Automaton Namespace
namespace SAM {
    struct node {
        int ch[26] = {0};
        int fa = 0;
        int len = 0;
    } sam[MAX];

    int sz[MAX] = {0};
    int tot = 1, las = 1;
    int c[MAX] = {0}, a[MAX] = {0};

    void insert(char c_char, const char t[]) {
        int x = c_char - 'a';
        int cur = las, p;
        int np = ++tot;
        sam[np].len = sam[cur].len + 1;
        sam[np].fa = 0;
        sz[np] = (t[sam[np].len] == '0') ? 1 : 0;

        while(cur && !sam[cur].ch[x]) {
            sam[cur].ch[x] = np;
            cur = sam[cur].fa;
        }
        if(!cur) {
            sam[np].fa = 1;
        }
        else {
            int q = sam[cur].ch[x];
            if(sam[cur].len + 1 == sam[q].len) {
                sam[np].fa = q;
            }
            else {
                int clone = ++tot;
                sam[clone] = sam[q];
                sam[clone].len = sam[cur].len + 1;
                sz[clone] = 0;
                while(cur && sam[cur].ch[x] == q) {
                    sam[cur].ch[x] = clone;
                    cur = sam[cur].fa;
                }
                sam[q].fa = sam[np].fa = clone;
            }
        }
        las = np;
    }

    void build(int n, const char s[], const char t[]) {
        rep(i, 1, n + 1) insert(s[i], t);
        rep(i, 1, tot + 1) c[sam[i].len]++;
        rep(i, 1, n + 1) c[i] += c[i-1];
        repr(i, tot +1, 2) a[c[sam[i].len]--] = i;
        repr(i, tot +1, 2) sz[sam[a[i]].fa] += sz[a[i]];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    char s[n+1], t[n+1];
    cin >> (s + 1) >> (t + 1);

    SAM::build(n, s, t);

    ll ans = 0;
    rep(i, 2, SAM::tot + 1){
        ans = max(ans, (ll)SAM::sam[i].len * SAM::sz[i]);
    }
    cout << ans;
}
