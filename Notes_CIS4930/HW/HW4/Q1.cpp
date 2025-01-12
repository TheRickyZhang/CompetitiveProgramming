#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>;
using vll = vector<long long>;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pq = priority_queue<ll>;
using mpq = priority_queue<int, vector<int>, greater<>>;
#define ump unordered_map
#define FOR(i, to) for (int i = 0; i < (to); ++i)
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define repr(i, a, b) for (int i = a-1; i >= b; --i)
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
constexpr int INF = 100000000;
constexpr int MOD = 100000007;
constexpr char en = '\n';
const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, t;
    cin >> n >> t;

    // {money, deadline}
    vector<pll> people(n);
    for(auto& p : people) cin >> p.first >> p.second;
    sort(all(people), greater<>());
    vector<bool> taken(t, false);
    ll res = 0;

    // Greedy place highest into latest position
    for(auto& [money, deadline] : people){
        for(ll i = min(deadline, t-1); i >=0; --i){
            if(!taken[i]){
                taken[i] = true;
                res += money;
                break;
            }
        }
    }
    cout << res << "\n";
}