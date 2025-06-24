import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.BiFunction;

public class PermutationPrimeSums {
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

    /* ---------------------------- here ----------------------------- */
    public static void main(String[] args) throws IOException{
        int n = ni();
        // sievelist
        boolean[] pr = new boolean[2*n+1];
        List<Integer> primes = new ArrayList<>();
        Arrays.fill(pr, true);
        pr[0] = false;
        pr[1] = false;
        for(int i = 2; i <= 2*n; i++) {
            if(!pr[i]) continue;
            primes.add(i);
            for(int j = 2*i; j <= 2*n; j += i) {
                pr[j] = false;
            }
        }
        int m = primes.size();

        int it = m-1; // This is the primes.size();
        int[] a = new int[n];
        int[] b = new int[n];
        int pos = 0;

        int curr = n;
        while(pos < n) {
            // Find the lowest prime > curr
            while(it > 0 && primes.get(it-1) > curr) {
                it--;
            }
            int p = primes.get(it);
            for(int i = p - curr; i <= curr; i++) {
                a[pos] = i;
                b[pos] = p - i;
                pos++;
            }
            curr = p-curr-1;
        }
        print(a);
        print(b);
        out.flush();
    }
    static void solve() throws IOException {

    }


    public static class FastInput {
        final byte[] buf = new byte[1<<16];
        int ptr, len;
        int read() throws IOException {
            if (ptr >= len) {
                ptr = 0;
                len = System.in.read(buf);
                if (len < 0) return -1;
            }
            return buf[ptr++];
        }
        public int nextInt() throws IOException {
            int c, x = 0;
            for (c = read(); c <= ' '; c = read());
            boolean neg = c == '-';
            if (neg) c = read();
            for (; c >= '0' && c <= '9'; c = read()) x = x*10 + (c - '0');
            return neg ? -x : x;
        }
        long nextLong() throws IOException {
            int c; long x = 0;
            for (c = read(); c <= ' '; c = read());
            boolean neg = c == '-';
            if (neg) c = read();
            for (; c >= '0' && c <= '9'; c = read()) x = x*10 + (c - '0');
            return neg ? -x : x;
        }
        String next() throws IOException {
            int c; StringBuilder sb = new StringBuilder();
            for (c = read(); c <= ' '; c = read());
            for (; c > ' '; c = read()) sb.append((char)c);
            return sb.toString();
        }
    }
}
