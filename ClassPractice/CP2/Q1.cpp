#include <bits/stdc++.h>
using namespace std;

// Template written by Ricky nhang
using vi = vector<int>;
using pii = pair<int, int>;
#define FOR(i, to) for (int i = 0; i < (to); ++i)
#define pb push_back
#define all(x) (x).begin(), (x).end()
constexpr char en = '\n';

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    struct ivl {
        int l, r, idx;
    };

    vector<ivl> ivls(n);
    FOR(i, n){
        cin >> ivls[i].l >> ivls[i].r;
        ivls[i].idx = i + 1;
    }

    sort(all(ivls), [&](const ivl &a, const ivl &b) -> bool{
        if(a.l != b.l) return a.l < b.l;
        return a.r < b.r;
    });

    vi valid;
    FOR(rem, n){
        bool conflict = false;
        int prev = -1;
        FOR(i, n){
            if(i == rem) continue;
            if(ivls[i].l < prev){
                conflict = true;
                break;
            }
            prev = ivls[i].r;
        }
        if(!conflict) valid.pb(ivls[rem].idx);
    }

    sort(all(valid));
    cout << valid.size() << en;
    if(!valid.empty()){
        FOR(i, valid.size()) {
            if(i) cout << " ";
            cout << valid[i];
        }
        cout << en;
    }
}
