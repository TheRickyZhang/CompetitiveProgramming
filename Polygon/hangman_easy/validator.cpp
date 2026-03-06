#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  string s = inf.readToken("[a-z]{1,100000}", "s");
  inf.readEoln();

  int n = inf.readInt(1, 26, "n");
  inf.readSpace();
  int k = inf.readInt(1, 26, "k");
  inf.readEoln();

  string guesses = inf.readToken("[a-z]{" + to_string(n) + "," + to_string(n) + "}", "guesses");

  // check all guess chars are distinct
  set<char> seen;
  for(char c : guesses) {
    ensuref(seen.find(c) == seen.end(), "Duplicate guess letter '%c'", c);
    seen.insert(c);
  }

  inf.readEoln();
  inf.readEof();
}
