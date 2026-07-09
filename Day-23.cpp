#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    // Optimize standard input/output streams for fast performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Build the adjacency list representation of the road network
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // BFS initialization: track distances and visited states
    vector<int> dist(n + 1, -1);
    queue<int> q;

    // Start traversal from the capital (City 1)
    q.push(1);
    dist[1] = 0;

    int max_distance = 0;

    while (!q.empty()) {
        int current_city = q.front();
        q.pop();

        // Update the maximum distance encountered so far
        max_distance = max(max_distance, dist[current_city]);

        for (int neighbor : adj[current_city]) {
            // If the neighbor city hasn't been visited yet
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[current_city] + 1;
                q.push(neighbor);
            }
        }
    }

    // Print the maximum number of roads traveled to reach the farthest city
    cout << max_distance << "\n";

    return 0;
}
