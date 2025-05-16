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

template<typename T>
struct PersSegtree {
    struct Node {
        T v;
        Node *l, *r;
        explicit Node(T _v=0, Node* _l=nullptr, Node* _r=nullptr)
          : v(_v), l(_l), r(_r) {}
    };
    int n;
    function<T(T, T)> c;
    // Note that we should maintain our list of roots OUTSIDE the class since this is only responsible for creating/returning these nodes
    // Usage: set roots[0] = build(0, n-1) ... and then call add/update along the secondary dimension (ex. t[i] = add(t[i-1], pos, x);)
    PersSegtree(int n, function<T(T, T)> c) : n(n), c(std::move(c)) {}
    Node* build(int l, int r) {
        if(l == r) return new Node();
        int m = (l+r)/2;
        Node* nl = build(l, m), *nr = build(m+1, r);
        return new Node(c(nl->v, nr->v), nl, nr);
    }
    // Note that we always RETURN a new node
    Node* _modify(Node* i, int l, int r, int pos, T x, bool upd) {
        if(l == r) {
            return (upd ? new Node(x) : new Node(c(i->v, x)));
        }
        int m = (l+r)/2;
        if(pos <= m) {
            Node* nl = _modify(i->l, l, m, pos, x, upd);
            return new Node(c(nl->v, i->r ->v), nl, i->r);
        } else {
            Node* nr = _modify(i->r, m+1, r, pos, x, upd);
            return new Node(c(nr->v, i->l->v), i->l, nr);
        }
    }
    Node* update(Node* i, int pos, T x) {
        return _modify(i, 0, n-1, pos, x, true);
    }
    Node* add(Node* i, int pos, T x) {
        return _modify(i, 0, n-1, pos, x, false);
    }
    T _query(Node* i, int l, int r, int a, int b) {
        if(l > r || b < l || a > r) return T();
        if(a <= l && r <= b) return i->v;
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