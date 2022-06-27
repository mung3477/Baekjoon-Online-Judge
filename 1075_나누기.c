#include <stdio.h>

int main(void)
{
    int N, F, ans;

    scanf("%d\n%d", &N, &F);

    N = N / 100 * 100;
    ans = 0;

    while ((N + ans) % F)
        ans += 1;
    
    printf("%d%d", ans / 10, ans % 10);
    return (0);
}