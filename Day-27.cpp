#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort to sort in descending order
int compare_desc(const void* a, const void* b) {
    int val_a = *(const int*)a;
    int val_b = *(const int*)b;
    
    if (val_a < val_b) return 1;
    if (val_a > val_b) return -1;
    return 0;
}

void dispatch_order(int n, int k, int* priorities, int* result) {
    // Sort the entire priorities array in descending order
    qsort(priorities, n, sizeof(int), compare_desc);
    
    // Copy the first K highest priorities into the result array
    for (int i = 0; i < k; ++i) {
        result[i] = priorities[i];
    }
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return 0;
    
    int* priorities = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &priorities[i]) != 1) return 0;
    }
    
    int* result = (int*)malloc(k * sizeof(int));
    
    // Call user logic function
    dispatch_order(n, k, priorities, result);
    
    // Print the output exactly as required by the template matching STDOUT format
    for (int i = 0; i < k; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    free(priorities);
    free(result);
    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> 84acad8e788b8e36c7e9e7180e454a996336624e
