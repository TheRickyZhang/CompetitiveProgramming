#include <bits/stdc++.h>
using namespace std;

int main() {
  string s; cin >> s;
  int k; cin >> k;
  vector<string> strings;
  if(k == 1) {
    string x; cin >> x;
    strings.push_back(x);
  } else {
    string x, y; cin >> x >> y;
    strings.push_back(x + y);
    strings.push_back(y + x);
  }
  string res;
  for(char c = 'a'; c <= 'z'; c++) {
    string ss = s;
    for(int i = 0; i < ss.size(); i++) {
      if(ss[i] == '_') ss[i] = c;
    }
    for(string t : strings) {
      if(ss == t) {
        res += c;
        break;
      }
    }
  }
  if(res.empty()) cout << "cheater" << endl;
  else {
    cout << res << endl;
  }
}
