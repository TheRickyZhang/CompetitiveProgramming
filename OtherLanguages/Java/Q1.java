import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Q1 {
    static class FastReader {
        BufferedReader b;
        StringTokenizer s; 

        public FastReader() {
            b = new BufferedReader(new InputStreamReader(System.in));
        }
        String next() {
            while (s == null || !s.hasMoreElements()) {
                try {
                    s = new StringTokenizer(b.readLine());
                } catch (IOException e) {
                    e.printStackTrace(); 
                }
            }
            return s.nextToken();
        }
        int nextInt() { 
            return Integer.parseInt(next()); 
        }
        long nextLong() { 
            return Long.parseLong(next()); 
        }
        double nextDouble() { 
            return Double.parseDouble(next()); 
        }
        String nextLine() {
            String str = "";
            try {
                if (s.hasMoreTokens()) {
                    str = s.nextToken("\n");
                } else {
                    str = b.readLine();
                }
            } catch (IOException e) {
                e.printStackTrace(); 
            }
            return str;
        }
    }
    public static void main(String[] args) {
        FastReader scanner = new FastReader();
        int n = scanner.nextInt();
        TreeMap<Integer, ArrayList<Integer>> edges = new TreeMap<>();
        double result = 0;
        for (int i = 0; i < n-1; i++) {
            int start = scanner.nextInt();
            int end = scanner.nextInt();
            if (edges.containsKey(start)) {
                ArrayList<Integer> modEdges = edges.get(start);
                modEdges.add(end);
                edges.put(start, modEdges);
            } else {
                ArrayList<Integer> edgeList = new ArrayList<>();
                edgeList.add(end);
                edges.put(start, edgeList);
            }
            
        }
        for (Map.Entry<Integer, ArrayList<Integer>> edge : edges.entrySet()) {
            // System.out.println("Key: " + edge.getKey());
            for (int val : edge.getValue()) {
                // System.out.print(" " + val);
            }
            // System.out.println("");
        }
        // map to store edges
        // bfs but track probabilites and layers
        ArrayDeque<Integer> q = new ArrayDeque<>();
        q.add(1);
        q.add(0);
        double prob = 1;
        double len = 0;
        TreeSet<Integer> seen = new TreeSet<>();
        // System.out.println("front of q is: " + q.peek());

        while (q.isEmpty() == false) {
            ArrayList<Integer> valid = new ArrayList<>();
            int start = q.peek();
            // System.out.println("Runnig on "+ start);
            q.remove();
            if (start == 0) {
                q.add(0);
                if (q.peek() == 0) {
                    break;
                }
                len++;
                continue;
            }
            if (edges.containsKey(start) == false) {
                result += (prob * len);
                // System.out.println((prob*len) + "added to result fromm key" + start);
                continue;
            }
            
            for (int end : edges.get(start)) {
                if (!seen.contains(end)) {
                    valid.add(end);
                }
            }
            seen.add(start);
            if (valid.size() == 0) {
                result += (prob * len);
            } else {
                prob /= (valid.size());
                for (int i = 0; i < valid.size(); i++) {
                    q.add(valid.get(i));
                }
            }
        }
        System.out.print(String.format("%.15f", result));
    }
}
