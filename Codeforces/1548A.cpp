#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> weaker(n + 1, 0); // Number of weaker friends for each noble
    vector<int> edges(n + 1, 0);  // Total number of friends for each noble
    vector<unordered_set<int>> friends(n + 1); // Adjacency list to track friends

    // Read initial friendships
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v); // Ensure u < v for easier handling
        friends[u].insert(v);
        friends[v].insert(u);
        edges[u]++;
        edges[v]++;
        weaker[v]++; // v has a weaker friend u
    }

    // Compute the initial number of non-vulnerable nobles
    int nonVulnerableCount = 0;
    for (int i = 1; i <= n; ++i) {
        if (weaker[i] == edges[i]) {
            nonVulnerableCount++;
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) { // Add a friendship
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v); // Ensure u < v for consistency
            friends[u].insert(v);
            friends[v].insert(u);

            // Update edges and weaker counts
            if (weaker[u] == edges[u]) nonVulnerableCount--; // u becomes vulnerable
            if (weaker[v] == edges[v]) nonVulnerableCount--; // v becomes vulnerable
            edges[u]++;
            edges[v]++;
            weaker[v]++; // v now has one more weaker friend
            if (weaker[u] == edges[u]) nonVulnerableCount++; // u becomes non-vulnerable
            if (weaker[v] == edges[v]) nonVulnerableCount++; // v becomes non-vulnerable
        } else if (type == 2) { // Remove a friendship
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v); // Ensure u < v for consistency
            friends[u].erase(v);
            friends[v].erase(u);

            // Update edges and weaker counts
            if (weaker[u] == edges[u]) nonVulnerableCount--; // u becomes vulnerable
            if (weaker[v] == edges[v]) nonVulnerableCount--; // v becomes vulnerable
            edges[u]--;
            edges[v]--;
            weaker[v]--; // v now has one less weaker friend
            if (weaker[u] == edges[u]) nonVulnerableCount++; // u becomes non-vulnerable
            if (weaker[v] == edges[v]) nonVulnerableCount++; // v becomes non-vulnerable
        } else if (type == 3) { // Query the number of non-vulnerable nobles
            cout << nonVulnerableCount << '\n';
        }
    }

    return 0;
}
