// PI(s) - count prefix = suffix
vi res(n, 0);
int l = 0;
for(int r = 1; r<n; ++r)
    while(l>0 && s[l] != s[r]) l=res[l-1];
    if(s[l]==s[r]) l++;
    res[r]=l;
return res;

// Z(s) - count prefix = prefix
vi z(n, 0);
l=0; int r=0;
for(int i = 1; i<n; ++i)
    z[i] = max(0, min(z[i-l], r-i+1));
    while(i+z[i] < n && s[i+z[i]] == s[z[i]])
        l=i; r=i+z[i];
        z[i]++;


// Exact substring search
bool findSubstring(string& s, string& t) // Better for many queries
  int n=s.size(), m=t.size();
  vi pi = pi(s);
  int j=0;
  for(int i=0; i<n;)
    if(s[i]==t[j])
      i++; j++;
      if(j==n) cout<<"YES"<<en;
    else
      if(j>0) j=pi[j-1];
      if(j==0) i++;
bool findSubstring(string s, stirng p) // Better for single query
    string x = p+'#'+s;
    vi Z = z(x);
    for(...) if(z[i]==m) return true;


// Lexigraphically smallest rotation
s += s;
int start = 0;  // starting index of minimal rotation
for(int i = 0; i < n;)
    start = i;
    int j=i+1, k=i; // NOTE THAT THE POINTERS are i, j. K is an iterator
    while(j<2*n && s[j]>=s[k])
        if(s[j]>s[k]) k = i; // Not better, reset comparison
        else k++;
        j++;
    while(i<=k) i += (j-k);  // Note that this while loop is necessary for not TLE; must be > k
cout<<s.substr(start, n);


// Longest palindrome substring
string manacher(string& s)
    string arr = "#"; // Preprocess the string for unified odd/even palindrome handling
    for (char ch : s) arr+=ch, arr+="#";
    int n = arr.size();
    vi dp(n, 0); // Palindrome radii
    int c=0, r=0, mx=0, mxi = 0; // center, right, mx rad, mx index
    f(i, n)
        if (i < r) dp[i] = min(dp[2*c - i], r-i);
        while (i - dp[i] - 1 >= 0 && i + dp[i] + 1 < n && arr[i - dp[i] - 1] == arr[i + dp[i] + 1]) // Expand around the c
            dp[i]++;
        if (i + dp[i] > r) // Update c and r boundary if the palindrome at i expands past r
            c=i; r=i+dp[i];
        if (dp[i] > mx)
            mx = dp[i]; mxi = i;
    string res;
    for (int i = mxi-mx; i <= mxi+mx; ++i)
        if (arr[i] != '#') res.push_back(arr[i]);
    return res;


// Common problems
function countDistinctSubstrings(s):
    n = length(s)
    z = computeZ(s)  // Compute Z-array for the string
    total = 0
    for i from 0 to n - 1:
        total += n - i  // All suffixes starting from i
        total -= z[i]  // Subtract non-distinct parts matching the prefix
    return total

function hasPeriod(s):
    n = length(s)
    pi = computePi(s)
    period = n - pi[n-1]  // Length of the smallest period
    if n % period == 0:  // If period divides n, then it's a periodic string
        return true, period
    else:
        return false

function countPrefixOccurrences(s):
    n = length(s)
    pi = computePi(s)  // Compute π-array for s
    count = array of size n filled with 0
    for i from 0 to n - 1:
        count[pi[i]] += 1  // Track occurrences of the current border
    for i from n - 1 down to 1:
        count[pi[i-1]] += count[i]  // Accumulate occurrences for borders
    for i from 0 to n - 1:
        count[i] += 1  // Each prefix itself is an occurrence
    return count  // count[i] tells how many times prefix s[0:i] occurs in s

function countUniqueSubstrings(s):
    n = length(s)
    z = computeZ(s)  // Compute Z-array for s
    total = n * (n + 1) / 2  // Total substrings in string
    for i from 1 to n - 1:
        total -= z[i]  // Subtract the repeated substrings
    return total

