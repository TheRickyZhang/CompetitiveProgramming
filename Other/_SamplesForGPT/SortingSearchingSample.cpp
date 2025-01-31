#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; using ll = long long; using vll = vector<long long>; using vb = vector<bool>; using vs = vector<string>; using pii = pair<int, int>;
using pll = pair<ll, ll>; using vpii = vector<pii>; using vvpii = vector<vpii>; using vpll = vector<pll>; using vvpll = vector<vpll>; using pq = priority_queue<ll>; using pqq = priority_queue<pll>;
using vvi = vector<vector<int>>; using vvll = vector<vector<ll>>; using mpq = priority_queue<ll, vector<ll>, greater<>>; using mpqq = priority_queue<pll, vpll, greater<>>;
#define ump unordered_map
#define ust unordered_set
#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define repr(i, a, b) for (int i = (a)-1; i >= (b); --i)
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define str string
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");
constexpr int MOD = 1000000007; constexpr ll INF = INT_MAX-37; constexpr ll INFL = 0x3f3f3f3f3f3f3f3f; const vector<pii> dirs = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
constexpr char EN = '\n'; constexpr char SP = ' '; auto en = EN; auto sp = SP;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os<<"("<<p.first<<", "<<p.second<<")"; }
template<typename T_container, typename T = enable_if_t<!is_same_v<T_container, string>, typename T_container::value_type>> ostream& operator<<(ostream &os, const T_container &v) { os<<"{"; string sep; for (const T &x : v) os<<sep<<x, sep = ", "; return os<<"}"; }
template<typename K, typename V> ostream& operator<<(ostream &os, const map<K, V> &m) { os<<"{"; string sep; for (const auto &kv : m) os<<sep<<kv.first<<": "<<kv.second, sep = ", "; return os<<"}"; }
struct pairHash { template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ (hash<T2>{}(p.second)<<1); } };
struct vectorHash { template <class T> size_t operator()(const vector<T>& v) const { size_t hashValue = 0; for (const T& i : v) hashValue ^= hash<T>{}(i) + 0x9e3779b9 + (hashValue<<6) + (hashValue >> 2); return hashValue; } };
auto check = [](auto y, auto x, auto m, auto n) { return y >= 0 && y < m && x >= 0 && x < n; };


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>k;
    if(n<3) {
        cout<<"IMPOSSIBLE"<<en; return 0;
    }
    vpii nums(n);
    f(i, n) {
        cin>>nums[i].ff;
        nums[i].ss=i+1;
    }
    sort(all(nums));
    f(i, n) {
        int target=k-nums[i].ff;
        int l=0, r=n-1;
        int a=0, b=0;
        while(l < r) {
            if(l==i) l++;
            if(r==i) r--;
            int sum=nums[l].ff+nums[r].ff;
            if(sum==target) {
                cout<<nums[i].ss<<" "<<nums[l].ss<<" "<<nums[r].ss<<en;
                return 0;
            }
            if(sum<target) {
                a+=nums[l].ff; l++;
            } else {
                b+=nums[r].ff; r--;
            }
        }
    }
    cout<<"IMPOSSIBLE"<<en;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>k;
    if(n < 4) {
        cout<<"IMPOSSIBLE"<<en;
        return 0;
    }
    vll nums(n);
    f(i, n) cin>>nums[i];
    ump<ll, vpll> mp;
    f(i, n) {
        for(int j=i+1; j<n; ++j) {
            mp[nums[i]+nums[j]].pb({i+1, j+1});
        }
    }
    for(auto [s, p1] : mp) {
        ll target = k - s;
        if (mp.count(target)) {
            auto &p2 = mp[target];
            for (auto &[i1, j1] : p1) {
                for (auto &[i2, j2] : p2) {
                    if (i1 != i2 && i1 != j2 && j1 != i2 && j1 != j2) {
                        cout << i1 << " " << j1 << " " << i2 << " " << j2 << en;
                        return 0;
                    }
                }
            }
        }
    }
    cout<<"IMPOSSIBLE"<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m>>k;
    vi p(n);
    f(i, n) cin>>p[i];
    vi w(m);
    f(i, m) cin>>w[i];
    sort(all(p)); sort(all(w));
    int i=0, j=0, res=0;
    while (i < n && j < m) {
        int l = w[j]-k;
        int r = w[j]+k;
        if(p[i] >= l && p[i] <= r) {
            res++; i++; j++;
        } else {
            if(p[i] >= l) j++;
            else i++;
        }
    }
    cout<<res<<en;
}


signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n,m; cin>>n>>m;
    int l = 1;
    int ind[n+2] = {0}, a[n+1] = {0};
    ind[n+1] = n+1;
    for (int i = 1; i <= n; i++) {
        int x; cin>>x;
        ind[x] = i;
        a[i] = x;
    }
    int c = 1;
    for (int i = 1; i <= n; i++) {
        if (l > ind[i])
            c++;
        l = ind[i];
    }
    while(m--) {
        int x,y; cin>>x>>y;
        int r = a[x], s = a[y];
        swap(a[x], a[y]);
        if (ind[r-1] <= ind[r] && ind[r-1] > y) c++;
        if (ind[r-1] > ind[r] && ind[r-1] <= y) c--;
        if (ind[r] <= ind[r+1] && y > ind[r+1]) c++;
        if (ind[r] > ind[r+1] && y <= ind[r+1]) c--;
        ind[r] = y;
        if (ind[s-1] <= ind[s] && ind[s-1] > x) c++;
        if (ind[s-1] > ind[s] && ind[s-1] <= x) c--;
        if (ind[s] <= ind[s+1] && x > ind[s+1]) c++;
        if (ind[s] > ind[s+1] && x <= ind[s+1]) c--;
        ind[s] = x;
        cout<<c<<endl;
    }
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vi nums(n);
    f(i, n) cin>>nums[i];
    sort(all(nums));
    int same = 0;
    for(int i = 1; i < n; ++i) {
        if(nums[i] == nums[i-1]) same++;
    }
    cout<<n-same<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>k;
    vll t(n);
    f(i, n) cin>>t[i];
    ll l=0, h=1e18;
    // NOTE: YOu can choose between:
    // l < h, m, m+1
    // l <= h, m-1, m+1
    // In both cases return l
    while(l < h) {
        ll m = l+(h-l)/2;
        ll curr=0;
        f(i, n) {
            curr+=m/t[i];
            if(curr >= k) break; // This line is important
        }
        if(curr <= k-1) {
            l=m+1;
        } else {
            h=m;
        }
    }
    cout<<l<<en;
}


int n, k;
vi tree;
vi nums;

void add(int i, int x) {
    while(i <= n) {
        tree[i] += x;
        i += (i & -i);
    }
}
int query(int i) {
    int res = 0;
    while(i > 0) {
        res += tree[i];
        i -= (i & -i);
    }
    return res;
}

// NEED to use < to find last less than, then add 1, otherwise <= can overshoot since there can be multiple positions with same sum
int findkth(int k) {
    int i = 0;
    int mask = 1 << (int)log2(n);
    while(mask > 0) {
        int ni = i + mask;
        if(ni <= n && tree[ni] < k) {
            i = ni;
            k -= tree[ni];
        }
        mask >>= 1;
    }
    return i + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n>>k;
    tree.resize(n + 1, 0);
    nums.resize(n, 0);
    f(i, n) add(i + 1, 1);

    int curr = 0;

    f(i, n) {
        curr = (curr + 1) % (n - i);
        int pos = findkth(curr + 1);
        cout<<pos<<en;
        add(pos, -1);
    }
    return 0;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vll nums(n);
    f(i, n) cin>>nums[i];
    ll mx=0, curr=0;
    f(i, n) {
        curr = max(nums[i], curr+nums[i]);
        mx=max(mx, curr);
    }
    if(mx==0) mx = *max_element(all(nums));
    cout<<mx<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vpii nums(n);
    f(i, n) {
        cin>>nums[i].ff;
        nums[i].ss = i;
    }
    // Using set to not TLE
    set<pii> s;
    int res=0, l=0;
    f(i, n) {
        auto [x, idx] = nums[i];
        auto it = s.lower_bound({x, -1});
        if(it != s.end() && it->first == x) {
            res = max(res, int(s.size()));
            for(int j = l; j<=it->ss; ++j) {
                s.erase(nums[j]);
            }
            l = it->ss+1;
        }
        s.insert(nums[i]);
    }
    res = max(res, int(s.size()));
    cout<<res<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vpii v(n);
    f(i, n) cin>>v[i].ff>>v[i].ss;
    sort(all(v), [&](pii& a, pii& b) {
        return a.ss < b.ss;
    });
    int res = 0;
    for(int i=0; i<n;) {
        int end = v[i].ss;
        res++;
        i++;
        while(i < n && v[i].ff < end) {
            i++;
        }
    }
    cout<<res<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vi l(n), r(n);
    f(i, n) {
        cin>>l[i]>>r[i];
    }
    sort(all(l)); sort(all(r));
    int i=0, j=0;
    int mx = 0;
    int curr = 0;
    while(i < n && j< n) {
        if(l[i] < r[j]) {
            mx = max(mx, ++curr);
            i++;
        } else {
            curr--;
            j++;
        }
    }
    cout<<mx<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    // Alternatively, insert negative values into the multiset so lower_bound works in reverse
    multiset<int, greater<int>> ms;
    f(i, n) {
        int x; cin>>x;
        ms.insert(x);
    }
    vi w(m);
    f(i, m) cin>>w[i];
    for(int x : w) {
        auto it = ms.lower_bound(x);
        if(it == ms.end()) {
            cout<<-1<<en;
            continue;
        }
        cout<<*it<<en;
        ms.erase(it);
    }
}


