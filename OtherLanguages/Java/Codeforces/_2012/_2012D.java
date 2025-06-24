package Codeforces._2012;

import java.io.*;
import java.util.*;

public class _2012D {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st = new StringTokenizer("");
    static PrintWriter out = new PrintWriter(System.out);

    static int ni() throws IOException {
        while(!st.hasMoreTokens()) st = new StringTokenizer(br.readLine());
        return Integer.parseInt(st.nextToken());
    }

    static void swap(int[] a, int i, int j) {
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }

    static int cycleParity(int[] arr) {
        int m = arr.length;
        int[] tmp = Arrays.copyOf(arr, m);
        Arrays.sort(tmp);
        Map<Integer,Integer> rank = new HashMap<>();
        for(int i = 0; i < m; i++) rank.put(tmp[i], i);
        boolean[] vis = new boolean[m];
        int cycles = 0;
        for(int i = 0; i < m; i++) {
            if(!vis[i]) {
                cycles++;
                int j = i;
                while(!vis[j]) {
                    vis[j] = true;
                    j = rank.get(arr[j]);
                }
            }
        }
        return (m - cycles) & 1;
    }

    static void solve() throws IOException {
        int n = ni();
        int[] a = new int[(n+1)/2], b = new int[n/2];
        for(int i = 0; i < n; i++) {
            int x = ni(); x--;
            if((i & 1) == 0) a[i/2] = x;
            else b[i/2] = x;
        }
        int pA = cycleParity(a);
        int pB = cycleParity(b);
        int paritySum = pA ^ pB;
        Arrays.sort(a);
        Arrays.sort(b);
        if(paritySum == 1) {
            if((n & 1) == 1) {
                swap(a, a.length-1, a.length-2);
            } else {
                swap(b, b.length-2, b.length-1);
            }
        }
        for(int i = 0; i < n; i++) {
            if((i & 1) == 0) {
                out.print(a[i/2] + 1);
            } else {
                out.print(b[i/2] + 1);
            }
            out.print(" ");
        }
        out.println();
    }

    public static void main(String[] args) throws IOException {
        int T = ni();
        while(T-- > 0) solve();
        out.flush();
    }
}
