#include <stdio.h>

int main(void)
{
    int N;
    scanf("%d", &N);
    for(N; N >= 1; N--) {
        for(int i = N; i > 0; i--) {
            printf("*");
        }
        printf("\n");
    }
}