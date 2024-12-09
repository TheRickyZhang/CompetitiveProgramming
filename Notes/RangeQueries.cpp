// Prefix sum, simple.
// Variant: 2D, Multiply, XOR
f(i, n)
    f(j,n)
        dp[i+1][j+1] = nums[i][j] + dp[i][j+1] + dp[i+1][j] - dp[i][j];
f(i, q)
    cin>>a>>b>>x>>y;
    ll res = dp[x][y] - dp[x][b-1] - dp[a-1][y] + dp[a-1][b-1];
    cout<<res<<en;

// Sparse Table - query min/max/gcd in O(1), O(log n) build, no modifications
int ln = log2(n) + 1;
vvi sparse(n, vi(ln, 0));
f(i, n) sparse[i][0] = nums[i]
for(int j = 1; (1<<j) <= n; ++j)
    for(int i = 0; i + (1<<j) <= n; ++i)
        sparse[i][j] = min(sparse[i][j-1], sparse[i+(1<<(j-1))][j-1]);
int ln = log2(r-l+1); // query from [l, r]
int mn = min(sparse[l][ln], sparse[r-(1<<ln)+1][ln]);


// Binary Indexed Tree (BIT)
void add(int i, int x)
	while(i<=n)
		bit[i] += x; x += x&-x
void sum(int i)
	int res = 0;
	while(i>0)
		res += bit[i]; i -= i&-1
	return res;

// Point updates, range queries (Common)
int pointUpdate(int i, int x)
	int d = x-nums[i]; nums[i] = x;
	add(i+1, d);
int rangeSum(int l, int r)
	return sum(r+1) - sum(l);

// Range updates, point queries: Difficult, but use BIT, with arr being a difference array rather than values array
int rangeUpdate(int l, int r, int x)
	add(l, x); add(r+1, -x);
int pointSum(int i)
    return sum(i);


// Segment trees
vi nums(N), tree(4*N); // vi lazy(4*N)

void build(int i, int a, int b)
    if(l==r) tree[x] = nums[a];
	else
        int mid = (a+b)/2;
        build(2*i, a, m); build(2*i+1, m+1, b);
        tree[i] = combine(2*i, 2*i+1)

/* Alternate version:
    if(r<a || b<l) return;
    if(l<=a && b<=r) return tree[i]
    No need for min/max call
*/
int query(int i, int a, int b, int l, int r)
    if(l > r) return sentinel;
    if(l==a && r==b) return tree[i];
    int mid = (a+b)/2;
    return sum(2*i, a, mid, l, min(r, mid)) + sum(2*i+1, mid+1, b, max(l, mid+1), r);
int update(int i, int a, int b, int pos, int newVal)
    if(a==b) tree[i] = newVal;
    else
        int mid = (a+b)/2;
        if(pos <= mid) update(2*i, a, mid, pos, newVal)
        else update(2*i+1, mid+1, b, pos, newVal);
        tree[i] = tree[2*i]+tree[2*i+1]

// Instance: Sum
void build(ll i, ll a, ll b)
    if(a==b)
        tree[i] = nums[a];
        return;
    ll mid = a+(b-a)/2;
    build(2*i, a, mid);
    build(2*i+1, mid+1, b);
    tree[i] = tree[2*i] + tree[2*i+1];
void update(ll i, ll a, ll b, ll pos, ll x)
    if(a==b) tree[i] = x;
    else
        ll m = a+(b-a)/2;
        if(pos <= m) update(2*i, a, m, pos, x);
        else update(2*i+1, m+1, b, pos, x);
        tree[i] = tree[2*i]+tree[2*i+1];
ll query(ll i, ll a, ll b, ll l, ll r)
    if(l>r) return 0;
    if(a==l && b==r) return tree[i];
    ll m = a+(b-a)/2;
    return query(2*i, a, m, l, min(r, m)) + query(2*i+1, m+1, b, max(l,m+1), r);
int main()
    cin>>n>>q;
    f(i, n) cin>>nums[i];
    build(1, 0, n-1);
    ll t, a, b;
    f(i, q)
        cin>>t>>a>>b;
        if(t==1) update(1, 0, n-1, a-1, b);
        else cout<<query(1, 0, n-1, a-1, b-1)<<en;
    return 0;

// Instance: Max subarray
struct node
    ll any{}, pre{}, post{}, cumSum{};
    ...
node combine(const node& a, const node& b)
    ll newAny = max({a.any, b.any, a.post + b.pre});
    ll newPre = max(a.pre, a.cumSum + b.pre);
    ll newPost = max(b.post, b.cumSum + a.post);
    ll cumSum = a.cumSum + b.cumSum;
    return{newAny, newPre, newPost, cumSum};
