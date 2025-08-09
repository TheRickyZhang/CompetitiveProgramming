#include  <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define op_ operator
#define cx_ constexpr
#define fn function
#define f(i, to) for (int i = 0; i < to; ++i)
#define fe(i, to) for (int i = 1; i <= to; ++i)
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define repr(i, a, b) for (int i = a; i >= b; --i)
#define ff first
#define ss second
#define pb push_back
#define fora(a, x) for (auto &(a) : (x))
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define quit(s) do{ cout<<(s)<<en; return; }while(false)

#define int long long
tpl_<tn_ T>using v=vector<T>; using vi=v<int>; tpl_<tn_ T>using vv=v<v<T>>; using ll=long long; using pii=pair<int,int>;
using vb=v<bool>; using vvb=v<vb>; using vs=v<string>; using iii=array<int, 3>; using i4=array<int, 4>;
using vvi=v<vi>; using vll=v<ll>; using vpii=v<pii>; using vvpii=v<vpii>;
tpl_<tn_ K,tn_ T>using ump=unordered_map<K,T>; tpl_<tn_ T>using ust=unordered_set<T>; tpl_<tn_ T>using mset=multiset<T>;
tpl_<tn_ T> using pq=priority_queue<T>; tpl_<tn_ T>using mpq=priority_queue<T,v<T>,greater<T>>;
tpl_<tn_ It, tn_ T> auto leq_bound(It l,It r,T x){auto it=upper_bound(l,r,x); return it!=l ? prev(it):r;}
tpl_<tn_ It, tn_ T> auto less_bound(It l,It r,T x){auto it=lower_bound(l,r,x);return it!=l ? prev(it):r;}
tpl_<tn_ T, tn_ U> T fstTrue(T l, T r, U ff) { for(++r; l<r;) { T m=l+(r-l)/2; if(ff(m)) r=m; else l=m+1; } return l;}
tpl_<tn_ T, tn_ U> T lstTrue(T l, T r, U ff) { for(++r; l<r;) { T m=l+(r-l)/2; if(ff(m)) l=m+1; else r=m; } return l-1;}
tpl_<tn_ T> bool cmn(T& a, T b) {return b<a ? a=b,1 : 0;} tpl_<tn_ T> bool cmx(T& a, T b) {return a<b ? a=b,1 : 0;}
cx_ auto en="\n"; cx_ auto sp=" "; using str=string; typedef fn<void(int,int)>fvii; typedef fn<void(int,int,int)>fviii;



tpl_<tn_ T> struct fun {
    T a, b;
    fun(T a, T b): a(a), b(b) {}
    T at(T x) const { return a*x + b; }
};
tpl_<tn_ T, bool upperHull = true>
struct CHT {
    deque<fun<T>> h;
    static bool badMiddle(const fun<T>& x, const fun<T>& y, const fun<T>& z) {
        auto lhs = static_cast<__int128>(y.b - x.b) * (x.a - z.a);
        auto rhs = static_cast<__int128>(z.b - y.b) * (x.a - y.a);
        return upperHull ? (lhs >= rhs) : (lhs <= rhs);
    }
    void add(fun<T> ln) {
        if (!upperHull) { ln.a = -ln.a; ln.b = -ln.b; }
        while (h.size() >= 2 && badMiddle(h[h.size()-2], h.back(), ln)) h.pop_back();
        h.pb(ln);
    }
    T query(T x) {
        if (h.empty()) return upperHull ? numeric_limits<T>::lowest() : numeric_limits<T>::max();
        while (h.size() >= 2) {
            T v0 = h[0].at(x), v1 = h[1].at(x);
            if (upperHull ? (v1 >= v0) : (v1 <= v0)) h.pop_front(); else break; }
        T res = h.front().at(x); return upperHull ? res : -res;
    }
};



#include <catch2/catch_test_macros.hpp>

TEST_CASE("cht behaves as expected", "[cht]") {
	cht<int> c({{2, 1}, {3, 2}, {1, -2}});
	REQUIRE(c.size() == 2);
	REQUIRE(c.query(-4).first == -10);
	REQUIRE(c.query(-3).second == 1);
	REQUIRE(c.query(-3).first == -7);
	REQUIRE(c.query(-2).first == -4);
	REQUIRE(c.query(0).first == -2);
	REQUIRE(c.query(2).first == 0);
	REQUIRE(c.query(2).second == 2);
	cht<int> c2({{1, 0}, {2, 2}, {-1, 0}});
	REQUIRE(c2.size() == 3);
	REQUIRE(c2.query(-3).first == -4);
	REQUIRE(c2.query(-2).first == -2);
	REQUIRE(c2.query(-1).first == -1);
	REQUIRE(c2.query(0).first == 0);
	REQUIRE(c2.query(1).first == -1);
}

TEST_CASE("lichao_tree behaves as expected", "[cht]") {
	lichao_tree<int> c(-100, 100);
	c.push_line({2, 1});
	c.push_line({3, 2});
	c.push_line({1, -2});
	REQUIRE(c.query(-4).first == -10);
	REQUIRE(c.query(-3).second == 1);
	REQUIRE(c.query(-3).first == -7);
	REQUIRE(c.query(-2).first == -4);
	REQUIRE(c.query(0).first == -2);
	REQUIRE(c.query(2).first == 0);
	REQUIRE(c.query(2).second == 2);
	lichao_tree<int> c2(-100, 100);
	c2.push_line({1, 0});
	c2.push_line({2, 2});
	c2.push_line({-1, 0});
	REQUIRE(c2.query(-3).first == -4);
	REQUIRE(c2.query(-2).first == -2);
	REQUIRE(c2.query(-1).first == -1);
	REQUIRE(c2.query(0).first == 0);
	REQUIRE(c2.query(1).first == -1);
}
