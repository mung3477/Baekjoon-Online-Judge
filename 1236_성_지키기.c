/*
    1. 빈 열/행 목록 만들기
    2. 최소 필요 경비원 계산

    빈 열/행에 해당하는 칸들을 볼건데,
    해당 칸이 채울 수 있는 열/행이 가장 큰 칸부터 채움

    한 칸 -> 0, 1, 2
*/

#include <stdio.h>

char    has_man_row[51];
char    has_man_col[51];

int max(int a, int b)
{
    if (a < b)
        return (b);
    else
        return (a);
}

int main(void)
{
    int     N;
    int     M;
    int     ans;
    int     need;
    char    input;

    N = 0;
    M = 0;
    ans = 0;
    need = 0;

    while (1)
    {
        input = getchar();
        if ('0' <= input && input <= '9')
            N = N * 10 + input - '0';
        else
            break;
    }
    while (1)
    {
        input = getchar();
        if ('0' <= input && input <= '9')
            M = M * 10 + input - '0';
        else
            break;
    }
    
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            input = getchar();
            if (input == 'X')
            {
                has_man_row[i] = 1;
                has_man_col[j] = 1;
            }
        }
        getchar();
    }

    for (int i = 1; i <= N; i++)
        if (!has_man_row[i])
            need += 1;
    ans = max(ans, need);

    need = 0;
    for (int j = 1; j <= M; j++)
        if (!has_man_col[j])
            need += 1;
    ans = max(ans, need);

    printf("%d", ans);
    return (0);
}