void build(ll i, ll a, ll b)
    if(a==b) tree[i] = node(nums[a]);
    else
        ll m = (a+b)/2;
        build(2*i, a, m);
        build(2*i+1, m+1, b);
        tree[i] = combine(tree[2*i], tree[2*i+1]);
void update(ll i, ll a, ll b, ll pos, ll val)
    if(a==b) tree[i] = node(val);
    else
        ll m = (a+b)/2;
        if(pos<=m) update(2*i, a, m, pos, val);
        else update(2*i+1, m+1, b, pos, val);
        tree[i] = combine(tree[2*i], tree[2*i+1]);
node query(ll i, ll a, ll b, ll l, ll r)
    if(l>r) return node(NINF);
    if(a==l&&b==r) return tree[i];
    ll m = (a+b)/2;
    node x = query(2*i, a, m, l, min(r, m));
    node y = query(2*i+1, m+1, b, max(l, m+1), r);
    if(x.any == NINF) return y; if(y.any==NINF) return x;
    return combine(x, y);

// Extension: Lazy Segment Trees
void applyLazy(int i, int a, int b)
	if(lazy[i]==0) continue;
	tree[i] += lazy[i] * (b-a+1)    // SUM
	if(a!=b)
		lazy[2*i] += lazy[i];		// SUM
		lazy[2*i+1] ++ lazy[i];		// SUM
	lazy[i] = 0;
void rangeUpdate(int i, int a, int b, int l, int r, int val)
	applyLazy(i, a ,b);
	if(a>b||a>r||b<l) return;
	if(a>=l && b<=r)
		update(tree[i], val);       // SUM
		if(a != b)
			lazy[2*i] += val;       // SUM
			lazy[2*i+1] += val;		// SUM
	else
		int m = a+(b-a)/2;
		rangeUpdate(2*i, a, m, l, r, min(r, mid), val);
		rangeUpdate(2*i+1, m+1, b, max(l, mid + 1), r, val);
		tree[i] = combine(tree[2*i], tree[2*i+1])    // SUM
int query(int i, int a, int b, int l, int r)
	applyLazy(i, a, b);
	if(a>r || b<l) return 0;
	if(a >= l || b <= r) return tree[i];
	int m - a+(b-a)/2;
	return combine(rangeSum(2*i, a, m, l, min(r, m)), rangeSum(2*i+1, m+1, b, max(l, m+1), r);

// Extension: Coordinate compression. (! a b) replaces ath element with b, and (? a b) counts number a<=x<=b
ll bit[MX];
vector<int> vals;
int n, q;
void update(int i, int val)
    for(; i <= MX; i += i & (-i)) bit[i] += val;
void add(int x, int b)
    int ind = upper_bound(vals.begin(), vals.end(), x) - vals.begin();
    update(ind, b);
ll sum(int x)
    ll res = 0;
    for (; x; x -= x & (-x)) res += bit[x];
    return res;
ll query(int x)
    int ind = upper_bound(vals.begin(), vals.end(), x) - vals.begin();
    return sum(ind);
cin >> n >> q;
vector<int> arr(n); vals = arr;
for (int i = 0; i < n; i++) cin >> arr[i];
vector<array<int, 3>> rec;
for (int i = 0; i < q; i++)
    char t;
    int a, b;
    cin >> t >> a >> b;
    rec.push_back({t == '?', a, b});
    if (t == '!') vals.push_back(b);
sort(vals.begin(), vals.end());
vals.erase(unique(vals.begin(), vals.end()), vals.end());
for (int i = 0; i < n; i++) add(arr[i], 1);
for (auto u : rec)
    u[1]--;
    if (u[0] == 0)
        add(arr[u[1]], -1);
        arr[u[1]] = u[2];
        add(arr[u[1]], 1);
    else
        cout << query(u[2]) - query(u[1]) << '\n';

// Rare
// Merge Sort Tree: Kth smallest, count # <x, cout distinct elements in range
void build(int i, int l, int r, vector<int>& a)
    if (l == r) t[i] ={a[l]}; // t is vvi
    else
        int m = (l + r) / 2;
        build(2 * i, l, m, a); build(2 * i + 1, m + 1, r, a);
        merge(all(t[2*i], all(t[2*i+1]), back_inserter(t[i]));
int qry(int i, int l, int r, int ql, int qr, int k)
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return upper_bound(t[i].begin(), t[i].end(), k - 1) - t[i].begin();
    int m = (l + r) / 2;
    return qry(2 * i, l, m, ql, qr, k) + qry(2 * i + 1, m + 1, r, ql, qr, k);

/*
*Operation	                    Technique
Sum / Min / Max	                Simple Segment Tree
K-th Smallest in Range	        Merge-Sort Tree
Count Distinct in Range	        Merge-Sort Tree / Mo's Algo
Maximum Subarray Sum	        Modified Segment Tree
Range Update, Point Query	    Difference Array BIT
Frequency Count	                Persistent Segment Tree
*/