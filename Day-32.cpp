#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    long long sum;
    int max_val;
    int sec_val;
    int max_cnt;
};

const int MAXN = 200005;
Node tree[4 * MAXN];
int arr[MAXN];

// Merge two child nodes to compute parent statistics
void merge(int node) {
    int left = 2 * node;
    int right = 2 * node + 1;
    
    tree[node].sum = tree[left].sum + tree[right].sum;
    
    if (tree[left].max_val == tree[right].max_val) {
        tree[node].max_val = tree[left].max_val;
        tree[node].max_cnt = tree[left].max_cnt + tree[right].max_cnt;
        tree[node].sec_val = max(tree[left].sec_val, tree[right].sec_val);
    } else if (tree[left].max_val > tree[right].max_val) {
        tree[node].max_val = tree[left].max_val;
        tree[node].max_cnt = tree[left].max_cnt;
        tree[node].sec_val = max(tree[left].sec_val, tree[right].max_val);
    } else {
        tree[node].max_val = tree[right].max_val;
        tree[node].max_cnt = tree[right].max_cnt;
        tree[node].sec_val = max(tree[left].max_val, tree[right].sec_val);
    }
}

// Helper to apply the modification directly onto a node
void put_tag(int node, int v) {
    if (tree[node].max_val <= v) return;
    tree[node].sum -= (long long)tree[node].max_cnt * (tree[node].max_val - v);
    tree[node].max_val = v;
}

// Push down lazy modifications to child nodes
void push_down(int node) {
    put_tag(2 * node, tree[node].max_val);
    put_tag(2 * node + 1, tree[node].max_val);
}

// Build the segment tree initially
void build(int node, int start, int end) {
    if (start == end) {
        tree[node].sum = arr[start];
        tree[node].max_val = arr[start];
        tree[node].sec_val = -1;
        tree[node].max_cnt = 1;
        return;
    }
    int mid = start + (end - start) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    merge(node);
}

// Range chmin (Ceiling Command)
void update_min(int node, int start, int end, int l, int r, int v) {
    if (start > r || end < l || tree[node].max_val <= v) {
        return;
    }
    if (start >= l && end <= r && tree[node].sec_val < v) {
        put_tag(node, v);
        return;
    }
    push_down(node);
    int mid = start + (end - start) / 2;
    update_min(2 * node, start, mid, l, r, v);
    update_min(2 * node + 1, mid + 1, end, l, r, v);
    merge(node);
}

// Range Sum Query Command
long long query_sum(int node, int start, int end, int l, int r) {
    if (start > r || end < l) {
        return 0;
    }
    if (start >= l && end <= r) {
        return tree[node].sum;
    }
    push_down(node);
    int mid = start + (end - start) / 2;
    return query_sum(2 * node, start, mid, l, r) + 
           query_sum(2 * node + 1, mid + 1, end, l, r);
}

int main() {
    // Optimize standard input/output streams for fast performance execution
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (cin >> n >> q) {
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        
        build(1, 1, n);
        
        for (int i = 0; i < q; i++) {
            int type, l, r;
            cin >> type >> l >> r;
            if (type == 1) {
                int v;
                cin >> v;
                update_min(1, 1, n, l, r, v);
            } else if (type == 2) {
                cout << query_sum(1, 1, n, l, r) << "\n";
            }
        }
    }
    return 0;
}