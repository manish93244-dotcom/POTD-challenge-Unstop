#include <iostream>

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

std::string valid_partition(Node* head, int x)
{
    Node* current = head;
    bool foundGreaterEqual = false;

    while (current != nullptr)
    {
        if (current->val >= x)
        {
            foundGreaterEqual = true;
            break;
        }

        current = current->next;
    }

    if (!foundGreaterEqual)
    {
        return "NO";
    }

    while (current != nullptr)
    {
        if (current->val < x)
        {
            return "NO";
        }

        current = current->next;
    }

    return "YES";
}
int main() {
    int n, x;
    std::cin >> n >> x;
    
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
    std::cout << result << std::endl;

    return 0;
}
