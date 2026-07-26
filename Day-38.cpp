#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Structure to hold offline queries
struct Query {
    int id;
    int l, r;
    int block;

    bool operator<(const Query& other) const {
        if (block != other.block) {
            return block < other.block;
        }
        // Hilbert curve / Zig-zag optimization for speed
        return (block & 1) ? (r < other.r) : (r > other.r);
    }
};

const int MAXA = 1000005;
const int MAXN = 200005;

long long freq[MAXA];
long long current_energy = 0;

inline void add(int x) {
    long long f = freq[x];
    current_energy += (2 * f + 1); // equivalent to (f+1)^2 - f^2
    freq[x]++;
}

inline void remove(int x) {
    long long f = freq[x];
    current_energy -= (2 * f - 1); // equivalent to f^2 - (f-1)^2
    freq[x]--;
}

int main() {
    // Optimize standard I/O streaming operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int block_size = max(1, (int)(n / sqrt(q)));

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
        queries[i].block = queries[i].l / block_size;
    }

    sort(queries.begin(), queries.end());

    vector<long long> ans(q);
    int cur_l = 1, cur_r = 0;

    for (int i = 0; i < q; ++i) {
        int L = queries[i].l;
        int R = queries[i].r;

        while (cur_r < R) {
            cur_r++;
            add(a[cur_r]);
        }
        while (cur_r > R) {
            remove(a[cur_r]);
            cur_r--;
        }
        while (cur_l < L) {
            remove(a[cur_l]);
            cur_l++;
        }
        while (cur_l > L) {
            cur_l--;
            add(a[cur_l]);
        }

        ans[queries[i].id] = current_energy;
    }

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}