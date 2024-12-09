#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vpll = vector<pll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
using vvi = vector<vector<int>>; using vvll = vector<vector<ll>>; using mpq = priority_queue<ll, vector<ll>, greater<>>; using mpqq = priority_queue<pll, vpll, greater<>>;
#define ump unordered_map
#define ust unordered_set
#define f(i, to) for (int i = 0; i < (to); ++i)
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define trav(a, x) for (auto &a : x)
constexpr int MOD = 1000000007; const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; constexpr char en = '\n';
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << "{"; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << "}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os << "{"; string sep; for (const auto &kv : m) os << sep << kv.first << ": " << kv.second, sep = ", "; return os << "}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second) << 1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2); return hashValue; } };

// int m, n;
// bool solve() {
//     cin>>m>>n;
//     vvi blocked(m, vi(n, 0)); // 0 = free, 1 = blocked, 2 = visited;
//     vpii good;
//     string temp;
//     f(i, m) {
//         cin>>temp;
//         f(j, n) {
//             if(temp[j] == '#') {
//                 blocked[i][j] = true;
//             } else if(temp[j] == 'B') {
//                 for(auto [dy, dx] : dirs) {
//                     int ny = i+dy;
//                     int nx = j+dx;
//                     if(ny>=0 && ny<m && nx >=0 && nx < n) {
//                         blocked[ny][nx] = 1; // Any "bad" person blocks all adjacent
//                     }
//                 }
//             } else if(temp[j] == 'G') {
//                 good.emplace_back(i, j);
//             }
//         }
//     }
//     if(good.empty()) return true; // Can block all given no good ones
//     if(blocked[m-1][n-1] == 1) return false; // If exit is blocked then false
//     f(i, good.size()) {
//         pii p = good[i];
//         queue<pii> q;
//         q.push(p);
//         bool valid = false;
//         while(!q.empty() && !valid) {
//             auto [y, x] = q.front(); q.pop();
//             if(y == m-1 && x == n-1) {
//                 valid = true;
//                 break;
//             }
//             if(blocked[y][x] == 1) {
//                 continue;
//             }
//             if(blocked[y][x] == 2 && i>0) {
//                 valid = true;
//                 break;
//             }
//             blocked[y][x] = 2;
//             for(auto [dy, dx] : dirs) {
//                 int ny=y+dy;
//                 int nx=x+dx;
//                 if(ny>=0&&ny<m&&nx>=0&&nx<n) {
//                     q.push({ny, nx});
//                 }
//             }
//         }
//         if(!valid) return false;
//     }
//     return true;
// }
//
// int main() {
//     int t; cin>>t;
//     f(i, t) {
//         cout << (solve() ? "Yes" : "No") << en;
//     }
//     return 0;
// }

int m, n;
bool solve() {
    cin >> m >> n;
    vvi blocked(m, vi(n, 0)); // 0 = empty, 1 = wall, 2 = good person, 3 = bad person
    vpii good, bad;
    string temp;
    f(i, m) {
        cin >> temp;
        f(j, n) {
            if (temp[j] == '#') {
                blocked[i][j] = 1;
            } else if (temp[j] == 'G') {
                blocked[i][j] = 2;
                good.pb({i, j});
            } else if (temp[j] == 'B') {
                blocked[i][j] = 3;
                bad.pb({i, j});
            }
        }
    }

    // Block cells adjacent to bad people
    trav(p, bad) {
        int i = p.first, j = p.second;
        trav(d, dirs) {
            int ny = i + d.first, nx = j + d.second;
            if (ny >= 0 && ny < m && nx >= 0 && nx < n) {
                if (blocked[ny][nx] == 2) {
                    return false;
                }
                if (blocked[ny][nx] == 0) {
                    blocked[ny][nx] = 1;
                }
            }
        }
    }

    // If exit is blocked and there are good people, they cannot escape
    if (blocked[m - 1][n - 1] == 1) {
        return good.empty();
    }

    // Perform BFS from the exit cell
    queue<pii> q;
    vvi visited(m, vi(n, 0));
    q.push({m - 1, n - 1});
    visited[m - 1][n - 1] = 1;

    while (!q.empty()) {
        auto [y, x] = q.front(); q.pop();
        trav(d, dirs) {
            int ny = y + d.first, nx = x + d.second;
            if (ny >= 0 && ny < m && nx >= 0 && nx < n) {
                if (!visited[ny][nx] && blocked[ny][nx] != 1) {
                    if (blocked[ny][nx] == 3) {
                        // Bad person can reach the exit
                        return false;
                    }
                    visited[ny][nx] = 1;
                    q.push({ny, nx});
                }
            }
        }
    }

    // Check if all good people can reach the exit
    trav(p, good) {
        int i = p.first, j = p.second;
        if (!visited[i][j]) {
            return false;
        }
    }

    return true;
}

int main() {
    int t; cin >> t;
    f(i, t) {
        cout << (solve() ? "Yes" : "No") << en;
    }
    return 0;
}