#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Node {
public:
    int node_id;
    int value;
    int next_id;
    Node* next;

    Node(int node_id, int value, int next_id) : node_id(node_id), value(value), next_id(next_id), next(nullptr) {}
};

void recover_chain(int n, vector<Node>& node_details, int start_id) {
    // Phase 1: Establish the node pointer connections
    unordered_map<int, Node*> id_to_node;
    for (int i = 0; i < n; ++i) {
        id_to_node[node_details[i].node_id] = &node_details[i];
    }

    for (int i = 0; i < n; ++i) {
        if (node_details[i].next_id != -1 && id_to_node.count(node_details[i].next_id)) {
            node_details[i].next = id_to_node[node_details[i].next_id];
        }
    }

    if (!id_to_node.count(start_id)) return;
    Node* start_node = id_to_node[start_id];

    // Phase 2: Floyd's Tortoise and Hare Cycle Detection Algorithm (O(1) Memory)
    Node* slow = start_node;
    Node* fast = start_node;
    bool has_cycle = false;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            has_cycle = true;
            break;
        }
    }

    // Phase 3: Break the cycle in-place if detected
    if (has_cycle) {
        Node* ptr1 = start_node;
        Node* ptr2 = slow;

        // If the cycle loops directly back to the start node
        if (ptr1 == ptr2) {
            while (ptr2->next != ptr1) {
                ptr2 = ptr2->next;
            }
            ptr2->next = nullptr;
        } else {
            // Move both at the same speed to locate the cycle's starting node
            while (ptr1 != ptr2) {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
            
            // ptr1 is now the entry node of the cycle. Find the node pointing to it.
            Node* curr = ptr1;
            while (curr->next != ptr1) {
                curr = curr->next;
            }
            curr->next = nullptr; // Break the cycle
        }
    }

    // Phase 4: Output the recovered simple chain values
    Node* traversal = start_node;
    bool first = true;
    while (traversal != nullptr) {
        if (!first) {
            cout << " ";
        }
        cout << traversal->value;
        first = false;
        traversal = traversal->next;
    }
    cout << "\n";
}

int main() {
    // Optimize standard input/output streams for speed
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Node> node_details;
    node_details.reserve(n);
    for (int i = 0; i < n; ++i) {
        int node_id, value, next_id;
        cin >> node_id >> value >> next_id;
        node_details.emplace_back(node_id, value, next_id);
    }

    int start_id;
    cin >> start_id;

    recover_chain(n, node_details, start_id);

    return 0;
}
