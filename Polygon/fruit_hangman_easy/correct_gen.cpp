#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char** argv) {
  registerGen(argc, argv, 1);
  int len = opt<int>("len", 20);
  int k = opt<int>("k", 2);
  int wordLen = opt<int>("word-len", min(len, 100));
  bool cheater = opt<bool>("cheater", false);
  int maxBlanks = opt<int>("max-blanks", max(1, len/5));
  ensure(1 <= len && len <= 500);
  ensure(1 <= k && k <= 2);
  ensure(3 <= wordLen && wordLen <= len);

  char blankLetter = char('a' + rnd.next(0, 25));

  // generate secret string
  string secret(len, 'a');
  string pattern(len, 'a');

  // pick blank positions (at least 1)
  int numBlanks = rnd.next(1, maxBlanks);
  set<int> blankSet;
  while((int)blankSet.size() < numBlanks) {
    blankSet.insert(rnd.next(0, len-1));
  }

  for(int i = 0; i < len; i++) {
    if(blankSet.count(i)) {
      secret[i] = blankLetter;
      pattern[i] = '_';
    } else {
      char c = char('a' + rnd.next(0, 24));
      if(c >= blankLetter) c++;
      secret[i] = c;
      pattern[i] = secret[i];
    }
  }

  // generate k words
  vector<string> words;
  unordered_set<string> seen;
  if(!cheater) {
    // chop secret into words
    int i = 0;
    while(i < len && (int)words.size() < k) {
      int maxWl = min(wordLen, len - i);
      if(maxWl < 3) break;
      int wl = rnd.next(3, maxWl);
      string w = secret.substr(i, wl);
      if(seen.insert(w).second) words.push_back(w);
      i += wl;
    }
    if(i < len && !words.empty()) {
      string merged = words.back() + secret.substr(i);
      if((int)merged.size() <= 100) {
        seen.erase(words.back());
        words.back() = merged;
        seen.insert(words.back());
      }
    }
  }

  // pad to k words
  while((int)words.size() < k) {
    int wl = rnd.next(3, max(3, wordLen));
    string w;
    for(int i = 0; i < wl; i++)
      w += char('a' + rnd.next(0, 25));
    bool ok = true;
    for(auto& existing : words) {
      if((int)w.size() <= (int)existing.size() &&
          existing.substr(0, w.size()) == w) { ok = false; break; }
      if((int)existing.size() <= (int)w.size() &&
          w.substr(0, existing.size()) == existing) { ok = false; break; }
    }
    if(ok && seen.insert(w).second) words.push_back(w);
  }

  shuffle(words.begin(), words.end());
  println(pattern);
  println((int)words.size());
  for(auto& w : words) println(w);
  return 0;
}
