#include <bits/stdc++.h>

using namespace std;
#define int long long
const int INF = 1e18;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> d(n + 1, vector<int>(n + 1, INF));
  for (int i = 1; i <= n; ++i) {
    d[i][i] = 0;
  }
  for (int i = 0; i < m; ++i) {
    int u, v;
    int w;
    cin >> u >> v >> w;

    d[u][v] = min(d[u][v], w);
    d[v][u] = min(d[v][u], w);
  }

  for (int i = 1; i <= n; ++i) {
    for (int k = 1; k <= n; ++k) {
      for (int j = 1; j <= n; ++j) {
        if (d[i][k] < INF && d[k][j] < INF) {
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
      }
    }
  }
  for (int i = 2; i <= n; ++i) {
    if (d[1][i] == INF) {
      cout << -1 << "\n";
    } else {
      cout << d[1][i] << "\n";
    }
  }
}

int32_t main() {
  solve();
}
