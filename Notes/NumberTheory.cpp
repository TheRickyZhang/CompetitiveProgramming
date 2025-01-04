Mod inverse:
fastPow(p, n-2) % mod

// Get all effective factors (largest prime * )
vi factorize(int m) {
    vb p(m + 1, true);
    p[0] = p[1] = false;
    for(int i=2; i*i<=m; ++i) {
        if(!p[i]) continue;
        for(int j=i*i; j <= m; j+=i) p[j] = false;
    }
    vi res;
    rep(i, 2, m+1) {
        if(!p[i]) continue;
        int x = i;
        while (x <= m / i) x *= i;
        res.pb(x);
    }
    return res;
}

// BIT OPERATIONS
// ORDER: (), << >>, &, ^, |, <>&&||, other

// Bit addition and multiplication
int add(int x, int y) {
    int xor_ = ~(x&y) & (x|y);
    return 2 * (x&y) + xor_;
}

int add(int a, int b) {
    while (b > 0) {
        int carry = a & b;
        a ^= b;
        b = carry << 1;
    }
    return a;
}

int multiply(int a, int b) {
    int res=0;
    while(b > 0) {
        if(b % 2) {
            res = add(res, a);
        }
        a<<=1; b>>=1;
    }
    return res;
}

// Find max AND
int maxAND(vi nums) {
    sort(rall(nums));
    int res=0;
    repr(i, 31, 0) {
        int temp = res | 1<<i;
        int cnt=0;
        for(int x : nums) {
            if((x&res)==res) {
                if(++cnt >= 2) {
                    break;
                }
            }
        }
        if(cnt < 2) return res;
        res = temp;
    }
    return res;
}

struct node {
    node* ch[2] = {nullptr, nullptr};
};
struct Trie {
    node* root;
    Trie() { root = new node(); }
    ~Trie() { delete root; }
    void insert(int x) {
        auto it=root;
        repr(i, k-1, 0) {
            int b=(x>>i)&1;
            if(!it->ch[b]) it->ch[b] = new node();
            it=it->ch[b];
        }
    }
    int minXor(int x) { // Calculates the closest values = greedy matching bits
        int closest = 0;
        auto it=root;
        repr(i, k-1, 0) {
            int b = (x>>i) & 1;
            if(it->ch[b]) {
                closest |= b<<i;
                it = it->ch[b];
            } else {
                closest |= (1-b)<<i;
                it = it->ch[1-b];
            }
        }
        return x ^ closest;
    }
};