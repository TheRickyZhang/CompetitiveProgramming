package Codeforces._2012;

import java.io.*;
import java.util.TreeSet;

public class _2012E {
    record Pair<T, U>(T ff, U ss) { }
    record pii<T extends Number>(T ff, T ss){ }
    static int lower_bound(int[] arr, int l, int r, int x) { // Note that just like C++, the upper bound is exclusive!
        while(l < r) {
            int m = (l + r) >>> 1;
            if(arr[m] < x) l = m+1;
            else r = m;
        }
        return l;
    }
    static int upper_bound(int[] arr, int l, int r, int x) {
        while(l < r) {
            int m = (l + r) >>> 1;
            if(arr[m] <= x) l = m+1;
            else r = m;
        }
        return l;
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
        int[] a = new int[n]; // Note we are using 1-indexed for ease of use
        for(int i = 0; i < n; i++) {
            a[i] = ni(); a[i]--;
        }
        int[] l = new int[n], r = new int[n];
        TreeSet<Integer> s = new TreeSet<>();
        for(int i = 0; i < n; i++) {
            s.add(i);
        }
        for(int i = 0; i < n; i++){
            Integer it = s.floor(a[i]); // Equivalent to leq_bound
            if(it != null) s.remove(it);
            l[i] = n - s.size();
        }

        s = new TreeSet<>();
        for(int i = 0; i < n; i++) {
            s.add(i);
        }
        for(int i = n-1; i >= 0; i--) {
            Integer it = s.floor(a[i]);
            if(it != null) s.remove(it);
            r[i] = n - s.size();
        }
        long res = 0;
        for(int i = 0; i < n-1; i++) {
            res += Math.min(l[i], r[i + 1]);
        }
        out.println(res);
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
