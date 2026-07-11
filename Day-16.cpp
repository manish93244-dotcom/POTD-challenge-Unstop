#include <iostream>
#include <vector>
#include <queue>

// Define a constant for infinity that fits comfortably inside a 64-bit integer
const long long INF = 1e18;

void find_shortest_distances(int n, int m, const std::vector<std::vector<int>>& connections) {
    // Build an adjacency list where adj[u] stores pairs of {neighbor, weight}
    std::vector<std::vector<std::pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u = connections[i][0];
        int v = connections[i][1];
        int w = connections[i][2];
        adj[u].push_back({v, w});
    }

    // Distance vector initialized to infinity
    std::vector<long long> dist(n + 1, INF);
    
    // Min-priority queue storing pairs of {distance, node}
    std::priority_queue<std::pair<long long, int>, 
                        std::vector<std::pair<long long, int>>, 
                        std::greater<std::pair<long long, int>>> pq;

    // State-First Initialization: starting point is node 1 with a distance of 0
    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();

        // Skip stale states if a shorter path to u has already been processed
        if (current_dist > dist[u]) {
            continue;
        }

        // Relax neighbors
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print space-separated shortest distances from node 1 to each pickup point
    for (int i = 1; i <= n; ++i) {
        std::cout << dist[i] << (i == n ? "" : " ");
    }
    std::cout << "\n";
}

int main() {
    // Optimize standard input/output channels for high-performance execution
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    if (!(std::cin >> n >> m)) return 0;

    std::vector<std::vector<int>> connections(m, std::vector<int>(3));
    for (int i = 0; i < m; ++i) {
        std::cin >> connections[i][0] >> connections[i][1] >> connections[i][2];
    }

    find_shortest_distances(n, m, connections);

    return 0;
}
