#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

// Structure representing a node in the Binary Search Tree
struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Function to insert a new value into the BST
Node* insert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

// Function to perform Level Order Traversal (BFS) and print stage by stage
void printLevelOrder(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();

            cout << current->val << (i == levelSize - 1 ? "" : " ");

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        cout << "\n";
    }
}

int main() {
    // Optimize standard input/output streaming operations for fast execution
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        Node* root = nullptr;
        for (int i = 0; i < n; ++i) {
            int towerID;
            cin >> towerID;
            root = insert(root, towerID);
        }

        printLevelOrder(root);
    }

    return 0;
}