#include <stdio.h>

int main(void)
{
    int n;
    int prev;
    int new;
    int ans;

    new = -1;
    ans = 0;
    scanf("%d", &n);
    prev = n;

    while (n != new)
    {
        new = prev / 10 + prev % 10;
        new = (prev % 10) * 10 + new % 10;
        prev = new;
        ans += 1;
    }
    printf("%d", ans);
    return (0);
}