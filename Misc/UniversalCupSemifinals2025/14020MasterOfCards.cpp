#include <iostream>
#include <vector>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;

	std::vector<std::vector<std::pair<int, int>>> graph(3 * n);

	for (int i = 0; i < n; ++i) {
		int a, b, c;
		std::cin >> a >> b >> c;
		--a, --b, --c;
		graph[a].emplace_back(n + b, 3 * i);
		graph[n + b].emplace_back(a, 3 * i);
		graph[n + b].emplace_back(2 * n + c, 3 * i + 1);
		graph[2 * n + c].emplace_back(n + b, 3 * i + 1);
		graph[2 * n + c].emplace_back(a, 3 * i + 2);
		graph[a].emplace_back(2 * n + c, 3 * i + 2);
	}

	std::vector<std::pair<int, int>> ans;

	std::vector<int> its(3 * n), eu(3 * n), ret;
	std::vector<std::pair<int, int>> s;

	for (int start = 0; start < n; ++start) {
		s.clear();
		s.emplace_back(start, -1);
		ret.clear();
		while (!s.empty()) {
			int x = s.back().first, id = s.back().second;
			int y, e, &it = its[x], end = (int) graph[x].size();
			if (it == end) { ret.push_back(id); s.pop_back(); continue; }
			std::tie(y, e) = graph[x][it++];
			if (!eu[e]) {
				eu[e] = 1; s.emplace_back(y, e);
			}
		}
		for (int i = 0; i + 2 < (int) ret.size(); i += 2) {
			ans.emplace_back(ret[i] / 3, ret[i + 1] / 3);
		}
	}

	std::cout << ans.size() << '\n';

	for (auto [a, b] : ans) {
		std::cout << a + 1 << ' ' << b + 1 << '\n';
	}

	return 0;
}
