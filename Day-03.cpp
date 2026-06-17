#include <iostream>
#include <vector>

int find_lucky_stone_pairs(int p, int n, int m, std::vector<int>& stones) {
    // Write your logic here.
    long long valid_stones_count = 0;

    // Count how many individual stones satisfy the divisibility condition
    for (int i = 0; i < p; ++i) {
        if (stones[i] % n == 0 || stones[i] % m == 0) {
            valid_stones_count++;
        }
    }

    // Calculate total pairs using the combination formula: K * (K - 1) / 2
    // Using cast to long long to securely avoid integer overflows
    long long total_pairs = (valid_stones_count * (valid_stones_count - 1)) / 2;

    return total_pairs;
}

int main() {
    // Optimize standard I/O operations for competitive environments
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int p, n, m;
    if (std::cin >> p >> n >> m) {
        std::vector<int> stones(p);
        for (int i = 0; i < p; ++i) {
            std::cin >> stones[i];
        }
        int result = find_lucky_stone_pairs(p, n, m, stones);
        std::cout << result << std::endl;
    }
    return 0;
}