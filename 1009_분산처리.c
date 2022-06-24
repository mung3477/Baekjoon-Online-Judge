#include <stdio.h>

void    solve(void)
{
    int a;
    int b;
    int cycle_size;
    int t;
    int cycle_loc;

    cycle_size = 1;

    scanf("%d %d", &a, &b);
    t = a % 10;

    while (1)
    {
        t = t * a % 10;

        if (t == a % 10)
            break ;
        cycle_size += 1;
    }

    t = 1;
    cycle_loc = b % cycle_size;
    if (cycle_loc == 0)
        cycle_loc = cycle_size;
    
    for (int i = 1; i <= cycle_loc; i++)
        t = t * a % 10;
    printf("%d\n", (t == 0 ? 10 : t));
}

int main(void)
{
    int T;

    scanf("%d", &T);
    while (T)
    {
        solve();
        T -= 1;
    }
    return (0);
}