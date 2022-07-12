#include <stdio.h>

int main(void)
{
    int A, B, N, i, num;

    i = 0;
    scanf("%d %d %d", &A, &B, &N);

    A %= B;
    while (i < N)
    {
        num = A * 10 / B;
        A = A * 10 % B;
        i += 1;
    }
    printf("%d", num);
}