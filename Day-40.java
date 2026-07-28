import java.util.*;

class Solution {
    static class Pair {
        int node;
        int weight;

        Pair(int node, int weight) {
            this.node = node;
            this.weight = weight;
        }
    }

    public int shortestPath(int V, int src, int dest, int[][] edges) {
        // Build adjacency list
        List<List<Pair>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj.get(u).add(new Pair(v, w));
            adj.get(v).add(new Pair(u, w));
        }

        // Distance array initialized to infinity
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);

        // Min-Heap (PriorityQueue) storing {node, distance}
        PriorityQueue<Pair> pq = new PriorityQueue<>(Comparator.comparingInt(p -> p.weight));

        // Distance to src is 0
        dist[src] = 0;
        pq.add(new Pair(src, 0));

        while (!pq.isEmpty()) {
            Pair current = pq.poll();
            int u = current.node;
            int d = current.weight;

            // Early exit if we reached destination
            if (u == dest) {
                return d;
            }

            if (d > dist[u]) {
                continue;
            }

            for (Pair neighbor : adj.get(u)) {
                int v = neighbor.node;
                int w = neighbor.weight;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.add(new Pair(v, dist[v]));
                }
            }
        }

        return dist[dest] == Integer.MAX_VALUE ? -1 : dist[dest];
    }
}