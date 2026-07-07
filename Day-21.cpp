#include <iostream>
#include <vector>

void find_flower_indices(int n, int t, std::vector<int>& arr, int result[2]) {
    int left = 0;
    int right = n - 1;

    // Use the two-pointer approach to find the target sum in O(N) time
    while (left < right) {
        int current_sum = arr[left] + arr[right];

        if (current_sum == t) {
            result[0] = left;
            result[1] = right;
            return; // Guaranteed first valid occurrence pair found
        } else if (current_sum < t) {
            left++; // Increase the sum by moving to a larger element
        } else {
            right--; // Decrease the sum by moving to a smaller element
        }
    }
}

int main() {
    // Optimize standard input/output channels for competitive programming execution
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, t;
    if (!(std::cin >> n >> t)) return 0;
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    int result[2] = {0, 0};
    find_flower_indices(n, t, arr, result);
    std::cout << result[0] << " " << result[1] << "\n";
    
    return 0;
}
