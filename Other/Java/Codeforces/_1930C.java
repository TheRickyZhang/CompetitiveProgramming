package Codeforces;

import java.io.BufferedReader;
import java.util.*;
import java.io.*;

public class _1930C {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st = new StringTokenizer("");
    static PrintWriter out = new PrintWriter(System.out);
    static String next() throws IOException {
        while(!st.hasMoreElements()) st = new StringTokenizer(br.readLine());
        return st.nextToken();
    }
    static int ni() throws IOException {
        return Integer.parseInt(next());
    }
    static long nl() throws IOException {
        return Long.parseLong(next());
    }

    record Pair<A, B>(A ff, B ss) { }

    static int n, m;
    static ArrayList<ArrayList<Integer>> adj;
    static ArrayList<Pair<Integer, Integer>> a, b;
    static int[] col;
    static boolean dfs(int u, int p, int c) {
        col[u] = c;
        for(int v : adj.get(u)) {
            if(v == p) continue;
            if(col[v] == col[u]) return false;
            if(col[v] == -1) {
                if(!dfs(v, u, 1-c)) {
                    return false;
                }
            }
        }
        return true;
    }
    static ArrayList<ArrayList<Integer>> nadj;
    static int[] in;


    public static void main(String[] args) throws Exception {
        n = ni();
        m = ni();
        adj = new ArrayList<>(n);
        for(int i = 0; i < n; ++i) {
            adj.add(new ArrayList<>());
        }
        a = new ArrayList<>();
        b = new ArrayList<>();
        for(int i = 0; i < m; i++){
            int t = ni(), u = ni(), v = ni();
            u--; v--;
            adj.get(u).add(v);
            adj.get(v).add(u);
            if(t == 1) {
                a.add(new Pair<>(u, v));
            } else {
                b.add(new Pair<>(u, v));
            }
        }
        col = new int[n];
        Arrays.fill(col, -1);
        for(int i = 0; i < n; i++) {
            if(col[i] == -1 && !dfs(i, -1, 0)) {
                out.println("No");
                out.close();
                return;
            }
        }

        nadj = new ArrayList<>(n);
        for(int i = 0; i < n; i++){
            nadj.add(new ArrayList<>());
        }
        in = new int[n];
        Arrays.fill(in, 0);
        for(Pair<Integer, Integer> p : a) {
            int u = p.ff(), v = p.ss();
            if(col[u] != 0) {
                int temp = v;
                v = u;
                u = temp;
            }
            nadj.get(u).add(v);
            in[v]++;
        }
        for(Pair<Integer, Integer> p : b){
            int u = p.ff(), v = p.ss();
            if(col[u] != 0) {
                int temp = v;
                v = u;
                u = temp;
            }
            nadj.get(v).add(u);
            in[u]++;
        }
        Queue<Integer> q = new ArrayDeque<Integer>();
        for(int i = 0; i < n; i++) {
            if(in[i] == 0) q.add(i);
        }
        int it = 0;
        int[] res = new int[n];
        while(!q.isEmpty()) {
            int u = q.remove();
            res[u] = it++;
            for(int v : nadj.get(u)) {
                if(--in[v] == 0) {
                    q.add(v);
                }
            }
        }
        if(it != n) {
            out.println("NO");
            out.close();
            return;
        }
        out.println("YES");
        for(int i = 0; i < n; i++) {
            out.print(col[i] == 0 ? 'L' : 'R');
            out.print(" ");
            out.println(res[i]);
        }
        out.close();
    }
}
