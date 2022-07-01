#include <stdio.h>

int rev(int A)
{
    int ret;

    ret = 0;
    while (A)
    {
        ret = ret * 10 + (A % 10);
        A /= 10;
    }
    return (ret);
}

int main(void)
{
    int X, Y;

    scanf("%d %d", &X, &Y);
    printf("%d", rev(rev(X) + rev(Y)));
    return (0);
}