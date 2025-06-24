import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class LongestCommonSubsequene {
    public static final class pii {
        public int ff, ss;
        public pii(int a, int b) {
            this.ff = a;
            this.ss = b;
        }
        public int ff() { return ff; }
        public int ss() { return ss; }
    }
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
    static <T> void print(Iterable<T> a) {
        for(T x : a) {
            out.print(x);
            out.print(" ");
        }
        out.println();
    }

    public static void main(String[] args) throws IOException {
        int n = ni(), m = ni();
        int[][] dp = new int[n+1][m+1];
        byte[][] prev = new byte[n+1][m+1];
        int[] a = new int[n];
        int[] b = new int[m];
        for(int i = 0; i < n; i++) {
            a[i] = ni();
        }
        for(int i = 0; i < m; i++) {
            b[i] = ni();
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i] == b[j]) {
                    prev[i+1][j+1] = 2;
                    dp[i+1][j+1] = dp[i][j] +1;
                } else {
                    if(dp[i][j+1] > dp[i+1][j]) {
                        prev[i+1][j+1] = 0;
                        dp[i+1][j+1] = dp[i][j+1];
                    } else {
                        prev[i+1][j+1] = 1;
                        dp[i+1][j+1] = dp[i+1][j];
                    }
                }
            }
        }
//        out.println(dp[n][m]);
        List<Integer> res = new ArrayList<>();
        int x = n, y = m;
        while (x != 0 && y != 0) {
            int dir = prev[x][y];
            if (dir == 2) {
                res.add(a[x-1]);
                x--; y--;
            }
            else if (dir == 0) {
                x--;
            }
            else {
                y--;
            }
        }
        Collections.reverse(res);
        out.println(res.size());
        print(res);
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
