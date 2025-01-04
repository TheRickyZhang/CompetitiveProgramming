#include <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define f(i, to) for (int i = 0; i < (to); ++i)
#define fe(i, to) for (int i = 1; i <= (to); ++i)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define repr(i, a, b) for (int i = (a); i >= (b); --i)
#define str string
#define ff first
#define ss second
#define pb push_back
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define setIO(name) ifstream cin(name".in"); ofstream cout(name".out");
tpl_<tn_ T>using v=vector<T>; using ll=long long; using pii=pair<int,int>; using pll=pair<ll,ll>; using t3=tuple<int,int,int>; using t4=tuple<int,int,int,int>;
using vi=v<int>; using vb=v<bool>; using vs=v<string>; using vvi=v<vi>; using vll=v<ll>; using vvll=v<vll>; using vpii=v<pii>; using vvpii=v<vpii>; using vpll=v<pll>; using vvpll=v<vpll>;
tpl_<tn_ K,tn_ V>using ump=unordered_map<K, V>; tpl_<tn_ T>using ust=unordered_set<T>; tpl_<tn_ K,tn_ V>using rmap=map<K,V,greater<K>>; tpl_<tn_ T>using rset=set<T,greater<T>>; tpl_<tn_ T>using mset=multiset<T>; tpl_<tn_ T>using rmset=multiset<T,greater<T>>;
tpl_<tn_ T>using pq=priority_queue<T>; tpl_<tn_ T>using mpq=priority_queue<T,vector<T>,greater<T>>;
tpl_<tn_ A, tn_ B> ostream& operator<<(ostream& os, const pair<A, B>& p) { return os << "(" << p.ff << ", " << p.ss << ")"; }
tpl_<tn_ C, tn_ T = enable_if_t<!is_same_v<C, str>, typename C::value_type>> ostream& operator<<(ostream& os, const C& v) { os << "{"; str sep; for (const T& x : v) os << sep << x, sep = ", "; return os << "}"; }
tpl_<tn_ K, tn_ V> ostream& operator<<(ostream& os, const map<K, V>& m) { os << "{"; str sep; for (const auto& kv : m) os << sep << kv.ff << ": " << kv.ss, sep = ", "; return os << "}"; }
struct pairHash{tpl_<class T1,class T2>size_t operator()(const pair<T1,T2>&p)const{return hash<T1>{}(p.first)^ (hash<T2>{}(p.second)<<1);}}; struct vectorHash{tpl_<class T>size_t operator()(const vector<T>&v)const{size_t hashValue=0;for(const T&i:v)hashValue^=hash<T>{}(i)+0x9e3779b9+(hashValue<<6)+(hashValue>>2);return hashValue;}};
const vector<pii> dirs={{1,0},{0,-1},{0,1},{-1,0}}; auto check=[](auto y,auto x,auto m,auto n){return y>=0&&y<m&&x>=0&&x<n;};
constexpr int MOD=1000000007; constexpr int INF=1000000000; constexpr ll INFL=0x3f3f3f3f3f3f3f3f; constexpr auto en = "\n"; constexpr auto sp = " ";

int t, k, n, m;
const int MAX_POS = 1000000000;

