#include <stdio.h>

// Helper function to calculate Greatest Common Divisor (GCD)
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long nextTogether(int a, int b) {
    long long A = a;
    long long B = b;
    
    // LCM = (A * B) / GCD(A, B)
    return (A / gcd(A, B)) * B;
}

int main() {
    int a, b;

    // Read two integers from input
    if (scanf("%d %d", &a, &b) == 2) {
        // Call the logic function and print the result
        long long result = nextTogether(a, b);
        printf("%lld\n", result);
    }

    return 0;
}