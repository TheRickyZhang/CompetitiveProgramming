#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, 200000, "n");
  inf.readEoln();

  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    if (i) inf.readSpace();
    a[i] = inf.readInt(1, 1000000000, format("a[%d]", i + 1).c_str());
  }
  inf.readEoln();

  vector<int> p(3), s(3);
  for (int i = 0; i < 3; ++i) {
    if (i) inf.readSpace();
    p[i] = inf.readInt(1, 3, format("p[%d]", i + 1).c_str());
    s[i] = p[i];
  }
  inf.readEoln();

  sort(s.begin(), s.end());
  ensuref(s == vector<int>({1, 2, 3}), "p must be a permutation of 1,2,3");

  inf.readEof();
}
