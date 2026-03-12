#include <bits/stdc++.h>
using namespace std;

#define f(i, n) for(int i = 0; i < (n); ++i)
#define int long long
using vi = vector<int>;

void solve() {
  int n; cin >> n;
  vi a(n); f(i, n) cin >> a[i];

  vi l(n), r(n);
  f(i, n) {
    l[i] = i-1;
    r[i] = i+1;
  }

  map<int, vi, greater<int>> byval;
  f(i, n) byval[a[i]].push_back(i);

  vector<char> rem(n, false), inq(n, false);
  int cnt = 0;

  auto canRem = [&](int i) -> bool {
    if(i < 0 || i >= n || rem[i]) return false;
    int li = l[i], ri = r[i];
    return (li >= 0 && !rem[li] && a[li] == a[i]-1) ||
           (ri < n && !rem[ri] && a[ri] == a[i]-1);
  };

  for(auto& [val, ids] : byval) {
    queue<int> q;
    for(int i : ids) {
      if(canRem(i) && !inq[i]) {
        q.push(i);
        inq[i] = true;
      }
    }

    while(!q.empty()) {
      int i = q.front(); q.pop();
      inq[i] = false;

      if(!canRem(i)) continue;

      cnt++;
      rem[i] = true;

      int li = l[i], ri = r[i];
      if(li >= 0) r[li] = ri;
      if(ri < n) l[ri] = li;

      for(int nb : {li, ri}) {
        if(nb >= 0 && nb < n && !rem[nb] && a[nb] == val && !inq[nb] && canRem(nb)) {
          q.push(nb);
          inq[nb] = true;
        }
      }
    }
  }

  cout << n-cnt << '\n';
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
