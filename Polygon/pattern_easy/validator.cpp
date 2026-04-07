#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int t = inf.readInt(1, 1000, "t");
  inf.readEoln();

  int sum_n = 0;
  for (int tc = 1; tc <= t; ++tc) {
    setTestCase(tc);

    int n = inf.readInt(1, 1000, ::format("n[%d]", tc).c_str());
    inf.readEoln();

    sum_n += n;
    ensuref(sum_n <= 1000, "sum of n over all test cases must not exceed 1000");

    vector<int> freq(n + 1);
    for (int i = 0; i < n; ++i) {
      if (i) inf.readSpace();
      int x = inf.readInt(1, n, ::format("a[%d][%d]", tc, i + 1).c_str());
      freq[x]++;
    }
    inf.readEoln();

    for (int x = 1; x <= n; ++x) {
      ensuref(freq[x] == 1, "a must be a permutation of 1..n");
    }

    string p = inf.readToken("[123]{3}", ::format("p[%d]", tc).c_str());
    inf.readEoln();

    string s = p;
    sort(s.begin(), s.end());
    ensuref(s == "123", "p must be a permutation of 123");
  }

  inf.readEof();
}
