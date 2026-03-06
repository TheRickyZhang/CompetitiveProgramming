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
  v<bool> good(26, true);
  f(i, n) {
    if(s[i] == '_') pos = i;
    else good[s[i]-'a'] = false;
  }

  string res;
  f(c, 26) {
    if(!good[c]) continue;
    char ch = (char)('a'+c);
    s[pos] = ch;

    int it = 0;
    while(it < n) {
      int prev = it;
      f(j, k) {
        int len = fruits[j].size();
        if(it+len <= n && s.compare(it, len, fruits[j]) == 0) {
          it += len;
          break;
        }
      }
      if(it == prev) break;
    }
    if(it >= n) res += ch;

    s[pos] = '_';
  }

  if(res.empty()) cout<<"cheater"<<endl;
  else cout<<res<<endl;
}
