#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    // Optimize standard input/output streams for fast performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    unordered_map<int, int> frequency_map;
    int max_freq = 0;
    int best_id = 0;

    for (int i = 0; i < n; ++i) {
        int visitor_id;
        cin >> visitor_id;
        
        // Increment frequency for the parsed Visitor ID
        frequency_map[visitor_id]++;
        int current_freq = frequency_map[visitor_id];

        // Evaluate the maximum frequency tracking criteria
        if (current_freq > max_freq) {
            max_freq = current_freq;
            best_id = visitor_id;
        } 
        // Handle ties by picking the smaller Visitor ID value
        else if (current_freq == max_freq) {
            if (visitor_id < best_id) {
                best_id = visitor_id;
            }
        }
    }

    // Print the result separated by a space as specified by output format rules
    cout << best_id << " " << max_freq << "\n";

    return 0;
}