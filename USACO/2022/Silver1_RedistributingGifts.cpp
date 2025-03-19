#include <bits/stdc++.h>
using namespace std;

int N;
bitset<501> reachable[501];
vector<int> gifts[501];

void calc_reachable_floyd() {
    for (int i = 1; i <= N; ++i)
        for (int g : gifts[i])
            reachable[i][g] = true;
    for (int k = 1; k <= N; ++k) // run floyd-warshall
        for (int i = 1; i <= N; ++i)
            if (reachable[i][k])
                reachable[i] |= reachable[k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    assert(N <= 500);
    for (int i = 1; i <= N; ++i) {
        gifts[i].resize(N);
        for (int &g : gifts[i])
            cin >> g;
        while (gifts[i].back() != i)
            gifts[i].pop_back();
    }

    calc_reachable_floyd();

    for (int i = 1; i <= N; ++i)
        for (int g : gifts[i])
            if (reachable[g][i]) {
                cout << g << "\n";
                break;
            }
}