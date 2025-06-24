import java.io.*;
import java.util.HashMap;

public class DistinctValuesSubsequences {
    static final long MOD = 1000000007L;
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

    public static void main(String[] args) throws IOException {
        int n = ni();
        int[] a = new int[n];
        for(int i = 0; i < n; i++) {
            a[i] = ni();
        }
        long curr = 1; // Unique count
        long res = 0;
        HashMap<Integer, Integer> mp = new HashMap<>();
        for(int i = 0; i < n; i++) {
            int x = mp.getOrDefault(a[i], 0);
            res = add(res, mult(curr, fpow(x + 1, MOD-2)));
            mp.put(a[i], x + 1);
            curr = mult(mult(curr, x + 2), fpow(x + 1, MOD-2));
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
