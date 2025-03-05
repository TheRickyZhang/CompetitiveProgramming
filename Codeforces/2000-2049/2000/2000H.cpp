#include <bits/stdc++.h>
using namespace std;

#define int long long
#define f(i, n) for (int i = 0; i < (n); ++i)

const int MOD = 1000000007, INF = 1000000009;

// Treap node for free segment [L, R) with length = R-L.
struct Node {
    pair<int,int> key; // {len, L}
    int prior, minL;
    Node *l, *r;
    Node(int L, int R): key({R-L, L}), prior((int) (rand()<<16 ^ rand())), minL(L), l(nullptr), r(nullptr){}
};

int mn(Node* t){return t?t->minL:INF;}
void upd(Node* t){ if(t){ t->minL = min(t->key.second, min(mn(t->l), mn(t->r))); } }

// Splits treap t into [<= x] and (> x) by key.
pair<Node*,Node*> split(Node* t, pair<int,int> x) {
    if(!t)return {nullptr,nullptr};
    if(t->key < x){
        auto p = split(t->r, x);
        t->r = p.first; upd(t);
        return {t, p.second};
    } else {
        auto p = split(t->l, x);
        t->l = p.second; upd(t);
        return {p.first, t};
    }
}

Node* merge(Node* a, Node* b){
    if(!a || !b)return a?a:b;
    if(a->prior > b->prior){
        a->r = merge(a->r, b); upd(a); return a;
    } else {
        b->l = merge(a, b->l); upd(b); return b;
    }
}

Node* rootTreap = nullptr;

void add_seg(int L, int R){
    if(L >= R)return;
    Node* t = new Node(L, R);
    auto p = split(rootTreap, {R-L, L});
    rootTreap = merge(merge(p.first, t), p.second);
}

void rem_seg(int L, int R){
    if(L>=R)return;
    // Remove node with key {R-L, L} from treap.
    function<void(Node*&, pair<int,int>)> rem=[&](Node*& t, pair<int,int> key){
        if(!t)return;
        if(t->key==key) { t = merge(t->l,t->r); return; }
        if(t->key < key) rem(t->r,key); else rem(t->l,key);
        upd(t);
    };
    rem(rootTreap,{R-L,L});
}

set<int> S;

void add_val(int x){
    auto it = S.lower_bound(x);
    int L = (it==S.begin()? 0 : *prev(it)), R = (it==S.end()? INF : *it);
    rem_seg(L+1,R);
    add_seg(L+1,x);
    if(R!=INF) add_seg(x+1,R);
    S.insert(x);
}

void rem_val(int x){
    auto it = S.lower_bound(x);
    int L = (it==S.begin()? 0 : *prev(it)), R = (next(it)==S.end()? INF : *next(it));
    rem_seg(L+1,x); rem_seg(x+1,R);
    if(R!=INF) add_seg(L+1,R);
    S.erase(x);
}

int query(int k){
    // Split treap into segments with length < k and >= k.
    auto p = split(rootTreap, {k, -1});
    int ans = INF;
    if(p.second) ans = p.second->minL;
    // Answer is min(last element in S + 1, ans)
    int last = S.empty()? 0 : *S.rbegin();
    ans = min(last+1, ans);
    rootTreap = merge(p.first, p.second);
    return ans;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        S.clear(); rootTreap = nullptr;
        int x;
        vector<int> init(n);
        f(i,n) { cin >> init[i]; S.insert(init[i]); }
        // Build free segments from initial S.
        auto it = S.begin();
        if(*it>1) add_seg(1,*it);
        for(auto jt = it; jt!=S.end(); jt++){
            auto nt = next(jt);
            if(nt!=S.end() && *jt+1 < *nt) add_seg(*jt+1,*nt);
        }
        add_seg(*S.rbegin()+1, INF);

        int m; cin >> m;
        while(m--){
            char op; cin >> op;
            if(op=='+'){
                cin >> x;
                add_val(x);
            } else if(op=='-'){
                cin >> x;
                rem_val(x);
            } else {
                int k; cin >> k;
                cout << query(k) << " ";
            }
        }
        cout<<"\n";
    }
    return 0;
}
