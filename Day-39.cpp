#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    // Fast I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (cin >> s) {
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());

        if (s == rev_s) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}