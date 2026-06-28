#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct Tower {
    long long val;
    int left;
    int right;
};

int main() {
    // Maximize standard I/O efficiency
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    if (n == 0) {
        cout << 0 << "\n";
        return 0;
    }

    // Read input precisely into sequential 0-indexed positions
    vector<Tower> tree(n);
    for (int i = 0; i < n; i++) {
        cin >> tree[i].val >> tree[i].left >> tree[i].right;
    }

    // FIXED FOR TESTCASE 8: Use a deeply negative floor (-1e18) 
    // to represent empty space so it never conflicts with low positive signals
    vector<long long> max_subtree_val(n, -1000000000000000000LL);
    vector<bool> is_peak(n, true);
    
    // Bottom-up Post-Order traversal simulation stacks
    stack<int> s1, s2;
    
    // Tower 0 is guaranteed to be the structural root
    s1.push(0); 
    
    while (!s1.empty()) {
        int curr = s1.top();
        s1.pop();
        s2.push(curr);
        
        if (tree[curr].left != -1) {
            s1.push(tree[curr].left);
        }
        if (tree[curr].right != -1) {
            s1.push(tree[curr].right);
        }
    }

    int peak_count = 0;

    // Process nodes iteratively from leaves to root
    while (!s2.empty()) {
        int curr = s2.top();
        s2.pop();

        long long current_val = tree[curr].val;
        long long max_from_descendants = current_val;
        bool has_children = false;

        // Check Left Child Subtree
        if (tree[curr].left != -1) {
            has_children = true;
            int left_child = tree[curr].left;
            if (max_subtree_val[left_child] >= current_val) {
                is_peak[curr] = false;
            }
            max_from_descendants = max(max_from_descendants, max_subtree_val[left_child]);
        }

        // Check Right Child Subtree
        if (tree[curr].right != -1) {
            has_children = true;
            int right_child = tree[curr].right;
            if (max_subtree_val[right_child] >= current_val) {
                is_peak[curr] = false;
            }
            max_from_descendants = max(max_from_descendants, max_subtree_val[right_child]);
        }

        // If it is a leaf node, its subtree max is simply its own value
        if (!has_children) {
            max_subtree_val[curr] = current_val;
        } else {
            max_subtree_val[curr] = max_from_descendants;
        }

        if (is_peak[curr]) {
            peak_count++;
        }
    }

    cout << peak_count << "\n";

    return 0;
}
