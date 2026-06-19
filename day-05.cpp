#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<long long> cost(N + 1);

    for (int i = 1; i <= N; i++) {
        string s;
        cin >> s;

        long long val = 0;
        for (char c : s) {
            val += (c - 'a' + 1);
        }
        cost[i] = val;
    }

    vector<vector<pair<int,int>>> adj(N + 1);

    for (int i = 0; i < M; i++) {
        int u, v, t;
        cin >> u >> v >> t;

        adj[u].push_back({v, t});
        adj[v].push_back({u, t});
    }

    int start, end;
    cin >> start >> end;

    const long long INF = 1e18;

    vector<long long> dist(N + 1, INF);

    priority_queue<
        pair<long long,int>,
        vector<pair<long long,int>>,
        greater<pair<long long,int>>
    > pq;

    dist[start] = cost[start];
    pq.push({dist[start], start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u])
            continue;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            long long w = edge.second;

            long long nd = d + w + cost[v];

            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    cout << (dist[end] == INF ? -1 : dist[end]) << '\n';

    return 0;
}