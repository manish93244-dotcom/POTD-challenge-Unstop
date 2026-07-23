#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define INF 1e18

long long min(long long a, long long b) {
    return (a < b) ? a : b;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int total_locations = N + 1;
    long long dist[17][17];

    for (int i = 0; i < total_locations; i++) {
        for (int j = 0; j < total_locations; j++) {
            scanf("%lld", &dist[i][j]);
        }
    }

    int num_masks = 1 << N;
    // dp[mask][u] stores the min cost to visit the set 'mask' ending at location 'u'
    // mask represents relays 1..N (bit k corresponding to relay k+1)
    long long dp[1 << 16][17];

    for (int mask = 0; mask < num_masks; mask++) {
        for (int u = 0; u <= N; u++) {
            dp[mask][u] = INF;
        }
    }

    // Base case: at Central Dock (0) with no relays visited
    dp[0][0] = 0;

    for (int mask = 0; mask < num_masks; mask++) {
        for (int u = 0; u <= N; u++) {
            if (dp[mask][u] == INF) continue;

            // Try to visit an unvisited relay v (1-indexed)
            for (int v = 1; v <= N; v++) {
                int bit = v - 1;
                if (!(mask & (1 << bit))) {
                    int next_mask = mask | (1 << bit);
                    dp[next_mask][v] = min(dp[next_mask][v], dp[mask][u] + dist[u][v]);
                }
            }
        }
    }

    // Return to Central Dock (0) from the last activated relay
    long long min_total_energy = INF;
    int full_mask = num_masks - 1;

    for (int u = 1; u <= N; u++) {
        if (dp[full_mask][u] != INF) {
            min_total_energy = min(min_total_energy, dp[full_mask][u] + dist[u][0]);
        }
    }

    printf("%lld\n", min_total_energy);

    return 0;
}