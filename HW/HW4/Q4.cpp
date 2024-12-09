#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky Zhang
using vi = vector<int>;
using vll = vector<long long>;
using ll = long long;
using pii = pair<int, int>;
using pq = priority_queue<int>;
using mpq = priority_queue<int, vector<int>, greater<>>;
#define ump unordered_map
#define FOR(i, to) for (int i = 0; i < (to); ++i)
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define repr(i, a, b) for (int i = a-1; i >= b; --i)
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
constexpr int INF = 100000001;
constexpr int MOD = 100000007;
constexpr char en = '\n';
const vector<pii> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct doll {
    int w, h;
};

bool cmp(const doll& A, const doll& B){
    if(A.w != B.w)
        return A.w > B.w;
    return A.h < B.h;
}

vi LDS;

int search_pos(int h){
    int L = 0, R = LDS.size() - 1;
    while (L < R){
        int mid = L + (R - L) / 2;
        if (LDS[mid] <= h)
            L = mid + 1;
        else
            R = mid;
    }
    return L;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t;
    cin >> t;
    FOR(_, t){
        int n;
        cin >> n;
        vector<doll> D(n);
        FOR(i, n){
            cin >> D[i].w >> D[i].h;
        }
        sort(all(D), cmp);
        LDS.clear();
        if(n > 0){
            LDS.pb(D[0].h);
            rep(i, 1, n){
                int current_h = D[i].h;
                int pos = search_pos(current_h);
                if(pos < LDS.size() && LDS[pos] > current_h){
                    LDS[pos] = current_h;
                }
                else{
                    LDS.pb(current_h);
                }
            }
            cout << LDS.size() << en;
        }
        else{
            cout << 0 << en;
        }
    }

    return 0;
}
