#include <stdio.h>

void    solve(int N, int g_num)
{
    char    names[20][61];
    char    name[61];
    char    think;
    int     made_nasty[20][20];
    int     nasty_ppl;
    int     jdx;


    nasty_ppl = 0;

    if (!N)
        return ;

    for (int i = 0; i < 20; i++)
        for (int j = 0; j <= 60; j++)
            names[i][j] = '\0';

    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k <= 60; k++)
            name[k] = '\0';
        scanf("%s", name);
        for (int k = 0; name[k]; k++)
            names[i][k] = name[k];
        
        made_nasty[i][i] = 0;
        for (int j = 1; j < N; j++)
        {
            scanf(" %c", &think);
            made_nasty[i][(i < j ? i - j + N : i - j)] = (think == 'P' ? 0 : 1);
        }
    }

    if (1 < g_num)
        printf("\n");
    printf("Group %d\n", g_num);
    for (int i = 0; i < N ; i++)
        for (int j = 1; j < N; j++)
        {
            jdx = (i < j ? i - j + N : i - j);
            if (made_nasty[i][jdx])
            {
                printf("%s was nasty about %s\n", names[jdx], names[i]);
                nasty_ppl += 1;
            }
        }
    if (!nasty_ppl)
        printf("Nobody was nasty\n");
}

int main(void)
{
    int N;
    int i;

    i = 1;
    scanf("%d", &N);
    while (N)
    {
        solve(N, i++);
        scanf("%d", &N);
    }
    return (0);
}