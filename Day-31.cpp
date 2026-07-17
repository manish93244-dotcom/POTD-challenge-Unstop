#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    // Maximize standard input/output streaming operations for high speed execution
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> p(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> p[i];
    }

    // dp[i][j] will store the minimum cost to chain frames from i to j (1-indexed)
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));

    // L is the chain length
    for (int L = 2; L <= n; ++L) {
        for (int i = 1; i <= n - L + 1; ++i) {
            int j = i + L - 1;
            dp[i][j] = 1e18; // Initialize with a large value representing infinity

            // Try all possible split points between i and j-1
            for (int k = i; k < j; ++k) {
                long long cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    // The result for the full chain from frame 1 to frame n
    cout << dp[1][n] << "\n";

    return 0;
}