#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void dfs1(int node, const vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs1(neighbor, adj, visited, st);
        }
    }
    st.push(node);
}

void dfs2(int node, const vector<vector<int>>& adjT, vector<bool>& visited, int comp_id, vector<int>& component) {
    visited[node] = true;
    component[node] = comp_id;
    for (int neighbor : adjT[node]) {
        if (!visited[neighbor]) {
            dfs2(neighbor, adjT, visited, comp_id, component);
        }
    }
}

int main() {
    // Optimize standard input/output streams for fast performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    vector<vector<int>> adjT(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adjT[v].push_back(u); // Transposed graph for Kosaraju's second pass
    }

    // Pass 1: Order nodes by their finishing times
    stack<int> st;
    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs1(i, adj, visited, st);
        }
    }

    // Pass 2: Extract strongly connected components
    fill(visited.begin(), visited.end(), false);
    vector<int> component(n + 1, -1);
    int comp_id = 0;

    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (!visited[node]) {
            dfs2(node, adjT, visited, comp_id, component);
            comp_id++;
        }
    }

    // Step 3: Compute the in-degree of each condensed component macro-node
    vector<int> in_degree(comp_id, 0);
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            if (component[u] != component[v]) {
                in_degree[component[v]]++;
            }
        }
    }

    // Step 4: Count how many components have no incoming edges
    int initial_announcers = 0;
    for (int i = 0; i < comp_id; ++i) {
        if (in_degree[i] == 0) {
            initial_announcers++;
        }
    }

    cout << initial_announcers << "\n";

    return 0;
}