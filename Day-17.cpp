#include <iostream>
#include <string>

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

std::string valid_partition(Node* head, int x) {
    bool entered_heavy_zone = false;
    Node* current = head;

    while (current != nullptr) {
        if (current->val >= x) {
            // Once an element is >= X, we enter the heavy zone
            entered_heavy_zone = true;
        } else {
            // If we are already in the heavy zone, we cannot see an element < X
            if (entered_heavy_zone) {
                return "NO";
            }
        }
        current = current->next;
    }

    return "YES";
}

int main() {
    // Optimize standard input/output streams for execution efficiency
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, x;
    if (!(std::cin >> n >> x)) return 0;
    
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        Node* node = new Node(value);
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    
    std::string result = valid_partition(head, x);
    std::cout << result << "\n";

    return 0;
}
