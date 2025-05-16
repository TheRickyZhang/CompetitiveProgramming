#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef long double ld;
typedef vector<ll> vi;
typedef vector<pii> vpi;

const ll maxn = 2e5 + 10;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const unsigned int mod = 1e9 + 7;

#define pb push_back
#define ppb pop_back
#define ff first
#define ss second
#define sza(x) ((int)(x).size())
#define all(a) (a).begin(), (a).end()
#define smax(s, v) s = max(s, (v))
#define smin(s, v) s = min(s, (v))

#define FFR(i,a,b,s) for(int i = a; i != b; i += s)
#define FF(i,n) FFR(i, 0, n, 1)
#define FF1(i,n) FFR(i, 1, n+1, 1)
#define FFD(i,n) FFR(i, n-1, -1, -1)
#define FFD1(i,n) FFR(i, n, 0, -1)

#define F(n) FF(i,n)
#define F1(n) FF1(i,n)
#define FD(n) FFD(i,n)
#define FD1(n) FFD1(i,n)
#define FR(a,b,s) FFR(i,a,b,s)

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << "(" << p.ff << ", " << p.ss << ")"; }
template<typename A> ostream& operator<<(ostream& os, const vector<A>& v) { os << "["; for(const auto& x: v) os << x << ", "; return os << "]"; }

#ifdef LOCAL
void dbg_out() { cerr << endl; }
template<typename H, typename... T> void dbg_out(H h, T... t) { cerr << " " << h; dbg_out(t...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

int add(int a, int b) {
    a += b;
    if(a >= mod) return a-mod;
    if(a<0) return a+mod;
    return a;
}
#define sadd(a, b) a = add(a, (b))

int sub(int a, int b) {
    return add(a, -b);
}
#define ssub(a, b) a = sub(a, (b))

int mul(int x, int y) {
    return (ll) x * y % mod;
}
#define smul(a, b) a = mul(a, (b))

int fpow(int x, ll e) {
    int r = 1;
    while(e) {
        if(e&1) smul(r, x);
        smul(x,x);
        e>>=1;
    }
    return r;
}

int modinv(int x) {
    return fpow(x, mod-2);
}

int safemod(ll x) {
    x %= mod;
    return x<0 ? x+mod : x;
}

// =================================================
// ================== CODIGO AQUI ==================
// =================================================

ll n, m, p, q, k;

ll a[maxn], b[maxn];

int send(int i) {
    cout << "? " << i << endl;
    int r;
    cin >> r;
    return r;
}

void sendans(int a, int b) {
    cout << "! " << a << " " << b << endl;
    return;
}

void solve() {
    cin >> n >> k;

    F(k) {
        a[i] = send(i+1);
    }

    F(k) {
        int r = n%k;
        b[(i+r)%k] = send(n-k+i + 1);
    }

    int lb = k, ub = n-k;
    // lb ctz que sim
    // ub talvez
    while(lb < ub) {
        int teomid = (lb + ub) / 2;
        int mid = -1;
        F(k) {
            int pos = teomid + i;
            if(pos<ub and a[pos%k] != b[pos%k]) {
                mid = pos;
                break;
            }
            pos = teomid-i;
            if(pos>=lb and a[pos%k] != b[pos%k]) {
                mid = pos;
                break;
            }
        }

        if(mid == -1) break;

        int ans = send(mid+1);
        if(a[mid%k] == ans) {
            lb = mid+1;
        } else {
            ub = mid;
        }
    }

    if(lb != ub) {
        cout << "! " << -1 << endl;
        return;
    }

    sendans(lb, n-lb);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    F1(t) solve();
}