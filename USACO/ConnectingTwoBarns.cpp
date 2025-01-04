#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
	int n, m;
	cin >> n >> m;

	// Adjacency list
	vector<vector<int>> adj(n);
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u;
		--v;  // Convert to 0-based indexing
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// Connected components parent and count
	vector<int> vis(n, -1);
	int cnt = 0;

	// Identify connected components using DFS
	for (int i = 0; i < n; ++i) {
		if (vis[i] != -1) continue;
		// DFS using a stack
		stack<int> s;
		s.push(i);
		while (!s.empty()) {
			int u = s.top();
			s.pop();
			if (vis[u] != -1) continue;
			vis[u] = cnt;
			for (ll v : adj[u]) {
				if (vis[v] == -1) s.push(v);
			}
		}
		cnt++;
	}

	// Mapping each component to its nodes
	vector<vector<int>> components(cnt);
	for (int i = 0; i < n; ++i) { components[vis[i]].push_back(i); }

	// Components containing the start (0) and end (n-1) barns
	vector<int> start_component = components[vis[0]];
	vector<int> end_component = components[vis[n - 1]];

	// Initialize distance vectors with infinity
	vector<int> dist1(cnt, INT_MAX);
	vector<int> dist2(cnt, INT_MAX);

	// Calculate minimum distances to start_component
	int a = 0;
	for (int i = 0; i < n; ++i) {
		int dist = abs(start_component[a] - i);
		while (a < start_component.size() - 1 &&
		       abs(start_component[a + 1] - i) < dist) {
			a++;
		}
		dist1[vis[i]] = min(dist1[vis[i]], dist);
	}

	// Calculate minimum distances to end_component
	int b = 0;
	for (int i = 0; i < n; ++i) {
		int dist = abs(end_component[b] - i);
		while (b < end_component.size() - 1 && abs(end_component[b + 1] - i) < dist) {
			b++;
		}
		dist2[vis[i]] = min(dist2[vis[i]], dist);
	}

	// Compute the result by finding the minimum sum of squared distances
	ll res = LLONG_MAX;
	for (int i = 0; i < cnt; ++i) {
		res = min(res, 1LL * dist1[i] * dist1[i] + 1LL * dist2[i] * dist2[i]);
	}
	cout << res << '\n';
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) { solve(); }
}