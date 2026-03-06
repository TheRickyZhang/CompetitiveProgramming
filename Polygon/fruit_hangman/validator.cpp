#include "testlib.h"
using namespace std;

const int MAX_S = 500;
const int MAX_K = 10000;

int main(int argc, char** argv) {
  registerValidation(argc, argv);

  string s = inf.readLine("[a-z_]{1," + to_string(MAX_S) + "}", "s");
  int n = s.size();

  int underscores = count(s.begin(), s.end(), '_');
  ensuref(underscores >= 1, "s must contain at least one '_', found %d",
          (int)underscores);

  // the blank letter must differ from all revealed letters,
  // so not all 26 letters can appear in s
  set<char> present;
  for (char c : s)
    if (c != '_') present.insert(c);
  ensuref(present.size() < 26,
          "all 26 letters appear in s, no valid blank letter exists");

  int k = inf.readInt(1, MAX_K, "k");
  inf.readEoln();

  set<string> seen;
  for (int i = 0; i < k; i++) {
    string w =
        inf.readLine("[a-z]{3," + to_string(n) + "}", "w_" + to_string(i + 1));
    ensuref(!seen.count(w), "duplicate fruit word: %s", w.c_str());
    seen.insert(w);
  }

  inf.readEof();
  return 0;
}
