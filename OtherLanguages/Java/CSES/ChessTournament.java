import java.io.*;
import java.util.*;
import java.util.function.BiFunction;

public class ChessTournament {
//    record Pair<T, U>(T ff, U ss) { }
    public static final class pii {
        public int ff, ss;
        public pii(int a, int b) {
            this.ff = a;
            this.ss = b;
        }
        public pii add(pii other) {
            return new pii(ff + other.ff, ss + other.ss);
        }
        @Override public String toString() { return ff + " " + ss; }
    }
    public static class Segtree<T> {
        int n;
        T[] t;
        T z;
        BiFunction<T, T, T> c; // Combine
        @SuppressWarnings("unchecked")
        public Segtree(int n, BiFunction<T, T, T> combine, T z) {
            this.n = n;
            this.c = combine;
            this.z = z;
            t = (T[]) new Object[4*n];
            Arrays.fill(t, z);
        }
        public void _update(int i, int l, int r, int pos, T x) {
            if(l == r) {
                t[i] = x;
            } else {
                int m = (l+r) / 2;
                if(pos <= m) {
                    _update(2*i, l, m, pos, x);
                } else {
                    _update(2*i+1, m+1, r, pos, x);
                }
                t[i] = c.apply(t[2*i], t[2*i+1]);
            }
        }
        public T _query(int i, int l, int r, int a, int b) {
            if(a > r || b < l) return z;
            if(a <= l && r <= b) {
                return t[i];
            }
            int m = (l + r) / 2;
            return c.apply(_query(2*i, l, m, a, b), _query(2*i+1, m+1, r, a, b));
        }
        public void update(int pos, T x) {
            _update(1, 0, n-1, pos, x);
        }
        public T query(int a, int b) {
            return _query(1, 0, n-1, a, b);
        }
    }
    public static class BIT {
        int n;
        long[] t;
        public BIT(int n) {
            this.n = n;
            this.t = new long[n+1];
        }
        void updateAdd(int pos, long x) {
            for(int i = pos + 1; i <= n; i += (i & -i)) {
                t[i] = add(t[i], x);
            }
        }
        long _query(int pos) {
            long res = 0;
            for(int i = pos+1; i > 0; i -= (i & -i)) {
                res = add(res, t[i]);
            }
            return res;
        }
        long query(int l, int r) {
            if(r < l) return 0;
            return (_query(r) - _query(l-1) + MOD) % MOD;
        }
    }

    static final long MOD  = 1000000007L;
    static final int  INF  = 1000000000;
    static final long INFL = 1_000_000_000_000_000_000L;
    static long add(long a, long b) {
        long res = a + b;
        return (res >= MOD ? res - MOD : res);
    }
    static long mult(long a, long b) {
        long res = a * b;
        return (res >= MOD ? res % MOD : res);
    }
    static long fpow(long x, long p) {
        long res = 1L;
        while(p > 0) {
            if(p % 2 == 1) {
                res = mult(res, x);
            }
            x = mult(x, x);
            p >>>= 1;
        }
        return res;
    }
    static void swap(int[] a, int i, int j) {
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }

    static FastInput in = new FastInput();
    static PrintWriter out = new PrintWriter(System.out);
    static int ni() throws IOException {
        return in.nextInt();
    }
    static long nl() throws IOException {
        return in.nextLong();
    }
    static <T> void print(Iterable<T> a) {
        for(T x : a) {
            out.print(x);
            out.print(" ");
        }
        out.println();
    }
    static void print(int[] a) {
        for(int x : a) {
            out.print(x);
            out.print(" ");
        }
        out.println();
    }

    /* ---------------------------- HERE ----------------------------- */
    public static void main(String[] args) throws IOException {
        int n = ni();
        List<pii> a = new ArrayList<>();
        for(int i = 0; i < n; i++) {
            int x = ni();
            a.add(new pii(x, i));
        }
        a.sort(Comparator.comparingInt((pii x) -> -x.ff));

        PriorityQueue<pii> pq = new PriorityQueue<>(
                Comparator.comparingInt((pii v) -> -v.ff)
        );
        for (pii v : a) {
            if (v.ff > 0) pq.add(v);
        }

        List<pii> res = new ArrayList<>();
        while (!pq.isEmpty()) {
            pii top = pq.poll();
            int d = top.ff;
            if (d > pq.size()) {
                out.println("IMPOSSIBLE");
                out.flush();
                return;
            }
            List<pii> temp = new ArrayList<>();
            for (int k = 0; k < d; k++) {
                pii nxt = pq.poll();
                res.add(new pii(top.ss, nxt.ss));
                nxt.ff--;
                if (nxt.ff < 0) {
                    out.println("IMPOSSIBLE");
                    out.flush();
                    return;
                }
                temp.add(nxt);
            }
            for (pii v2 : temp) {
                if (v2.ff > 0) pq.add(v2);
            }
        }

        out.println(res.size());
        for (pii e : res) { out.print(e.ff + 1);
            out.print(" "); out.println(e.ss + 1);
        } out.flush();
    } static void solve() throws IOException {

    }


}

