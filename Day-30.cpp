#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    // Optimize standard input/output streaming operations for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C;
    if (cin >> R >> C) {
        // Process row by row to save space and display the output directly
        for (int i = 0; i < R; ++i) {
            vector<int> row(C);
            for (int j = 0; j < C; ++j) {
                cin >> row[j];
            }
            
            // Reverse the elements horizontally within the current row
            reverse(row.begin(), row.end());
            
            // Print the mirrored row
            for (int j = 0; j < C; ++j) {
                cout << row[j] << (j == C - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }
    
    return 0;
}


