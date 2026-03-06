#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  int n, k;
  cin >> s >> n >> k;
  string guesses;
  cin >> guesses;

  set<char> need(s.begin(), s.end());
  int wrong = 0;
  for(char c : guesses) {
    if(need.count(c)) need.erase(c);
    else wrong++;
    if(wrong > k) break;
  }

  cout << (need.empty() && wrong <= k ? "WIN" : "LOSE") << "\n";
}
