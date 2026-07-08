#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    // Optimize standard input/output streams for fast performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long d;
    if (!(cin >> n >> d)) return 0;

    vector<long long> checkpoints(n);
    for (int i = 0; i < n; ++i) {
        cin >> checkpoints[i];
    }

    // Sort checkpoints in ascending order to process sequentially
    sort(checkpoints.begin(), checkpoints.end());

    // Greedy choice: always select the first checkpoint
    int count = 1;
    long long last_selected_pos = checkpoints[0];

    for (int i = 1; i < n; ++i) {
        // Check if the current checkpoint is at least D meters away from the last selected one
        if (checkpoints[i] - last_selected_pos >= d) {
            count++;
            last_selected_pos = checkpoints[i]; // Update the position tracking
        }
    }

    // Print the maximum number of checkpoints that can be selected
    cout << count << "\n";

    return 0;
}