int main() {
	freopen("angry.in", "r", stdin);

	int n;
	cin >> n;
	vector<int> bales(n);
	for (int i = 0; i < n; i++) {
		cin >> bales[i];
		bales[i] *= 2; // avoid floats by doubling coordinates
	}
	sort(bales.begin(), bales.end());

	// Iterative version of 'push'
	function<bool(int, int, int, bool)> push = [&](int pos, int idx, int r, bool dir) {
		// We'll simulate the old recursion with a stack of states:
		// Each state is (current position, current index, current radius, direction)
		stack<array<int, 4>> st;
		st.push({pos, idx, r, (int)dir});

		while (!st.empty()) {
			auto [curPos, curIdx, curR, curDir] = st.top();
			st.pop();

			// Base checks for finishing
			if (curDir == 0) { // going right
				if (curIdx >= n - 1) {
					// If idx is beyond or at the rightmost bale, check coverage
					return (curIdx >= n || curPos + curR >= bales[curIdx]);
				}
				if (curPos + curR >= bales.back()) {
					return true;
				}
				int new_idx = curIdx;
				while (new_idx < n && curPos + curR >= bales[new_idx]) {
					new_idx++;
				}
				// no progression
				if (new_idx == curIdx) return false;

				st.push({bales[new_idx - 1], new_idx, curR - 2, 0});
			}
			else { // going left
				if (curIdx <= 0) {
					return (curIdx < 0 || curPos - curR <= bales[curIdx]);
				}
				if (curPos - curR <= bales[0]) {
					return true;
				}
				int new_idx = curIdx;
				while (new_idx >= 0 && curPos - curR <= bales[new_idx]) {
					new_idx--;
				}
				// no progression
				if (new_idx == curIdx) return false;

				st.push({bales[new_idx + 1], new_idx, curR - 2, 1});
			}
		}
		return false; // stack empty => no successful path
	};

	int lo = 0;
	int hi = MAX_POS * 2;
	while (lo < hi) {
		int power = lo + (hi - lo) / 2;

		// find largest initial position so explosions go all the way left
		int pos_lo = 0;
		int pos_hi = MAX_POS * 2;
		while (pos_lo < pos_hi) {
			int pos = pos_lo + (pos_hi - pos_lo + 1) / 2;
			int close = int(lower_bound(bales.begin(), bales.end(), pos) - bales.begin());

			if (close < n && push(pos, close, power, true)) {
				pos_lo = pos;
			} else {
				pos_hi = pos - 1;
			}
		}

		int close = int(upper_bound(bales.begin(), bales.end(), pos_lo) - bales.begin());
		if (push(pos_lo, close, power, false)) {
			hi = power;
		} else {
			lo = power + 1;
		}
	}

	freopen("angry.out", "w", stdout);
	cout << fixed << setprecision(1) << (double)lo / 2 << endl;
}
//
// int main() {
//     setIO("angry");
//     ios::sync_with_stdio(false); cin.tie(nullptr);
//     // int t; cin>>t; f(i, n) solve();
//     cin>>n;
//     vi nums(n);
//     f(i, n) {
//         int x; cin>>x; nums[i]=x*2; // Double all distances
//     }
//     sort(all(nums));
//
//     vvi dists(n, vi(2, 2*INF)); // 1 or 2 elements adjacent to
//     f(i, n-1) {
//         int d = nums[i+1]-nums[i];
//         dists[i][1]=d; dists[i+1][0]=d;
//     }
//     // cout<<nums<<en<<dists<<en;
//
//     auto check = [&](int x) {
//         // int temp=0, x1=-1, x2=-1;
//         f(i, n) {
//             int j = upper_bound(all(nums), nums[i]+2*x) - nums.begin(); if(j>0) j--;   // <= upper
//             vb exploded(n, false);
//             int marked=0;
//             function<void(int, int, bool)> mark = [&](int k, int r, bool isLeft) {
//                 if(exploded[k]) return;
//                 exploded[k]=true; marked++;
//                 if(isLeft && dists[k][0]<=r) mark(k-1, r-2, isLeft);
//                 if(!isLeft && dists[k][1]<=r) mark(k+1, r-2, isLeft);
//             };
//             rep(k, i+1, j-1) {      // Mark everything in middle
//                 exploded[k]=true;
//                 marked++;
//             }
//             mark(i, x-2, true); mark(j, x-2, false);  // Always optimal to start exploding from endpoints
//             if(marked==n) {
//                 // cout<<x<<sp<<"works from"<<sp<<i<<sp<<j<<en;
//                 return true;
//             }
//             // if(marked > temp) {
//             //     temp=marked;
//             //     x1=i;
//             //     x2=j;
//             // }
//         }
//         // cout<<x<<" fails, best "<<temp<<" at "<<x1<<sp<<x2<<en;
//         return false;
//     };
//
//     int l=0, r=2*INF; // These are half-unit increments
//     while(l<r) {
//         int m=l+(r-l)/2;
//         if(!check(m)) {
//             l=m+1;
//         }
//         else r=m;
//     }
//     if(l&1) cout<<l/2<<".5"<<en;
//     else cout<<l/2<<".0"<<en;
// }
