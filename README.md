# Competitive Programming
My solutions to various problems on Codeforces, USACO, CSES, and more. 

Competitive Programming is quite fun. 

## Notable tooling / utilities:

### Template.cpp

A comprehensive personal template featuring everything I would want pre-written and properly abstracted. Supports:
- \#define and using transformations
- enriched types with broadened operations and cin/cout syntax
- simple helpers such as binary search and modular arithmetic
- common data structures and algorithms

For instance, a subtree range add solution might look like:
```
int n, m, k;
void solve() {
  cin >> n >> k;
  Tree<int> adj(n); cin >> adj;
  auto [dep, par, sz, tin, tout] = _dfs(adj);
  BIT bit(n, plus<int>{}, 0);
  f(_, k) {
    int u, x;
    cind >> u; cin >> x;
    bit.add(tin[u], x);
    bit.add(tout[u], -x);
    // print(bit);
  }
  f(i, n) {
    cout << bit.query(i, i) << " ";
  }
  cout << endl;
}

int32_t main() {
  int t; cin >> t;
  f(_, t) solve();
}
```

### init.sh
Takes in a filename and copies the template to files A-F, or whatever the problem letter names are.

### run.sh
Quickly compiles and runs the specified file with terminal IO, then cleans up after execution.

### put.sh
Stores root files to organized locations based on name.
