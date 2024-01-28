#include <stdio.h>

int main() {
    int a = 5;
    float b = 3.14;
    
    if (a > 0) {
        printf("Hello, World!\n");
    } else {
        printf("Goodbye, World!\n");
    }

    for (int i = 0; i < 3; i++) {
        printf("Iteration %d\n", i);
    }

    return 0;
}
