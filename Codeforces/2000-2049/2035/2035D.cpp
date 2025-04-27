#include <bits/stdc++.h>
using namespace std;

/*
  John Watson
  Handle codeforces : quangminh98

  Mua Code nhu mua Florentino !!
*/

#define ll long long

string name = "test";

void solve();
signed main()
{
    if (fopen((name + ".inp").c_str(), "r"))
    {
        freopen((name + ".inp").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}

// main program
const int mod = 1e9 + 7;

int add(int a, int b) { a += b; if (a >= mod) a -= mod; return a; }
int sub(int a, int b) { a -= b; if (a < 0) a += mod; return a; }
int mul(int a, int b) { return (1ll * a * b) % mod; }

int power(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b % 2 == 1)
            res = mul(res, a);
        a = mul(a, a);
        b /= 2;
    }
    return res;
}

void solve()
{
    int n; cin >> n;
    int a[n + 1];
    for (int i = 1; i <= n; i++) cin >> a[i];

    int cur = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 1; i <= n; i++)
    {
        // update current value
        cur = add(cur, a[i]);

        // get the form of a[i] as described earlier
        int p = 0;
        while (a[i] % 2 == 0)
        {
            p++;
            a[i] /= 2;
        }
        int y = a[i];

        while (!pq.empty())
        {
            int x = pq.top().first, cnt = pq.top().second;

            // whether we can perform all operations for this
            bool great= false;
            // compare as analysed earlier
            if (p > 31)
                great = true;
            else
                if (1ll * (1 << p) * y >= x) // remember to add 1ll
                    great = true;
            if (!great) break;

            pq.pop();

            // now we can proceed, we substract the old values while adding new ones
            cur = sub(cur, mul(power(2, p), a[i]));
            cur = add(cur, mul(power(2, p + cnt), a[i]));
            cur = sub(cur, mul(x, power(2, cnt)));
            cur = add(cur, x);
            // also remember to update the power
            p += cnt;
        }

        // if p is equal to 0, it meres the value cannot be divided by 2
        // we only push value that can be used
        if (p != 0)
            pq.push({y, p});

        cout << cur << ' ';
    }
    cout << '\n';
}


// Ew don't look at this
// void solve() {
//     cin>>n;
//     vi a(n); read(a);
//     auto get = [&](int x) {
//         int p = 0;
//         while(x % 2 == 0) {
//             x >>= 1; p++;
//         }
//         return make_pair(x, p);
//     };
//
//     auto [asum, apow] = get(a[0]);
//     vi dp(n); v<double> mag(n);
//     dp[0] = a[0], mag[0] = log2(a[0]);
//
//     v<tuple<double, int, int>> critical; // Contains {log, x, pow} used up to a critical point
//     auto addLog = [&](double l, int y, int init = 0) {
//         return l + log2(1 + y * exp2(init-l)); // if l == log2(x), log2(x + y) = l + log(1 + y/(1<<x));
//     };
//     fe(i, n-1) {
//         auto [x, p] = get(a[i]);
//         double best = 0, pos = -3;
//         auto comp = [&](double lg, int ii) {
//             if(lg > best) {
//                 best = lg;
//                 pos = ii;
//             }
//         };
//         comp(addLog(apow + log2(a[i]), asum), -1); // Put everything on a[i]
//         comp(addLog(mag[i-1], a[i]), -2); // Add a[i] normally
//         f(j, critical.size()) {
//             auto [lg, x, pow] = critical[j];
//             comp(addLog(lg, a[i], apow - pow), j);
//         }
//         if(pos == -1) {
//             while(!critical.empty()) critical.pop_back();
//             mag[i] = addLog(apow + log2(a[i]), asum);
//             int val = add(mult(a[i], fastPow(2, apow)), asum);
//             critical.pb({mag[i],  val, apow});
//             cout<<val<<en;
//         } else if (pos >= 0) {
//             auto [lg, x, pow] = critical[pos];
//             mag[i] = addLog(lg, a[i], apow - pow);
//             cout<<add(x, fastPow(a[i], apow-pow))<<en;
//         }
//         asum += x, apow += p;
//     }
//     f(i, n) cout<<dp[i]<<sp;
//     cout<<en;
// }

// int32_t main() {
//     setIO();
//     int t; cin>>t; f(i, t) solve();
// }
