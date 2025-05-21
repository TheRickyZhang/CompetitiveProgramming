#include  <bits/stdc++.h>
using namespace std;

#define tpl_ template
#define tn_ typename
#define cx_ constexpr
#define fn function
#define f(i, to) for (int (i) = 0; (i) < (to); ++(i))
#define fe(i, to) for (int (i) = 1; (i) <= (to); ++(i))
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); ++(i))
#define repr(i, a, b) for (int (i) = (a); (i) >= (b); --(i))
#define ff first
#define ss second
#define pb push_back
#define fora(a, x) for (auto &(a) : (x))
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define quit(s) do{ cout<<(s)<<en; return; }while(false)

#define int long long
tpl_<tn_ T>       using v = vector<T>; using ll=long long; using pii=pair<int,int>; using pll=pair<ll,ll>; using iii=array<int, 3>;  using i4=array<int, 4>;

// Very optimized tree
// class F is typedef of specific function, though can be inferred from constructor
tpl_<tn_ T, class F>
struct PersSegtree {
    int n;
    F c;
    T z;
    struct Node {
        T x;
        int l, r;
        Node(T x, int l = -1, int r = -1) : x(x), l(l), r(r) {}
    };
    v<Node> pool;
    int pit = 0;
    int nodes(T x,int l=0,int r=0){
        pool.pb({x, l, r});
        return pit++;
    }
    PersSegtree(int n, F c, T z = T())
      : n(n), c(std::move(c)), z(z)
    {
        pool.reserve(n*20); // Generally a safe amount
        nodes(z, 0, 0); // To avoid -1 checks we can set 0 as a sentinel. Only fails if we want lazy tags as well
    }
    int _modify(int i, int l, int r, int p, T x, bool upd) {
        int u = nodes(z);
        if (l == r) {
            pool[u].x = upd ? c(pool[i].x, x) : x;
            return u;
        }
        int m = (l + r) >> 1;
        if (p <= m) {
            int nl = _modify(pool[i].l, l, m, p, x, upd);
            pool[u].l = nl;
            pool[u].r = pool[i].r;
        } else {
            int nr = _modify(pool[i].r, m+1, r, p, x, upd);
            pool[u].r = nr;
            pool[u].l = pool[i].l;
        }
        pool[u].x = c(pool[ pool[u].l ].x, pool[ pool[u].r ].x);
        return u;
    }
    T _query(int i,int l,int r,int a,int b){
        if(a>r||b<l) return z;
        if(a<=l&&r<=b) return pool[i].x;
        int m=(l+r)>>1;
        return c(_query(pool[i].l,l,m,a,b),
                 _query(pool[i].r,m+1,r,a,b));
    }
    int update(int i, int p, T x) {
        return _modify(i, 0, n-1, p, x, true);
    }
    int add(int i, int p, T x) {
        return _modify(i, 0, n-1, p, x, false);
    }
    T query(int i, int a, int b) {
        return _query(i, 0, n-1, a, b);
    }
};


// Example iterative optimized usage
/*
auto combine = [](int x, int y) {
    return min(x, y);
};
PersSegtree tree(n, combine, INF+1);
vi nodes(n+1);
nodes[0] = tree.build(0, n-1);
int m = copy.size();
vi prev(m, -1);
f(i, n) {
    if(prev[a[i]] >= 0) {
        nodes[i+1] = tree.update(nodes[i], prev[a[i]], i-prev[a[i]]);
    } else {
        nodes[i+1] = nodes[i];
    }
    prev[a[i]] = i;
}
f(i, k) {
    int l, r; cind>>l>>r;
    int res = tree.query(nodes[r+1], l, r);
    if(res == INF+1) cout<<-1<<en;
    else cout<<res<<en;
}

auto nodeLeft = [&](int u) {
    return tree.pool[u].l;
};
auto nodeRight = [&](int u) {
    return tree.pool[u].r;
};
auto getLeft = [&](int u) {
    return tree.pool[tree.pool[u].l].x;
};
auto getRight = [&](int u) {
    return tree.pool[tree.pool[u].r].x;
};
// Root u, root v, root lca(u, v), root par(lca(u, v))
function<int(int, int, int, int, int, int, int)> kthMinimum = [&](int ru, int rv, int rw, int rpw, int l, int r, int k) {
    if(l == r) return l;
    int m = (l+r) / 2;
    int leftCount = getLeft(ru) + getLeft(rv) - getLeft(rw) - getLeft(rpw);
    if(leftCount >= k) {
        return kthMinimum(nodeLeft(ru), nodeLeft(rv), nodeLeft(rw), nodeLeft(rpw), l, m, k);
    } else {
        return kthMinimum(nodeRight(ru), nodeRight(rv), nodeRight(rw), nodeRight(rpw), m+1, r, k - leftCount);
    }
};
f(i, q) {
    int u, v, k; cind>>u>>v; cin>>k;
    int w = getLCA(up, dep, u, v, tin, tout);
    int pw = par[w];
    int res = kthMinimum(roots[u], roots[v], roots[w], roots[pw], 0, m-1, k);
    cout<<b[res]<<en; // Don't forget to convert back to noncompressed value!
}
*/

