#include <stdio.h>

int findUniqueGuest(int* registrationIDs, int N) {
    // Initialize the result to 0
    int uniqueID = 0;
    
    // XOR all elements in the array
    for (int i = 0; i < N; i++) {
        uniqueID ^= registrationIDs[i];
    }
    
    return uniqueID;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    int registrationIDs[N];
    for (int i = 0; i < N; ++i) {
        if (scanf("%d", &registrationIDs[i]) != 1) return 0;
    }
    
    int uniqueID = findUniqueGuest(registrationIDs, N);
    printf("%d\n", uniqueID);
    
    return 0;
}
