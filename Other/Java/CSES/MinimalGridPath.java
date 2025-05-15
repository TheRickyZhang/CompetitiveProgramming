import java.io.*;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

public class MinimalGridPath {
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
        int n = ni();
        String[] grid = new String[n];
        for(int i = 0; i < n; i++) {
            grid[i] = in.next();
        }
        pii[] dirs = {new pii(1, 0), new pii(0, 1)};
        boolean[][] vis = new boolean[n][n];
        Queue<pii> q = new ArrayDeque<>();
        q.add(new pii(0, 0));
        out.print(grid[0].charAt(0));
        for(int i = 0; i < 2*n - 2; i++) {
            char best = 'Z' + 1;
            List<pii> temp = new ArrayList<>();
            int sz = q.size();
            for(int j = 0; j < sz; j++) {
                pii u = q.remove();
                for(pii d : dirs) {
                    pii v = u.add(d);
                    int x = v.ff, y = v.ss;
                    if(x < n && y < n && !vis[x][y]) {
                        vis[x][y] = true;
                        char c = grid[x].charAt(y);
                        if(c < best) {
                            best = grid[x].charAt(y);
                            temp.clear();
                            temp.add(new pii(x, y));
                        } else if (c == best) {
                            temp.add(new pii(x, y));
                        }
                    }
                }
            }
            out.print(best);
            q.addAll(temp);
        }
        out.println();
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
