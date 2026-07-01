#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int minUnassignedShifts(int n, int m, const vector<int>& doctorSpecs, const vector<int>& shiftReqs) {
    // Hash maps to store the frequency of each specialization
    unordered_map<int, int> doctorCount;
    unordered_map<int, int> shiftCount;

    // State-First Frequency Collection: Count available doctors per specialization
    for (int i = 0; i < n; ++i) {
        doctorCount[doctorSpecs[i]]++;
    }

    // Count required shifts per specialization
    for (int i = 0; i < m; ++i) {
        shiftCount[shiftReqs[i]]++;
    }

    int fulfilledShifts = 0;

    // Process every unique specialization requested by the shifts
    for (const auto& pair : shiftCount) {
        int spec = pair.first;
        int required = pair.second;

        // If doctors with this specialization exist, match as many as possible
        if (doctorCount.count(spec)) {
            fulfilledShifts += min(doctorCount[spec], required);
        }
    }

    // Minimum unassigned shifts is total shifts minus successfully covered shifts
    return m - fulfilledShifts;
}

int main() {
    // Optimize standard I/O streaming operations for competitive programming speeds
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0; // Guard against empty or corrupted streams
    
    vector<int> doctorSpecs(n);
    vector<int> shiftReqs(m);

    for (int i = 0; i < n; ++i) {
        cin >> doctorSpecs[i]; 
    }

    for (int i = 0; i < m; ++i) {
        cin >> shiftReqs[i]; 
    }

    // Call the user logic function and print the result
    int result = minUnassignedShifts(n, m, doctorSpecs, shiftReqs);
    cout << result << "\n";

    return 0;
} 
