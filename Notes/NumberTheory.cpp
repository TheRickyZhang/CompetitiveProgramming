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