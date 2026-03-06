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
  v<int> blanks;
  v<bool> good(26, true);
  f(i, n) {
    if(s[i] == '_') blanks.push_back(i);
    else good[s[i]-'a'] = false;
  }
  string res;
  f(c, 26) {
    if(!good[c]) continue;
    for(int p : blanks) s[p] = 'a'+c;
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
    for(int p : blanks) s[p] = '_';
  }
  if(res.empty()) cout<<"cheater"<<endl;
  else cout<<res<<endl;
}
