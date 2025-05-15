package Codeforces;

import java.io.*;

public class _1996A {
    static FastInput in = new FastInput();
    static PrintWriter out = new PrintWriter(System.out);
    public static void main(String[] args) throws IOException {
        int t = in.nextInt();
        while (t-- > 0) solve();
        out.flush();
    }
    static void solve() throws IOException {
        int x = in.nextInt();
        int f = x / 4;
        out.println(f + (x - f * 4) / 2);
    }
    static class FastInput {
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
        int nextInt() throws IOException {
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
