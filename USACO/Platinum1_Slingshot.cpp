#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// BeginCodeSnip{Segment Tree (from the module)}
template <class T> class MinSegmentTree {
  private:
	const T DEFAULT = numeric_limits<T>().max();

	vector<T> segtree;
	int len;

  public:
	MinSegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) {}

	void set(int ind, T val) {
		ind += len;
		segtree[ind] = val;
		for (; ind > 1; ind /= 2) {
			segtree[ind / 2] = min(segtree[ind], segtree[ind ^ 1]);
		}
	}

	T range_min(int start, int end) {
		T res = DEFAULT;
		for (start += len, end += len; start < end; start /= 2, end /= 2) {
			if (start % 2 == 1) { res = min(res, segtree[start++]); }
			if (end % 2 == 1) { res = min(res, segtree[--end]); }
		}
		return res;
	}

	T get(int ind) { return segtree[len + ind]; }
};
// EndCodeSnip

int main() {
	freopen("slingshot.in", "r", stdin);
	freopen("slingshot.out", "w", stdout);

	int n, q;
	cin >> n >> q;
	vector<array<int, 4>> events;
	vector<int> coords = {0, INT_MAX};
	for (int i = 0; i < n; i++) {
		int x, y, t;
		cin >> x >> y >> t;
		coords.push_back(x);
		coords.push_back(y);
		events.push_back({0, x, y, t});
	}
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		coords.push_back(a);
		coords.push_back(b);
		events.push_back({1, a, b, i});
	}

	// apply coordinate compression on all relevant locations
	sort(begin(coords), end(coords));
	coords.erase(unique(begin(coords), end(coords)), end(coords));
	const auto id = [&](int x) -> int {
		return lower_bound(begin(coords), end(coords), x) - begin(coords);
	};

	constexpr ll INF = 1e18;  // not long long max to avoid overflow later on
	vector<ll> res(q, INF);
	for (int t = 0; t < 2; t++) {
		/*
		 * x <= a if t = 0.
		 * x >= a if t = 1.
		 * We always place the slingshot events before
		 * the query events in our sorting order.
		 */
		sort(begin(events), end(events),
		     [&](const array<int, 4> &x, const array<int, 4> &y) -> bool {
			     int v_1 = x[1], v_2 = y[1];
			     if (t == 0) { v_1 *= -1, v_2 *= -1; }
			     return (v_1 == v_2) ? x[0] < y[0] : v_1 < v_2;
		     });

		// pref = RMQ for best option if b <= y
		// suff = RMQ for best option if b >= y
		MinSegmentTree<ll> pref(coords.size());
		MinSegmentTree<ll> suff(coords.size());
		for (const auto [type, a, b, c] : events) {
			int b_id = id(b);
			if (type == 0) {
				// applying this result for future queries where b <= y.
				ll add_1 = (t) ? c - a - b : c + a - b;
				if (pref.get(b_id) > add_1) { pref.set(b_id, add_1); }

				// applying this result for future queries where b >= y.
				ll add_2 = (t) ? c - a + b : c + a + b;
				if (suff.get(b_id) > add_2) { suff.set(b_id, add_2); }
			} else {
				/*
				 * res1 is for if we are choosing a slingshot with b <= y
				 * res2 is for if we are choosing a slingshot with b >= y
				 * we set res1 and res2 to be at most INF to prevent overflow when
				 * adding to them
				 */
				ll res1 = min(INF, pref.range_min(0, b_id + 1));
				ll res2 = min(INF, suff.range_min(b_id, coords.size()));

				// could have overflow when adding (e.g. if adding a + b to res1)
				if (t == 0) {
					res1 += b - a;
					res2 -= a + b;
				} else {
					res1 += a + b;
					res2 += a - b;
				}

				res[c] = min({res[c], res1, res2, (ll)abs(a - b)});
			}
		}
	}

	for (int i = 0; i < q; i++) { cout << res[i] << '\n'; }
}