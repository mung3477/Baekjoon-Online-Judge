#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char    N[11] = {0, };
    int     A, B, length, ans, zero_count;

    A = 1;
    ans = 0;
    zero_count = 0;
    scanf("%s", N);
    B = 1;
    length = strlen(N);
    for (int i = 0; i < length; i++)
    {
        B *= N[i] - '0';
        if (N[i] == '0')
            zero_count += 1;
    }

    if (1 < zero_count)
        ans = 1;
    else if (zero_count == 0)
    {
        for (int i = 0; i < length - 1; i++)
        {
            A *= N[i] - '0';
            B /= N[i] - '0';
            if (A == B)
            {
                ans = 1;
                break;
            }
        }
    }

    printf("%s", (ans ? "YES" : "NO"));
    return (0);
}