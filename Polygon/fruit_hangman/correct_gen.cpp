#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
  registerGen(argc, argv, 1);

  int len = opt<int>("len", 500);
  int k = opt<int>("k", 25);
  int wordLen = opt<int>("word-len", min(len, 100));
  int blanks = opt<int>("blanks", 3);
  bool cheater = opt<bool>("cheater", false);

  ensure(1 <= len && len <= 500);
  ensure(1 <= k && k <= 100);
  ensure(3 <= wordLen && wordLen <= 100);
  ensure(1 <= blanks && blanks <= len);

  char blankLetter = char('a' + rnd.next(0, 25));
  if (cheater) {
    ensure(blanks >= 2);
  }

  string secret(len, 'a');
  vector<int> perm(len);
  iota(perm.begin(), perm.end(), 0);
  shuffle(perm.begin(), perm.end());

  vector<int> blankPos(perm.begin(), perm.begin() + blanks);
  sort(blankPos.begin(), blankPos.end());
  set<int> blankSet(blankPos.begin(), blankPos.end());

  if (cheater) {
    char c2 = blankLetter;
    while (c2 == blankLetter)
      c2 = char('a' + rnd.next(0, 25));
    for (int i = 0; i < blanks; i++)
      secret[blankPos[i]] = (i == 0) ? blankLetter : c2;
  } else {
    for (int p : blankPos)
      secret[p] = blankLetter;
  }

  for (int i = 0; i < len; i++) {
    if (blankSet.count(i))
      continue;
    char c = char('a' + rnd.next(0, 24));
    if (c >= blankLetter)
      c++;
    secret[i] = c;
  }

  string pattern = secret;
  for (int p : blankPos)
    pattern[p] = '_';

  vector<string> words;
  unordered_set<string> seen;

  if (!cheater) {
    int i = 0;
    while (i < len) {
      int maxWl = min(wordLen, len - i);
      if (maxWl < 3)
        break;
      int wl = rnd.next(3, maxWl);
      string w = secret.substr(i, wl);
      if (seen.insert(w).second)
        words.push_back(w);
      i += wl;
    }
    if (i < len && !words.empty()) {
      string merged = words.back() + secret.substr(i);
      if ((int)merged.size() <= 100) {
        seen.erase(words.back());
        words.back() = merged;
        seen.insert(words.back());
      }
    }
  }

  while ((int)words.size() < k) {
    int wl = rnd.next(3, max(3, wordLen));
    string w;
    for (int i = 0; i < wl; i++)
      w += char('a' + rnd.next(0, 25));
    if (seen.insert(w).second)
      words.push_back(w);
  }

  shuffle(words.begin(), words.end());

  println(pattern);
  println((int)words.size());
  for (auto& w : words)
    println(w);
  return 0;
}
