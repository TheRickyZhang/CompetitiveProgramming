#include <bits/stdc++.h>
using namespace std;

#define f(i, n) for(int i = 0; i < (n); ++i)
#define int long long
using vi = vector<int>;

void solve() {
  int n; cin>>n;
  vi a(n); f(i,n) cin>>a[i];
  vi l(n), r(n), ord(n);
  f(i,n) l[i]=i-1, r[i]=i+1, ord[i]=i;
  sort(ord.begin(), ord.end(), [&](int x, int y){ return a[x]>a[y]; });

  vector<char> rem(n);
  int cnt = 0;

  auto ok = [&](int i) {
    int li=l[i], ri=r[i];
    return (li>=0 && !rem[li] && a[li]==a[i]-1) ||
           (ri<n && !rem[ri] && a[ri]==a[i]-1);
  };
  auto del = [&](int i) {
    rem[i]=1; cnt++;
    if(l[i]>=0) r[l[i]]=r[i];
    if(r[i]<n) l[r[i]]=l[i];
  };

  int p = 0;
  while(p < n) {
    int v = a[ord[p]];
    queue<int> q;
    while(p<n && a[ord[p]]==v) {
      if(ok(ord[p])) q.push(ord[p]);
      p++;
    }
    while(!q.empty()) {
      int i=q.front(); q.pop();
      if(rem[i] || !ok(i)) continue;
      int li=l[i], ri=r[i];
      del(i);
      for(int nb : {li, ri})
        if(nb>=0 && nb<n && !rem[nb] && a[nb]==v && ok(nb))
          q.push(nb);
    }
  }
  cout<<n-cnt<<"\n";
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
