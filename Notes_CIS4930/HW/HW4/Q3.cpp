#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>;
using vll = vector<long long>;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pq = priority_queue<ll>;
using mpq = priority_queue<ll, vector<ll>, greater<>>;
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

struct Coord {
    ll x;
    ll y;
};

ll d(const Coord& a, const Coord& b) {
    ll dx = a.x-b.x;
    ll dy = a.y-b.y;
    return dx*dx + dy*dy;
}

ll getParent(ll n, vll& link) {
    if(link[n] == n) return n;
    return link[n] = getParent(link[n], link);
}

struct Edge {
    ll a, b, dist;
    bool operator<(const Edge& other) const {
        return dist < other.dist;
    }

};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;
    FOR(_, n) {
        ll s, p;
        cin >> s >> p;
        vector<Coord> posts(p);
        FOR(i, p) cin >> posts[i].x >> posts[i].y;

        vector<Edge> edges;
        FOR(i, p) {
            rep(j, i+1, p) {
                edges.pb({i, j, d(posts[i], posts[j])});
            }
        }

        sort(all(edges)); // min dist

        vll link(p);
        vll size(p, 1);
        FOR(i, p) link[i] = i;

        // squared dist
        ll res = 0;
        ll usedEdges = 0;

        if(s >= p) {
            cout << 0.00 << en;
            continue;
        }

        // Greedily link disconnected stations
        for(auto& edge : edges) {
            ll x = getParent(edge.a, link);
            ll y = getParent(edge.b, link);
            if(x == y) continue;

            if(size[x] < size[y]) swap(x, y);
            link[y] = x;

            if(++usedEdges == p-s) {
                cout << fixed << setprecision(2) << sqrt(edge.dist) << en;
                break;
            }
        }
    }
    return 0;
}
