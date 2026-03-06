#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  mt19937 rng(atoi(argv[1]));

  int maxlen = 100000;
  int len = rng() % maxlen + 1;
  int alpha = rng() % 26 + 1; // how many distinct chars to use

  string s(len, 'a');
  for(auto& c : s) c = 'a' + rng() % alpha;

  set<char> in_s(s.begin(), s.end());
  int distinct = in_s.size();

  // n = number of guesses, between 1 and 26
  int n = rng() % 26 + 1;
  int k = rng() % 26 + 1;

  // generate n distinct guess letters
  string pool = "abcdefghijklmnopqrstuvwxyz";
  shuffle(pool.begin(), pool.end(), rng);
  string guesses = pool.substr(0, n);

  cout << s << "\n";
  cout << n << " " << k << "\n";
  cout << guesses << "\n";
}
