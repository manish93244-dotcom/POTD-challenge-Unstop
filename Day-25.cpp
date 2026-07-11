#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getTopRecord(char operations[][100], int N) {
    // Dynamically allocate memory for the stack array to safely handle N up to 100,000
    int* stack = (int*)malloc(N * sizeof(int));
    int top = -1; // Index tracker pointing to the top element of the stack

    for (int i = 0; i < N; ++i) {
        // If the operation starts with "ADD", extract the number value X
        if (strncmp(operations[i], "ADD", 3) == 0) {
            int value;
            // Parse out the integer from strings like "ADD 10"
            sscanf(operations[i], "ADD %d", &value);
            top++;
            stack[top] = value;
        } 
        // Otherwise, it is a "REMOVE" operation
        else if (strncmp(operations[i], "REMOVE", 6) == 0) {
            if (top >= 0) {
                top--; // Simulates popping the top element
            }
        }
    }

    // Capture the final answer before freeing the memory allocation
    int final_record = (top == -1) ? -1 : stack[top];
    
    free(stack);
    return final_record;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    // Allocate operations block dynamically to prevent stack overflow on high N values
    char (*operations)[100] = malloc(N * sizeof(*operations));
    if (operations == NULL) return 0;

    // Read each operation based on the template logic provided
    for (int i = 0; i < N; ++i) {
        scanf("%s", operations[i]);
        if (strcmp(operations[i], "ADD") == 0) {
            char x[100];
            scanf("%s", x);
            strcat(operations[i], " ");
            strcat(operations[i], x);
        }
    }

    // Call user logic function and print the final output matching the platform configuration
    int result = getTopRecord(operations, N);
    printf("%d\n", result);

    free(operations);
    return 0;
}
