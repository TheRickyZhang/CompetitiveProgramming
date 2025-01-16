#include<bits/stdc++.h>
//#include <boost/multiprecision/cpp_int.hpp>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
//#define bint int1024_t
#define ld long double
#define vect vector<ll>
#define unmap unordered_map
#define pb push_back
#define F first
#define S second
#define pi 3.1415926536
#define mod int(1e9+7)
#define mp make_pair
//ios_base::sync_with_stdio(false);cin.tie(NULL);
#define testcases ll t; cin>>t; while(t--)

using namespace std;
//using namespace boost::multiprecision;
//using namespace __gnu_pbds;

ll n, k;
vect v(2001, 0);
vector<string> s(2001);
bool dp_table[2010][2010];
vect dig{119, 18, 93, 91, 58, 107, 111, 82, 127, 123};

ll check(ll current_mask, ll target_mask) {
    if((current_mask & target_mask) != current_mask) return -1;
    return __builtin_popcount(target_mask) - __builtin_popcount(current_mask);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    // Read and convert each digit's segment representation to a mask
    for(ll i = 1; i <= n; i++) {
        cin >> s[i];
        ll c = 0;
        for(ll j = 6; j >= 0; j--){
            if(s[i][j] == '1') v[i] += (1LL << c);
            c++;
        }
    }

    // Initialize DP table
    memset(dp_table, 0, sizeof(dp_table));
    dp_table[n+1][0] = 1;

    // Populate DP table from digit n down to 1
    for(ll i = n; i >= 1; i--){
        for(ll j = 0; j <= k; j++){
            if(!dp_table[i+1][j]) continue;
            for(ll d = 0; d <= 9; d++){
                ll cost = check(v[i], dig[d]);
                if(cost != -1 && j + cost <= k){
                    dp_table[i][j + cost] = 1;
                }
            }
        }
    }

    string ans = "";
    ll remaining = k;
    bool possible = true;

    // Reconstruct the maximum number by selecting the highest possible digit at each position
    for(ll i = 1; i <= n; i++) {
        bool found = false;
        for(ll d = 9; d >= 0; d--){
            ll cost = check(v[i], dig[d]);
            if(cost == -1 || remaining < cost) continue;
            if(dp_table[i+1][remaining - cost]){
                ans += to_string(d);
                remaining -= cost;
                found = true;
                break;
            }
        }
        if(!found){
            possible = false;
            break;
        }
    }

    if(ans.size() != n || !possible) cout << "-1";
    else cout << ans;

    return 0;
}