// Longest palindrome substring using binary search + hashing
string longestPalindrome(string& s)
    vi fhash(sz(s)+1,0), bhash(sz(s)+1,0), power(sz(s)+1,1);
    f(i,sz(s)) fhash[i+1]=(fhash[i]*31+(s[i]-'a'+1))%MOD, bhash[i+1]=(bhash[i]*31+(s[sz(s)-i-1]-'a'+1))%MOD, power[i+1]=(power[i]*31)%MOD;
    auto getFHash=[&](int l,int r){return (fhash[r+1]-fhash[l]*power[r-l+1]%MOD+MOD)%MOD;};
    auto getBHash=[&](int l,int r){return (bhash[sz(s)-l]-bhash[sz(s)-r-1]*power[r-l+1]%MOD+MOD)%MOD;};
    auto hasPalindromeOfLength=[&](int L){f(i,sz(s)-L+1) if(getFHash(i,i+L-1)==getBHash(i,i+L-1)) return i; return -1;};
    int lo=1, hi=sz(s), start=0, maxLen=0;
    while(lo<=hi){
        int mid=(lo+hi)/2, l=hasPalindromeOfLength(mid);
        if(l!=-1) start=l, maxLen=mid, lo=mid+1;
        else hi=mid-1;
    }
    return s.substr(start,maxLen);

// Rare

// Suffix Automaton - ex: calculate distinct substrings in string S
// Variables:
// node[i]: state with len (longest suffix ending here), link (suffix link), nxt (transitions), dp (distinct substrings ending here)
// sz: total states, last: most recent state, N: length of input string
struct Node{ ll dp; int len, link; map<char,int> nxt; } node[2*maxN];
char S[maxN];
int N, sz, last;
void init()
    node[0].len = 0; node[0].link = -1; sz = 1; last = 0;
void extend(char c)
    int cur = sz++, p = last;
    node[cur].len = node[last].len + 1;
    while (p != -1 && !node[p].nxt.count(c))
        node[p].nxt[c] = cur, p = node[p].link;
    if (p == -1) node[cur].link = 0;
    else
        int q = node[p].nxt[c];
        if (node[p].len + 1 == node[q].len) node[cur].link = q;
        else
            int clone = sz++;
            node[clone] ={0, node[p].len + 1, node[q].link, node[q].nxt};
            while (p != -1 && node[p].nxt[c] == q)
                node[p].nxt[c] = clone, p = node[p].link;
            node[q].link = node[cur].link = clone;
    last = cur;
void calc(int u = 0)
    node[u].dp = 1;
    for (const auto& [c, v] : node[u].nxt)
        if (!node[v].dp) calc(v);
        node[u].dp += node[v].dp;
N = strlen(S);
init();
for (int i = 0; i < N; i++) extend(S[i]);
calc();
cout<<node[0].dp - 1); // Subtract 1 to exclude empty substring


// Suffix array
vector<int> pn(n), cn(n); // pn: shifted positions of suffixes, cn: new classes of suffixes
for (int h = 0; (1 << h) < n; ++h)
    for (int i = 0; i < n; i++)
        pn[i] = p[i] - (1 << h); // Shift suffix positions left by 2^h
        if (pn[i] < 0) pn[i] += n; // Wrap around for negative indices
    fill(cnt.begin(), cnt.begin() + classes, 0); // Reset count for radix sort
    for (int i = 0; i < n; i++) cnt[c[pn[i]]]++; // Count occurrences of each class
    for (int i = 1; i < classes; i++) cnt[i] += cnt[i-1]; // Cumulative count
    for (int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i]; // Place suffixes in sorted order
    cn[p[0]] = 0; // First suffix gets class 0
    classes = 1; // Total number of distinct classes
    for (int i = 1; i < n; i++)
        pair<int, int> cur ={c[p[i]], c[(p[i] + (1 << h)) % n]}; // Current 2^h-length substring
        pair<int, int> prev ={c[p[i-1]], c[(p[i-1] + (1 << h)) % n]}; // Previous 2^h-length substring
        if (cur != prev) ++classes; // New class if substrings differ
        cn[p[i]] = classes - 1; // Assign class to current suffix
    c.swap(cn); // Update classes for next iteration
return p; // Final suffix array










