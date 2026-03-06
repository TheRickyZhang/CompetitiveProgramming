#include <bits/stdc++.h>
using namespace std;
#define f(i, n) for(int i = 0; i < n; i++)
template<typename T> using v = vector<T>;

int n, k;
string s;
v<string> fruits;

bool solve(int pos) {
  if(pos == n) return true;
  f(j, k) {
    int len = fruits[j].size();
    if(pos+len <= n && s.compare(pos, len, fruits[j]) == 0)
      if(solve(pos+len)) return true;
  }
  return false;
}

int main() {
  cin>>s;
  cin>>k;
  fruits.resize(k);
  f(i, k) cin>>fruits[i];
  n = s.size();

  int pos = -1;
  v<bool> good(26, true);
  f(i, n) {
    if(s[i] == '_') pos = i;
    else good[s[i]-'a'] = false;
  }

  string res;
  f(c, 26) {
    if(!good[c]) continue;
    s[pos] = 'a'+c;
    if(solve(0)) res += (char)('a'+c);
    s[pos] = '_';
  }

  if(res.empty()) cout<<"cheater"<<endl;
  else cout<<res<<endl;
}