// Check out https://drive.google.com/file/d/0BwGLW04WRv0ITEZjRWlMSFc2bk0/view?resourcekey=0-1Zvsu-oMrdNsCuCIU3xGNA from USACO persistent data structures for picture + practice problems
template<typename T>
struct PersSegtree {
    struct Node {
        T x;
        Node *l, *r;
        explicit Node(T _x, Node* _l=nullptr, Node* _r=nullptr)
          : x(_x), l(_l), r(_r) {}
    };
    int n;
    function<T(T, T)> c;
    T z;
    // Note that we should maintain our list of roots OUTSIDE the class since this is only responsible for creating/returning these nodes
    // Usage: set roots[0] = build(0, n-1) ... and then call add/update along the secondary dimension (ex. t[i] = add(t[i-1], pos, x);)
    PersSegtree(int n, function<T(T, T)> c, const T& z = T()) : n(n), c(std::move(c)), z(z) {}
    Node* build(int l, int r) {
        if(l == r) return new Node(z);
        int m = (l+r)/2;
        Node* nl = build(l, m), *nr = build(m+1, r);
        return new Node(c(nl->x, nr->x), nl, nr);
    }
    // Note that we always RETURN a new node
    Node* _modify(Node* i, int l, int r, int pos, T x, bool upd) {
        if(l == r) {
            return (upd ? new Node(x) : new Node(c(i->x, x)));
        }
        int m = (l+r)/2;
        if(pos <= m) {
            Node* nl = _modify(i->l, l, m, pos, x, upd);
            return new Node(c(nl->x, i->r ->x), nl, i->r);
        } else {
            Node* nr = _modify(i->r, m+1, r, pos, x, upd);
            return new Node(c(nr->x, i->l->x), i->l, nr);
        }
    }
    Node* update(Node* i, int pos, T x) {
        return _modify(i, 0, n-1, pos, x, true);
    }
    Node* add(Node* i, int pos, T x) {
        return _modify(i, 0, n-1, pos, x, false);
    }
    T _query(Node* i, int l, int r, int a, int b) {
        if(l > r || b < l || a > r) return z;
        if(a <= l && r <= b) return i->x;
        int m = (l+r)/2;
        return c(_query(i->l, l, m, a, b), _query(i->r, m+1, r, a, b));
    }
    T query(Node* i, int a, int b) {
        return _query(i, 0, n-1, a, b);
    }
};


// Example usage: Missing Coin Sum Queries
// int32_t main() {
//     setIO();
//     cin>>n>>k;
//     vi a(n); read(a);
//     vi b = a; sort(all(b));
//     b.erase(unique(all(b)), b.end());
//     int m = b.size(); // This will be the index we use for the tree for accurate range-sums
//     map<int, int> mp;
//     f(i, m) mp[b[i]] = i;
//
//     PersSegtree<int> tree(m, ad);
//     v<PersSegtree<int>::Node*> nodes(n+1); // Use n+1 since we need to start with 0 as the default tree
//     nodes[0] = tree.build(0, m-1);
//     f(i, n) {
//         nodes[i+1] = tree.add(nodes[i], mp[a[i]], a[i]); // Why have pos as mp[a[i]]?
//     }
//     auto sum = [&](int l, int r, int x) {
//         // Note we shifted because nodes is 1-indexed
//         return tree.query(nodes[r+1], 0, x) - tree.query(nodes[l], 0, x);
//     };
//     f(_, k) {
//         int l, r; cind>>l>>r;
//         int curr = 0;
//         while(true) {
//             auto rit = upper_bound(all(b), curr+1);
//             if(rit == b.begin()) break;
//             int avail = sum(l, r, rit-b.begin()-1); // We can sum all values <= curr+1
//             if(avail <= curr) break;
//             curr = avail;
//         }
//         cout<<curr+1<<en;
//     }
// }