vi t; // This is a DIFFERENCE ARRAY for availalble r
int n;
int m; // NUmber of unique r. <= n
void update(int i, int x) {
    while(i<=m) {
        t[i]+=x;
        i+=(i&-i);
    }
}
int sum(int i) {
    int res=0;
    while(i>0) {
        res+=t[i];
        i-=(i&-i);
    }
    return res;
}
struct node {
    int l;
    int r;
    int i;
};
bool compare(node& a, node& b) {
    if(a.l==b.l) return a.r>b.r; // NOTE: DESCENDING here to preserve well-ordering
    return a.l<b.l;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vector<node> v(n);
    t.assign(n+1, 0);
    set<int> ends;
    map<int, int> mp; // Maps from r -> normalized rank (among r's)
    f(i, n) {
        int a, b; cin>>a>>b;
        v[i] = {a, b, i};
        ends.insert(b);
    }
    m=0;
    for(auto x : ends) {
        mp[x] = ++m; // 1-indexed here
    }
    sort(all(v), compare);

    // Start from the back because HIGH L = more restrictive of ranges it can contain
    vi res(n, 0);
    for(int i=n-1; i>=0; --i) {
        int rank = mp[v[i].r];
        res[v[i].i] += sum(rank); // Want to add everything <= current rank
        update(rank, 1);      // Only add current rank afterward because it is available based on left bounds
    }
    f(i, n) cout<<(res[i]>0 ? 1 : 0)<<" ";
    cout<<en;

    res.assign(n, 0);
    t.assign(n+1, 0);
    // Note that 1 is arbitrarily used here because any end < r is guaranteed to be valid. lmp[v[i].l  may be more accurate but this is simple
    for(int i=0; i<n; ++i) {
        int rank=mp[v[i].r];
        res[v[i].i] += sum(rank);
        update(1, 1); update(rank+1, -1); // This works because it is a difference array!
    }
    f(i, n) cout<<(res[i]>0 ? 1 : 0)<<" ";
    cout<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vpii nums(n);
    f(i, n) {
        cin>>nums[i].ff;
        nums[i].ss=i+1;
    }
    stack<pii> seen;
    seen.push({0, 0});
    vi res(n);
    f(i, n) {
        while(seen.top().ff >= nums[i].ff) {
            seen.pop();
        }
        res[i]=seen.top().ss;
        seen.push(nums[i]);
    }
    f(i, n) cout<<res[i]<<" ";
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vi nums(n);
    f(i, n) cin>>nums[i];
    sort(all(nums));
    ll l=0, r=n-1;
    ll a=0, b=0;
    while(l<=r) {
        if(a<=b) {
            a+=nums[l];
            l++;
        } else {
            b+=nums[r];
            r--;
        }
    }
    if((l==1 && a > b) || (r==n-2 && b>a)) {
        cout<<2*max(a, b)<<en;
    } else {
        cout<<a+b<<en;
    }
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vector<tuple<int, int, int>> v;
    f(i, n) {
        cin>>a>>b;
        // Process entries (0) first since cannot be same time
        v.pb({a, 0, i});
        v.pb({b, 1, i});
    }
    sort(all(v));
    // Res holds available room #s
    vi res(n, 0);
    stack<int> s; // available rooms
    int curr=0;
    for(auto [a, b, i] : v) {
        if(b==0) {
            curr++;
            if(s.empty()) res[i]=curr;
            else {
                res[i]=s.top();
                s.pop();
            }
        } else {
            curr--;
            s.push(res[i]);
        }
    }
    cout<<*max_element(all(res))<<en;
    f(i, n) cout<<res[i]<<" ";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vll nums(n); f(i, n) cin>>nums[i];
    sort(all(nums));
    vll dp(200001, 1);
    f(i, n) {
        // Keep track of limit what we expect
        if(nums[i] > dp[i]) {
            cout<<dp[i]<<en; return 0;
        }
        dp[i+1]=dp[i]+nums[i];
    }
    cout<<dp[n];
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vi nums(n); f(i, n) cin>>nums[i];
    sort(all(nums));
    ll res = 0;
    ll target = nums[n/2];
    f(i, n) res += abs(nums[i]-target);
    cout<< res <<en;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vi nums(n);
    f(i, n) cin>>nums[i];
    map<int, int> mp;
    mp[0]++;
    ll curr=0, res=0;
    f(i, n) {
        curr=(curr+nums[i]) % n; if(curr<0) curr+=n;
        if(mp.count(curr)) {
            res+=mp[curr];
        }
        mp[curr]++;
    }
    cout<<res<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin>>n>>k;
    vll nums(n);
    f(i, n) {
        cin>>nums[i];
    }
    map<ll, int> mp; mp[0]++;
    ll curr=0, res=0;
    f(i, n) {
        curr+=nums[i];
        if(mp.count(curr-k)) res+=mp[curr-k];
        mp[curr]++;
    }
    cout<<res<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vpii v(n);
    f(i, n) cin>>v[i].ff>>v[i].ss;
    sort(all(v)); // Process shorter tasks greedily first
    ll res=0;
    ll time=0;
    for(auto [t, d] : v) {
        time += t;
        res += d-time;
    }
    cout<<res<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    vi nums(n);
    f(i, n) cin>>nums[i];
    multiset<int> s;
    trav(x, nums) {
        auto it = s.upper_bound(x);
        if(it == s.end()) {
            // cout<<x<<en;
            s.insert(x);
        } else {
            s.erase(it);
            s.insert(x);
        }
    }
    cout<<s.size()<<en;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>k;
    vi nums(k); f(i, k) cin>>nums[i];
    set<int> s;
    s.insert(0); s.insert(n);
    multiset<int> gaps;
    gaps.insert(n);
    for(int x : nums) {
        auto it = s.upper_bound(x);
        auto lit = it; --lit;
        int r=*it-x;
        int l=x-*lit;
        s.insert(x);
        gaps.erase(gaps.find(l+r)); // NOTE: erase removes all instances to decrememnt erase iterator
        gaps.insert(l); gaps.insert(r);
        // cout<<gaps<<en;
        cout<<*gaps.rbegin()<<en;
    }
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int mx; cin>>n>>mx;
    vi nums(n);
    f(i, n) cin>>nums[i];
    sort(all(nums));
    int i=0, j=n-1;
    int res = 0;
    while(i<=j) {
        if(nums[i] + nums[j] <= mx) {
            i++; j--;
        } else {
            j--;
        }
        res++;
    }
    cout<<res<<en;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int x;
    cin>>n>>x;
    vi nums(n);
    f(i, n) cin>>nums[i];
    map<int, int> mp;
    f(i, n) {
        if(mp.count(x - nums[i])) {
            cout<<mp[x-nums[i]]+1<<" "<<i+1<<en;
            return 0;
        }
        mp[nums[i]] = i;
    }
    cout<<"IMPOSSIBLE"<<en;
}
