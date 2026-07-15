#include <stdio.h>
#include <stdlib.h>

// Helper function to perform binary search (similar to lower_bound)
int lower_bound(int* tails, int len, int target) {
    int low = 0, high = len - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (tails[mid] >= target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int longest_chain(int arr[], int n) {
    if (n == 0) return 0;

    // Allocate memory for tracking active subsequence tail elements
    int* tails = (int*)malloc(n * sizeof(int));
    int len = 0;

    for (int i = 0; i < n; i++) {
        int idx = lower_bound(tails, len, arr[i]);
        
        tails[idx] = arr[i];
        if (idx == len) {
            len++;
        }
    }

    free(tails);
    return len;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    // Dynamically allocate to safely handle the upper bound array size constraints
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) return 0;
    }

    int result = longest_chain(arr, n);
    printf("%d\n", result);

    free(arr);
    return 0;
}
