#include  <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define op_ operator
#define cx_ constexpr
#define fn function
#define f(i, to) for (int i = 0; i < to; ++i)
#define fe(i, to) for (int i = 1; i <= to; ++i)
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define repr(i, a, b) for (int i = a; i >= b; --i)
#define ff first
#define ss second
#define pb push_back
#define fora(a, x) for (auto &(a) : (x))
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define quit(s) do{ cout<<(s)<<en; return; }while(false)

// #define int long long
tpl_<tn_ T>using v=vector<T>; using vi=v<int>; tpl_<tn_ T>using vv=v<v<T>>; using ll=long long; using pii=pair<int,int>;
using vb=v<bool>; using vvb=v<vb>; using vs=v<string>; using iii=array<int, 3>; using i4=array<int, 4>;
using vvi=v<vi>; using vll=v<ll>; using vpii=v<pii>; using vvpii=v<vpii>;

int k, n, m;

int solution(string s) {
    int curr = 0;
    int res = 0;
    for(char c : s) {
        if(c == 'i') {
            curr++;
        } else if(c == 'd') {
            curr = max(0, curr-1);
        } else if(c == 'w') {
            res += curr;
            curr = 0;
        } else {
            cout<<"invalid char, shouldn't happen";
            return -1;
        }
    }
    return res;
}