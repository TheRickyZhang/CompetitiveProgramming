#include <bits/stdc++.h>
using namespace std;
#define f(i, n) for(int i = 0; i < n; i++)
template<typename T> using v = vector<T>;

int main() {
  string s; cin>>s;
  int k; cin>>k;
  v<string> fruits(k);
  f(i, k) cin>>fruits[i];
  int n = s.size();

  int pos = -1;
  // BUG: no filtering of revealed letters
  f(i, n) {
    if(s[i] == '_') pos = i;
  }

  string res;
  f(c, 26) {
    s[pos] = 'a'+c;

    v<bool> dp(n+1, false);
    dp[0] = true;
    f(i, n) {
      if(!dp[i]) continue;
      f(j, k) {
        int len = fruits[j].size();
        if(i+len <= n && s.compare(i, len, fruits[j]) == 0)
          dp[i+len] = true;
      }
    }
    if(dp[n]) res += (char)('a'+c);

    s[pos] = '_';
  }

  if(res.empty()) cout<<"cheater"<<endl;
  else cout<<res<<endl;
}
