#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

void solve() {
	ll n, m;
	cin >> n >> m;

	// Adjacency list
	vector<vector<ll>> adj(n);
	for (int i = 0; i < m; ++i) {
		ll u, v;
		cin >> u >> v;
		--u;
		--v;  // Convert to 0-based indexing
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// Connected components parent and count
	vector<ll> vis(n, -1);
	ll cnt = 0;

	// Identify connected components using DFS
	for (int i = 0; i < n; ++i) {
		if (vis[i] != -1) continue;
		// DFS using a stack
		stack<ll> s;
		s.push(i);
		while (!s.empty()) {
			ll u = s.top();
			s.pop();
			if (vis[u] != -1) continue;
			vis[u] = cnt;
			for (ll v : adj[u]) {
				if (vis[v] == -1) { s.push(v); }
			}
		}
		cnt++;
	}

	// Mapping each component to its nodes
	vector<vector<ll>> components(cnt);
	for (ll i = 0; i < n; ++i) { components[vis[i]].push_back(i); }

	// Components containing the start (0) and end (n-1) barns
	vector<ll> startComponent = components[vis[0]];
	vector<ll> endComponent = components[vis[n - 1]];

	// Initialize distance vectors with infinity
	vector<ll> dist1(cnt, LLONG_MAX);
	vector<ll> dist2(cnt, LLONG_MAX);

	// Calculate minimum distances to startComponent
	ll a = 0;
	for (ll i = 0; i < n; ++i) {
		ll dist = abs(startComponent[a] - i);
		while (a < startComponent.size() - 1 && abs(startComponent[a + 1] - i) < dist) {
			a++;
		}
		dist1[vis[i]] = min(dist1[vis[i]], dist);
	}

	// Calculate minimum distances to endComponent
	ll b = 0;
	for (ll i = 0; i < n; ++i) {
		ll dist = abs(endComponent[b] - i);
		while (b < endComponent.size() - 1 && abs(endComponent[b + 1] - i) < dist) { b++; }
		dist2[vis[i]] = min(dist2[vis[i]], dist);
	}

	// Compute the result by finding the minimum sum of squared distances
	ll res = LLONG_MAX;
	for (ll i = 0; i < cnt; ++i) {
		res = min(res, dist1[i] * dist1[i] + dist2[i] * dist2[i]);
	}
	cout << res << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll t;
	cin >> t;
	for (int i = 0; i < t; ++i) { solve(); }
}