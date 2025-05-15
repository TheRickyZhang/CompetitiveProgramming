import java.io.*;
import java.lang.reflect.Array;
import java.util.*;
import java.util.function.BiFunction;

public class MountainRange {
    public static final class pii {
        public int ff, ss;
        public pii(int a, int b) {
            this.ff = a;
            this.ss = b;
        }
    }
    static final long MOD  = 1000000007L;
    static final int INF   = 1000000000;
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
//    static void print(Object x){
//        if(x instanceof Iterable<?> it)
//            for(Object e: it) out.print(e+" ");
//        else if(x != null && x.getClass().isArray()){
//            int n = Array.getLength(x);
//            for(int i=0;i<n;i++) out.print(Array.get(x,i)+" ");
//        } else {
//            out.print(x);
//        }
//        out.println();
//    }

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

    public static void main(String[] args) throws IOException {
        int n = ni();
        int[] a = new int[n];
        for(int i = 0; i < n; i++) {
            a[i] = ni();
        }
        int[] l = new int[n], r = new int[n];
        Deque<pii> s = new ArrayDeque<>();
        for(int i = 0; i < n; i++) {
            while(!s.isEmpty() && s.getLast().ff < a[i]) {
                s.removeLast();
            }
            l[i] = (s.isEmpty() ? -1 : s.getLast().ss);
            s.addLast(new pii(a[i], i));
        }
        s.clear();
        for(int i = n-1; i >= 0; i--) {
            while(!s.isEmpty() && s.getLast().ff < a[i]) {
                s.removeLast();
            }
            r[i] = (s.isEmpty() ? n : s.getLast().ss);
            s.addLast(new pii(a[i], i));
        }
//        print(l);
//        print(r);

        int[] dp = new int[n];
        Arrays.fill(dp, 1);
        pii[] b = new pii[n];
        for(int i = 0; i < n; i++) {
            b[i] = new pii(a[i], i);
        }
        Arrays.sort(b, Comparator.comparingInt(x -> x.ff));
        Segtree<Integer> tree = new Segtree<>(n, Integer::max, 0);
        int res = 0;
        for(int i = 0; i < n; i++) {
            int x = b[i].ff, pos = b[i].ss;
            int mx = Math.max(tree.query(l[pos] + 1, pos-1), tree.query(pos+1, r[pos]-1));
            tree.update(pos, mx + 1);
            res = Math.max(res, mx + 1);
        }
        out.println(res);



        // I'm pretty sure this solves it correctly when going from LEFT to RIGHT (not both directions)
        // Wait this is just the same as the LDS algorithm... just with potential for more complexity with deletions, updates and such
//        NavigableMap<Integer, Integer> mp = new TreeMap<>();
//        Map<Integer, Integer> heights = new TreeMap<>();
//        int[] res = new int[n];
//        for(int i = 0; i < n; i++) {
//            Integer key = mp.higherKey(a[i]);
//            int h = (key == null ? 0 : mp.get(key)) + 1;
//            res[i] = h;
//            if (heights.containsKey(h) && heights.get(h) <= a[i]) {
//                mp.remove(heights.get(h));
//                mp.put(a[i], h);
//                heights.put(h, a[i]);
//            } else if (!heights.containsKey(h)) {
//                mp.put(a[i], h);
//                heights.put(h, a[i]);
//            }
//        }
//        print(res);
//        out.println(Arrays.stream(res).max().orElseThrow());
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
