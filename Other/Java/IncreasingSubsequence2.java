import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class IncreasingSubsequence2 {
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


    public static void main(String[] args) throws IOException {
        int n = ni();
        int[] a = new int[n];
        for(int i = 0; i<n; i++) {
            a[i] = ni();
        }
        Set<Integer> s = Arrays.stream(a).boxed().collect(Collectors.toCollection(TreeSet::new));
        Map<Integer, Integer> mp = new HashMap<>();
        int it = 0;
        for(int x : s) {
            mp.put(x, it++);
        }
        for(int i = 0; i < n; i++) {
            a[i] = mp.get(a[i]);
        }
//        print(a);
        long res = 0;
        BIT b = new BIT(mp.size());
        for(int i = 0; i < n; i++) {
            long tot = add(b.query(0, a[i]-1), 1);
            res = add(res, tot);
            b.updateAdd(a[i], tot);
        }
        out.println(res);
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
