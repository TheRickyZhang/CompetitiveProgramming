package Codeforces._2012;

import java.io.*;

public class _2012C {
    record Pair<T, U>(T ff, U ss) { }
    record pii<T extends Number>(T ff, T ss){ }
    static boolean check(int x, int y, int n, int m) {
        return x >= 0 && x < n && y >= 0 && y < m;
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
        int t = in.nextInt();
        for(int i = 0; i < t; i++) {
            solve();
        }
        out.flush();
    }
    static void solve() throws IOException {
        int n = ni();
        int[][] res = new int[n][n];

        int[] dx = {0, 1, 0, -1}, dy = {1, 0, -1, 0};
        int d = 0, steps = 1, it = 0;
        int x = (n-1) / 2, y = (n-1)/2;
        res[x][y] = it++;
        while(it < n*n) {
            for(int j = 0; j < 2; j++) {
                for(int i = 0; i < steps; i++) {
                    x += dx[d];
                    y += dy[d];
                    if(check(x, y, n, n) && it < n*n) {
                        res[x][y]=it++;
                    }
                }
                d = (d + 1) % 4;
            }
            steps++;
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                out.print(res[i][j]);
                out.print(" ");
            }
            out.println();
        }
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
