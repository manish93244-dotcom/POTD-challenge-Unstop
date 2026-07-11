#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;

    // Fast tracking array initialized to false (max value is 10^5)
    vector<bool> seen(100005, false);
    bool has_duplicate = false;

    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;

        // If we have already seen this value in the current test case
        if (seen[value]) {
            has_duplicate = true;
        }
        seen[value] = true;
    }

    if (has_duplicate) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    // Maximize standard input/output streaming efficiency
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        // Correctly loop through and process all independent test cases
        while (t--) {
            solve();
        }
    }

    return 0;
}
