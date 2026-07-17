#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int min_energy(int* energy, int n) {
    // Allocate memory for the dp array
    long long* dp = (long long*)malloc(n * sizeof(long long));
    
    // Initialize the base case
    dp[0] = 0;
    
    // Fill the rest of the dp table with a very large value representing infinity
    for (int i = 1; i < n; i++) {
        dp[i] = 1e18; // Use a large value to safely avoid integer overflow
    }
    
    // Compute the minimum energy needed for each subsequent tower
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < j; i++) {
            long long current_jump_cost = (long long)abs(energy[i] - energy[j]) * (j - i);
            long long total_cost = dp[i] + current_jump_cost;
            if (total_cost < dp[j]) {
                dp[j] = total_cost;
            }
        }
    }
    
    // Capture the final answer for the last tower
    int result = (int)dp[n - 1];
    
    free(dp);
    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    int* energy = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &energy[i]) != 1) return 0;
    }
    
    // Call user logic function and print the final output matching the template structure
    int result = min_energy(energy, n);
    printf("%d\n", result);
    
    free(energy);
    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> 84acad8e788b8e36c7e9e7180e454a996336624e
