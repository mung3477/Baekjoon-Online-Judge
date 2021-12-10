#include <stdio.h>

int main() {
    freopen("output.txt", "w", stdout);

    printf("100000 100000 0\n");

    for (int i = 1; i < 100000; i++)
        printf("%d %d\n", i, i + 1);

    return 0;
}