#include <stdio.h>

int seq[1001];

int main(void)
{
    int idx, cur_num, put, A, B, ans;

    idx = 1;
    cur_num = 1;
    put = 0;
    ans = 0;
    while (idx <= 1000)
    {
        if (put == cur_num)
        {
            cur_num += 1;
            put = 0;
        }
        seq[idx] = cur_num;
        put += 1;
        idx += 1;
    }
    
    scanf("%d %d", &A, &B);
    for (int i = A; i <= B; i++)
        ans += seq[i];
    printf("%d", ans);
    
    return (0);
}