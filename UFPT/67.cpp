#include <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define op_ operator
#define cx_ constexpr
#define fn function
#define F_GET(_1, _2, _3, NAME, ...) NAME
#define f(...) F_GET(__VA_ARGS__, f3, f2)(__VA_ARGS__)
#define f2(i, to) for (int i = 0; i < (to); ++i)
#define f3(i, from, to) for (int i = (from); i < (to); ++i)
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define repr(i, a, b) for (int i = a; i >= b; --i)
#define ff first
#define ss second
#define pb push_back
#define fora(a, x) for (auto &(a) : (x))
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define print(x) (cout<<#x<<"="<<(x)<<endl)
#define quit(s) do{ cout<<(s)<<en; return; }while(false)

#include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
tpl_<tn_ T> using oset = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<>, __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;
tpl_<tn_ K, tn_ V> using omap = __gnu_pbds::tree<K, V, less<>, __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;

// Aliases
#define int long long
using str=string; using ll=long long; using pii=pair<int, int>; using iii=array<int, 3>; using i4=array<int, 4>;
tpl_<tn_ T> struct v : vector<T> {
  using vector<T>::vector; v(const vector<T>& a) : vector<T>(a) {}
  v(vector<T>&& a) : vector<T>(std::move(a)) {}
  friend istream& operator>>(istream& in, v& a) { for(auto& x : a) in>>x; return in; }
  pair<map<T,int>, v<T>> compress() {
    v<T> vals = *this; sort(vals.begin(), vals.end()); vals.erase(unique(vals.begin(), vals.end()), vals.end());
    map<T,int> mp; f(i, vals.size()) mp[vals[i]] = i; for(auto& x : *this) x = mp[x];
    return {mp, vals}; }
};
tpl_<tn_ T> struct vv : v<v<T>> {
  using v<v<T>>::v; vv(const v<v<T>>& a) : v<v<T>>(a) {} vv(v<v<T>>&& a) : v<v<T>>(std::move(a)) {}
  vv(int n, int m, T val=T()) : v<v<T>>(n, v<T>(m, val)) {}
  using v<v<T>>::operator[];
  void prefix() { int n=this->size(), m=n?(*this)[0].size():0; f(i,n) f(j,m) {
      if(i) (*this)[i][j]+=(*this)[i-1][j]; if(j) (*this)[i][j]+=(*this)[i][j-1];
      if(i&&j) (*this)[i][j]-=(*this)[i-1][j-1]; } }
  void row_prefix() { int n=this->size(), m=n?(*this)[0].size():0; f(i,n) f(j,m-1) (*this)[i][j+1]+=(*this)[i][j]; }
  void col_prefix() { int n=this->size(), m=n?(*this)[0].size():0; f(i,n-1) f(j,m) (*this)[i+1][j]+=(*this)[i][j]; }
  friend istream& operator>>(istream& in, vv& g) { for(auto& row : g) for(auto& x : row) in>>x; return in; }
};
using vi = v<int>; using vb=v<bool>; using vs=v<string>; using vvi = vv<int>; 
tpl_<tn_ K,tn_ T>using ump=unordered_map<K,T>; tpl_<tn_ T>using ust=unordered_set<T>; tpl_<tn_ T>using mset=multiset<T>;
tpl_<tn_ T> using pq=priority_queue<T>; tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;
typedef fn<void(int,int)>fvii; typedef fn<void(int,int,int)>fviii;

// Constants
cx_ ll INF=1e18; cx_ int B=62; cx_ int N=100000; cx_ int MOD=1e9+7; // 998244353;
cx_ auto en="\n"; cx_ auto sp=" ";
auto _max=[](int a, int b) {return max(a, b);}; auto _min=[](int a, int b) {return min(a, b);};
auto _sortinv=[](const pii& a,const pii& b) {if(a.ff==b.ff) return a.ss > b.ss; return a.ff<b.ff;};
cx_ ll msb(ll x) { return x ? 63 - __builtin_clzll(x) : -1; } cx_ ll lsb(ll x) { return x ? __builtin_ctzll(x) : -1; }

// Input/Output
void setIO(const str&name=""){ios_base::sync_with_stdio(false);cin.tie(nullptr); if(!name.empty())
    {freopen((name+".in").c_str(),"r",stdin);freopen((name+".out").c_str(),"w",stdout);}}
tpl_<tn_ A,tn_ B>ostream& op_<<(ostream& os,const pair<A,B>& p){return os<<"("<<p.ff<<", "<<p.ss<<")";}
tpl_<tn_ A>ostream& op_<<(ostream& o,const v<v<A>>& m){for(auto& r:m){o<<"{";for(auto& e:r)o<<e<<" ";o<<"}\n";}return o;}
tpl_<tn_ K,tn_ T>ostream& op_<<(ostream& o,const map<K,T>& m){o<<"{";for(auto& p:m)o<<p.ff<<":"<<p.ss<<", ";return o<<"}";}
template <typename...> using void_t_ = void;
template <typename T> struct StringLike : std::is_convertible<T, std::string_view> {};
template <typename C, typename = void> struct HasBeginEnd : std::false_type {};
template <typename C> struct HasBeginEnd<C, void_t_<
    decltype(std::begin(std::declval<const C&>())),
    decltype(std::end(std::declval<const C&>()))
>> : std::true_type {};
template <typename C, typename = void> struct HasStreamableElem : std::false_type {};
template <typename C> struct HasStreamableElem<C, void_t_<
    decltype( std::declval<ostream&>() << *std::begin(std::declval<const C&>())) >> : std::true_type {};
template <typename C>
struct PrintableRange : std::integral_constant<bool,
    !StringLike<C>::value && HasBeginEnd<C>::value && HasStreamableElem<C>::value > {};
tpl_<tn_ C, typename std::enable_if<PrintableRange<C>::value, int>::type = 0>
ostream& op_<<(ostream& os, const C& v) { for (const auto& x : v) os << x << " "; return os; }
struct cind{tpl_<tn_ T> cind& op_>>(T &x){cin>>x;--x;return *this;}} cind;
struct bout{tpl_<tn_ T> bout& op_<<(T x){if cx_(is_integral_v<T>){int y=x;if(y==0){cout<<'0';return *this;} if(y<0)
    {cout<<'-';y=-y;}str s;while(y){s.pb('0'+(y&1));y>>=1;}reverse(all(s));cout<<s;}else cout<<x;return *this;}} bout;




enum Op {
  ADD, SUB,
  MULT, DIV
};

void solve() {
  int n; cin >> n;
  vector<pair<Op, int>> res;
  auto addOp = [&](Op op, int x) {
    if(op == DIV) { assert(n % x == 0); n /= x; }
    else if(op == ADD) n += x;
    else if(op == SUB) n -= x;
    else assert(false);
    res.emplace_back(op, x);
  };
  while(n >= 6) {
    int r6 = n % 6, r7 = n % 7;
    int a6 = min(r6, 6 - r6), a7 = min(r7, 7 - r7);
    if(a6 <= a7) {
      if(r6 <= 3) f(i, r6) addOp(SUB, 7);
      else f(i, 6 - r6) addOp(ADD, 7);
      addOp(DIV, 6);
    } else {
      if(r7 <= 3) f(i, r7) addOp(ADD, 6);
      else f(i, 7 - r7) addOp(SUB, 6);
      addOp(DIV, 7);
    }
  }
  int m = n;
  f(i, m) {
    addOp(ADD, 6);
    addOp(SUB, 7);
  }
  reverse(all(res));
  assert((int)res.size() <= 67);
  cout<<res.size()<<en;
  for(auto [op, x] : res) {
    if(op == ADD) cout<<"- "<<x<<en;
    else if(op == SUB) cout<<"+ "<<x<<en;
    else if(op == DIV) cout<<"* "<<x<<en;
    else assert(false);
  }
}

// void solve() {
//   int n; cin >> n;
//   vector<pair<Op, int>> res;
//   auto addOp = [&](Op op, int x) {
//     if(op == DIV) {
//       assert(n % x == 0);
//       n /= x;
//     } else if(op == ADD) {
//       n += x;
//     } else if(op == SUB) {
//       n -= x;
//     } else assert(false);
//     res.emplace_back(op, x);
//   };
//   while(n > 3) {
//     int rem7 = n % 7;
//     int rem6 = n % 6;
//     int prev = n;
//     if(rem7 >= 1 && rem7 <= 3) {
//       f(i, rem7) {
//         addOp(ADD, 6);
//       }
//       addOp(DIV, 7);
//     } else if(rem7 == 0) {
//       addOp(DIV, 7);
//     } else if(rem7 == 6) {
//       addOp(ADD, 7);
//       addOp(SUB, 6);
//       addOp(DIV, 7);
//     }
//     else if(rem6 >= 3 && rem6 <= 5) {
//       f(i, 6 - rem6) {
//         addOp(ADD, 7);
//       }
//       addOp(DIV, 6);
//     } else if(rem6 == 0) {
//       addOp(DIV, 6);
//     } else if(rem6 == 1) {
//       addOp(ADD, 6);
//       addOp(SUB, 7);
//       addOp(DIV, 6);
//     }
//     else if(rem7 == 5 && rem6 == 2) {
//       f(_, 4) addOp(ADD, 7);
//       f(_, 2) addOp(SUB, 6);
//     } else if(rem7 == 4 && rem6 == 2) {
//       f(_, 4) addOp(ADD, 6);
//       f(_, 2) addOp(SUB, 7);
//     } else {
//       assert(false);
//     }
//   }
//   int m = n;
//   f(i, m) {
//     addOp(ADD, 6);
//     addOp(SUB, 7);
//   }
//   reverse(all(res));
//   assert(res.size() <= 67);
//   cout << res.size() << en;
//   for(auto [op, x] : res) {
//     if(op == ADD) cout << "-";
//     else if(op == SUB) cout << "+";
//     else if(op == DIV) cout << "*";
//     else assert(false);
//     cout << " ";
//     cout << x << en;
//
//   }
// }

int32_t main() {
  setIO();
  solve();
}
